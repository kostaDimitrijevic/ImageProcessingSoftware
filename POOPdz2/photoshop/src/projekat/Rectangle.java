package projekat;

public class Rectangle {
	private int x;
	private int y;
	private int height;
	private int width;

	public Rectangle(int x_, int y_, int width_, int height_) {
		x = x_;
		y = y_;
		height = height_;
		width = width_;
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}

	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}

	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}
	
}
