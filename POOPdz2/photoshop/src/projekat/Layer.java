package projekat;

import java.awt.image.BufferedImage;

public class Layer {
	private int transparency;
	private boolean active = true;
	private int selected = 0;
	private boolean visible = true;
	private String name;
	private int width;
	private int height;
	private BufferedImage layer;
	private String chName;

	public String getChName() {
		return chName;
	}

	public void setChName(String chName) {
		this.chName = chName;
	}

	public BufferedImage getBufferImage() {
		return layer;
	}

	public void setBufferImage(BufferedImage layer) {
		this.layer = layer;
	}

	public Layer(int transparency_, boolean active_, int selected_, boolean visible_, String name_, int width_,
			int height_) {
		transparency = transparency_;
		active = active_;
		selected = selected_;
		visible = visible_;
		name = name_;
		width = width_;
		height = height_;
	}

	public Layer(int width_, int height_) {
		width = width_;
		height = height_;
	}

	public int getTransparency() {
		return transparency;
	}

	public void setTransparency(int transparency) {
		this.transparency = transparency;
	}

	public boolean isActive() {
		return active;
	}

	public void setActive(boolean active) {
		this.active = active;
	}

	public int getSelected() {
		return selected;
	}

	public void setSelected() {
		selected++;
	}

	public void minusSelected() {
		--selected;
	}

	public boolean isVisible() {
		return visible;
	}

	public void setVisible(boolean visible) {
		this.visible = visible;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getWidth() {
		return layer.getWidth();
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getHeight() {
		return layer.getHeight();
	}

	public void setHeight(int height) {
		this.height = height;
	}

	void extendLayerByY(Layer extending, Layer sizeLayer) {
		BufferedImage extended = new BufferedImage(extending.width, sizeLayer.height, BufferedImage.TYPE_INT_ARGB);
		for (int i = 0; i < sizeLayer.height; i++) {
			for (int j = 0; j < extending.width; j++) {
				if (i < extending.height)
					extended.setRGB(j, i, extending.getBufferImage().getRGB(j, i));
				else
					extended.setRGB(j, i, 0);
			}
		}
		extending.setBufferImage(extended);
	}

	void extendLayerByX(Layer extending, Layer sizeLayer) {
		BufferedImage extended = new BufferedImage(sizeLayer.width, extending.height, BufferedImage.TYPE_INT_ARGB);
		//System.out.println("width:" + sizeLayer.width + "height:" + sizeLayer.height);
		for (int i = 0; i < extending.height; i++) {
			for (int j = 0; j < sizeLayer.width; j++) {
				if (j < extending.width) {
					extended.setRGB(j, i, extending.getBufferImage().getRGB(j, i));
					//System.out.println("j:" + j + "i:" + i);
				}
				else
					extended.setRGB(j, i, 0);
			}
		}
		extending.setBufferImage(extended);
	}

}
