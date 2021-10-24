package projekat;

import java.awt.BasicStroke;
import java.awt.Canvas;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Image extends Canvas {
	private double ap = 1;
	private ArrayList<Layer> image = new ArrayList<Layer>();
	private double a = 0;
	private int b = 0;
	private int r = 0;
	private int g = 0;
	private int width;
	private int height;
	private HashMap<String, Selection> selection_map = new HashMap<String, Selection>();
	private ArrayList<Rectangle> tempRect = new ArrayList<Rectangle>();
	private BufferedImage merged;
	private ArrayList<BasicOperation> operations = new ArrayList<BasicOperation>();
	private ArrayList<CompositOperation> compOperations = new ArrayList<CompositOperation>();
	private Map<Selection, ArrayList<Line>> line_map = new HashMap<Selection, ArrayList<Line>>();
	int brLine = 0;
	int beg = 0;

	public int getBeg() {
		return beg;
	}

	public void setBeg(int beg) {
		this.beg = beg;
	}

	public int getbrLine() {
		return brLine;
	}

	public void addComp(CompositOperation c) {
		compOperations.add(c);
	}

	public Map<Selection, ArrayList<Line>> getLine_map() {
		return line_map;
	}

	public ArrayList<Line> getLines() {
		return lines;
	}

	public void setLines(ArrayList<Line> lines) {
		this.lines = lines;
	}

	public ArrayList<CompositOperation> getCompOperations() {
		return compOperations;
	}

	public void setCompOperations(ArrayList<CompositOperation> compOperations) {
		this.compOperations = compOperations;
	}

	public ArrayList<BasicOperation> getOperations() {
		return operations;
	}

	public void setOperations(ArrayList<BasicOperation> operations) {
		this.operations = operations;
	}

	public void addOperation(BasicOperation o) {
		operations.add(o);
	}

	ArrayList<Line> lines = new ArrayList<>();
	private Line line;

	public Image() {
		addMouseListener(new MouseEventHandler());
		addMouseMotionListener(new MouseEventHandler());
	}

	public ArrayList<Rectangle> getTempRect() {
		return tempRect;
	}

	public void setTempRect(ArrayList<Rectangle> tempRect) {
		this.tempRect = tempRect;
	}

	private class MouseEventHandler extends MouseAdapter {

		@Override
		public void mouseDragged(MouseEvent e) {
			/*
			 * Pamcenje kraja linije i slanje zahteva za iscrtavanje kako bi korisnik video
			 * liniju koju trenutno iscrtava.
			 */

			if (e.getX() > width)
				line.endX = width;
			else if (e.getX() <= 0)
				line.endX = 0;
			else
				line.endX = e.getX();
			if (e.getY() > height)
				line.endY = height;
			else if (e.getY() <= 0)
				line.endY = 0;
			else
				line.endY = e.getY();
			repaint();
		}

		@Override
		public void mousePressed(MouseEvent e) {
			/*
			 * Na pritisak misa ce se kreirati novi objekat linije zapamtiti pocetne
			 * koordinate novokreirane linije i dodati linija u listu linija koje treba da
			 * se iscrtaju.
			 */
			line = new Line();
			lines.add(line);
			brLine++;
			line.begX = e.getX();
			line.begY = e.getY();
		}

		@Override
		public void mouseReleased(MouseEvent e) {
			tempRect.add(new Rectangle(Integer.min(line.endX, line.begX), Integer.min(line.endY, line.begY),
					Math.abs(line.begX - line.endX), Math.abs(line.begY - line.endY)));
			repaint();
		}
	}

	public void addLayer(Layer l) {
		if (image.isEmpty()) {
			image.add(l);
		} else {
			if (l.getHeight() < image.get(0).getHeight() && l.getWidth() > image.get(0).getWidth()) {
				for (Layer lay : image) {
					lay.extendLayerByX(lay, l);
				}
				l.extendLayerByY(l, image.get(0));
			}
			if (l.getHeight() > image.get(0).getHeight() && l.getWidth() < image.get(0).getWidth()) {
				for (Layer lay : image) {
					lay.extendLayerByY(lay, l);
				}
				l.extendLayerByX(l, image.get(0));
			}
			if (l.getHeight() < image.get(0).getHeight() && l.getWidth() < image.get(0).getWidth()) {
				l.extendLayerByX(l, image.get(0));
				l.extendLayerByY(l, image.get(0));
			}
			if (l.getHeight() > image.get(0).getHeight() && l.getWidth() > image.get(0).getWidth()) {
				for (Layer lay : image) {
					lay.extendLayerByX(lay, l);
					lay.extendLayerByY(lay, l);
				}
			}
			image.add(l);
		}
		height = l.getHeight();
		width = l.getWidth();
		merged = mergeLayers();
	}

	public BufferedImage getMerged() {
		return merged;
	}

	public void setMerged(BufferedImage merged) {
		this.merged = merged;
	}

	public BufferedImage mergeLayers() {
		BufferedImage merged = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				resetRGBA();
				for (Layer l : image) {
					if (l.isActive()) {
						int argb = l.getBufferImage().getRGB(j, i);
						int red = 0xFF & (argb >> 16);
						int alpha = 0xFF & (argb >> 24);
						int blue = 0xFF & (argb >> 0);
						int green = 0xFF & (argb >> 8);
						operationA(alpha, l.getTransparency());
						operationRGB(red, green, blue, alpha, l.getTransparency());
						if (l.getTransparency() == 100)
							break;
					}
				}
				double a1 = a;
				int b1 = b;
				int r1 = r;
				int g1 = g;
				if (a1 != 0) {
					b1 = (int) ((double) b1 / a1);
					b1 = b1 % 256;
					r1 = (int) ((double) r1 / a1);
					r1 = r1 % 256;
					g1 = (int) ((double) g1 / a1);
					g1 = g1 % 256;
				}
				a1 = a1 * 255;
				int tempA = (int) a1;
				g1 = g1 << 8;
				r1 = r1 << 16;
				tempA = tempA << 24;

				int rgba = g1 | r1 | b1 | tempA;
				merged.setRGB(j, i, rgba);
			}
		}
		return merged;
	}

	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}

	public void paint(Graphics g) {
		Stroke dashed = new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[] { 9 }, 0);
		Graphics2D gg = (Graphics2D) g.create();
		gg.clearRect(0, 0, getSize().width, getSize().height);
		gg.setStroke(dashed);
		if (!image.isEmpty()) {
			gg.drawImage(mergeLayers(), 0, 0, null);
			/*
			 * Crtanje linija pocevsi od njihovih koordinata (begX, begY) pa do (endX, endY)
			 */

			if (line_map.isEmpty()) {
				for (Line line : lines) {
					if (line.begX > width || line.begY > height)
						continue;
					gg.drawRect(Integer.min(line.endX, line.begX), Integer.min(line.endY, line.begY),
							Math.abs(line.begX - line.endX), Math.abs(line.begY - line.endY));
				}
			} else {
				for (Selection s : line_map.keySet()) {
					if (s.isActive()) {
						for(int i = 0; i< line_map.get(s).size() ; i++) {
							if (line_map.get(s).get(i).begX > width || line_map.get(s).get(i).begY > height)
								continue;
							gg.drawRect(Integer.min(line_map.get(s).get(i).endX, line_map.get(s).get(i).begX), 
									Integer.min(line_map.get(s).get(i).endY, line_map.get(s).get(i).begY),
									Math.abs(line_map.get(s).get(i).begX - line_map.get(s).get(i).endX), 
									Math.abs(line_map.get(s).get(i).begY - line_map.get(s).get(i).endY));
						}
					}
				}
			}
		}
	}

	void addSelection(String name, Selection s) {
		selection_map.put(name, s);
	}

	public double getAp() {
		return ap;
	}

	public void setAp(double ap) {
		this.ap = ap;
	}

	public ArrayList<Layer> getImage() {
		return image;
	}

	public void setImage(ArrayList<Layer> image) {
		this.image = image;
	}

	public double getA() {
		return a;
	}

	public void setA(double a) {
		this.a = a;
	}

	public int getB() {
		return b;
	}

	public void setB(int b) {
		this.b = b;
	}

	public int getR() {
		return r;
	}

	public void setR(int r) {
		this.r = r;
	}

	public int getG() {
		return g;
	}

	public void setG(int g) {
		this.g = g;
	}

	public HashMap<String, Selection> getSelection_map() {
		return selection_map;
	}

	public void setSelection_map(HashMap<String, Selection> selection_map) {
		this.selection_map = selection_map;
	}

	public void calculateAp(double an, double LayerTransparency) {
		ap = ap - (ap * an * LayerTransparency / 100) / 255;
	}

	public void operationA(int alpha, double LayerTransparency) {
		a = a + ((((double) alpha) / 255) * ap * LayerTransparency / 100);
	}

	public void operationRGB(int r_, int g_, int b_, int a_, double LayerTransparency) {
		b = (int) (b + (b_ * ap * ((double) a_ / 255) * LayerTransparency / 100));
		r = (int) (r + (r_ * ap * ((double) a_ / 255) * LayerTransparency / 100));
		g = (int) (g + (g_ * ap * ((double) a_ / 255) * LayerTransparency / 100));
		calculateAp(a_, LayerTransparency);
	}

	public void resetRGBA() {
		ap = 1;
		a = 0;
		b = 0;
		r = 0;
		g = 0;
	}

	public void removeLayer(String name) {
		for (int i = 0; i < image.size(); i++) {
			if (image.get(i).getName().equals(name))
				image.remove(i);
		}
		mergeLayers();
	}

}
