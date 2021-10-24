package projekat;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;

import javax.imageio.ImageIO;

public class BMPFormatter extends Formatter {
	public static byte[] invertByte(byte[] arr) {
		byte temp;
		temp = arr[0];
		arr[0] = arr[3];
		arr[3] = temp;
		temp = arr[1];
		arr[1] = arr[2];
		arr[2] = temp;
		return arr;
	}

	public Layer myImport(String file) {
		BufferedImage lay;
		try {
			lay = ImageIO.read(new File(file));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
		Layer newLayer = new Layer(lay.getWidth(), lay.getHeight());
		newLayer.setBufferImage(lay);
		return newLayer;
	}

	public void myExport(String file, Image i) {
		OutputStream f = null;
		try {
			f = new FileOutputStream(file);
			byte[] ID = { 0x42, 0x4D };
			byte[] BMPsize = new byte[4];
			ByteBuffer.wrap(BMPsize).putInt(122 + i.getWidth() * i.getHeight() * 4);
			BMPsize = invertByte(BMPsize);
			byte[] offset = { 0x00, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, };

			byte[] DIB_size = { 0x6C, 0x00, 0x00, 0x00, };
			byte[] width = new byte[4];
			ByteBuffer.wrap(width).putInt(i.getWidth());
			width = invertByte(width);
			byte[] height = new byte[4];
			ByteBuffer.wrap(height).putInt(i.getHeight());
			height = invertByte(height);
			byte[] A_Eh = { 0x01, 0x00, 0x20, 0x00, 0x03, 0x00, 0x00, 0x00, };
			byte[] rawBitMap = new byte[4];
			ByteBuffer.wrap(rawBitMap).putInt(width.length * height.length * 4);
			rawBitMap = invertByte(rawBitMap);
			byte[] DIB = { // Size of the raw bitmap data (including padding) TREBA DA SE PROMENII
					0x13, 0x0B, 0x00, 0x00, // Print resolution of the image...
					0x13, 0x0B, 0x00, 0x00, // ..
					0x00, 0x00, 0x00, 0x00, // num of collor in the palette
					0x00, 0x00, 0x00, 0x00, // 0 means all colors are important
					0x00, 0x00, -1, 0x00, // Red channel bit mask
					0x00, -1, 0x00, 0x00, // Green channel bit mask
					-1, 0x00, 0x00, 0x00, // Blue channel bit mask
					0x00, 0x00, 0x00, -1, // Alpha channel bit mask
					0x20, 0x6E, 0x69, 0x57, // LCS_WINDOWS_COLOR_SPACE
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Unused for LCS "Win " or "sRGB"
					0x00, 0x00, 0x00, 0x00, // Unused for LCS "Win " or "sRGB"
					0x00, 0x00, 0x00, 0x00, // Unused for LCS "Win " or "sRGB"
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00// Unused
																											// for LCS
																											// "Win " or
																											// "sRGB"
					// STAR OF THE PIXEL ARRAY
			};
			f.write(ID);
			f.write(BMPsize);
			f.write(offset);
			f.write(DIB_size);
			f.write(width);
			f.write(height);
			f.write(A_Eh);
			f.write(rawBitMap);
			f.write(DIB);
			i.mergeLayers();
			for (int p = i.getHeight() - 1; p >= 0; p--) {
				for (int q = 0; q < i.getWidth(); q++) {
					int argb = i.getMerged().getRGB(q, p);
					byte red = (byte) (0xFF & (argb >> 16));
					byte alpha = (byte) (0xFF & (argb >> 24));
					byte blue = (byte) (0xFF & (argb >> 0));
					byte green = (byte) (0xFF & (argb >> 8));
					f.write(new byte[] { blue, green, red, alpha });
				}
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
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
