package projekat;

import java.util.ArrayList;

public class Selection {
	private ArrayList<Rectangle> selection = new ArrayList<Rectangle>();
	private String name;
	private boolean active;
	private int pocetak;
	private int kraj;

	public int getPocetak() {
		return pocetak;
	}
	public void addRectangle(Rectangle r) {
		selection.add(r);
	}
	public void setPocetak(int pocetak) {
		this.pocetak = pocetak;
	}

	public int getKraj() {
		return kraj;
	}

	public void setKraj(int kraj) {
		this.kraj = kraj;
	}

	public Selection(ArrayList<Rectangle> selection_, String name_, boolean active_) {
		selection = selection_;
		name = name_;
		active = active_;
	}
	public Selection(String name_, boolean active_) {
		name = name_;
		active = active_;
	}
	
	public ArrayList<Rectangle> getSelection() {
		return selection;
	}

	public void setSelection(ArrayList<Rectangle> selection) {
		this.selection = selection;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public boolean isActive() {
		return active;
	}

	public void setActive(boolean active) {
		this.active = active;
	}

	public void addRectangle(int x , int y, int w, int h) {
		selection.add(new Rectangle(x, y, w, h));
	}
}
