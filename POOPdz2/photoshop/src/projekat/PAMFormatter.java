package projekat;

import java.awt.image.BufferedImage;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;

public class PAMFormatter extends Formatter {

	@Override
	public Layer myImport(String file) {
		InputStream f = null;
		int width = 0;
		int height = 0;
		BufferedImage lay = null;
		try {
			f = new FileInputStream(file);
			int a0 = 0;
			int space = 0;
			char c = ' ';
			String w = "";
			String h = "";
			while (space < 2) {
				c = (char) f.read();
				if (c == ' ') {
					if (space == 0) {
						c = (char) f.read();
						while (c != '\n') {
							w = w + c;
							c = (char) f.read();
						}
						a0++;
						width = Integer.parseInt(w);
						space++;
						continue;
					}
					if (space == 1) {
						c = (char) f.read();
						while (c != '\n') {
							h = h + c;
							c = (char) f.read();
						}
						a0++;
						height = Integer.parseInt(h);
						space++;
					}
				}
			}
			while (a0 < 6) {
				c = (char) f.read();
				if (c == '\n')
					a0++;
			}
			int r, g, b, a;
			lay = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					r = f.read();
					g = f.read();
					b = f.read();
					a = f.read();
					g = g << 8;
					r = r << 16;
					a = a << 24;
					int rgba = r | g | b | a;
					lay.setRGB(j, i, rgba);
				}
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		} finally {
			try {
				if (f != null)
					f.close();
				Layer l = new Layer(lay.getWidth(), lay.getHeight());
				l.setBufferImage(lay);
				return l;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return null;
	}

	@Override
	public void myExport(String file, Image i) {
		OutputStream f = null;
		try {
			f = new FileOutputStream(file);
			byte[] P7 = { 'P', '7' };
			byte[] w = { 'W', 'I', 'D', 'T', 'H', ' ' };
			byte[] h = { 'H', 'E', 'I', 'G', 'H', 'T', ' ' };

			int width = i.getWidth();
			int height = i.getHeight();

			byte[] depth = { 'D', 'E', 'P', 'T', 'H', ' ', '4' };
			byte[] maxval = { 'M', 'A', 'X', 'V', 'A', 'L', ' ', '2', '5', '5' };
			byte[] tupltype = { 'T', 'U', 'P', 'L', 'T', 'Y', 'P', 'E', ' ' };
			byte[] rgba = { 'R', 'G', 'B', '_', 'A', 'L', 'P', 'H', 'A' };
			byte[] endhdr = { 'E', 'N', 'D', 'H', 'D', 'R' };
			byte[] nextRow = { '\n' };

			f.write(P7);
			f.write(nextRow);

			f.write(w);
			f.write(Integer.toString(width).getBytes());
			f.write(nextRow);

			f.write(h);
			f.write(Integer.toString(height).getBytes());
			f.write(nextRow);

			f.write(depth);
			f.write(nextRow);

			f.write(maxval);
			f.write(nextRow);

			f.write(tupltype);

			f.write(rgba);
			f.write(nextRow);

			f.write(endhdr);
			f.write(nextRow);
			
			i.mergeLayers();
			for (int p = 0; p < height; p++) {
				for (int q = 0; q < width; q++) {
					int argb = i.getMerged().getRGB(q, p);
					byte red = (byte) (0xFF & (argb >> 16));
					byte alpha = (byte) (0xFF & (argb >> 24));
					byte blue = (byte) (0xFF & (argb >> 0));
					byte green = (byte) (0xFF & (argb >> 8));
					f.write(new byte[] { red, green, blue, alpha });
				}
			}

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			if (f != null)
				try {
					f.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		}
	}

}
