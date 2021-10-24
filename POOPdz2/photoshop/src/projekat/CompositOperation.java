package projekat;

import java.util.ArrayList;

public class CompositOperation extends Operation{
	String name;
	private ArrayList<Operation> comp = new ArrayList<Operation>();

	public CompositOperation(String name) {
		super();
		this.name = name;
	}

	public ArrayList<Operation> getComp() {
		return comp;
	}

	public void setComp(ArrayList<Operation> comp) {
		this.comp = comp;
	}
	
	public void addOperation(Operation o) {
		comp.add(o);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
}
