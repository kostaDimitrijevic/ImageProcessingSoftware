package projekat;

public class BasicOperation extends Operation{
	private String operation;
	private int c;
	private boolean nema;
	public boolean isNema() {
		return nema;
	}
	public void setNema(boolean nema) {
		this.nema = nema;
	}
	public BasicOperation(String operation, int c) {
		super();
		this.operation = operation;
		this.c = c;
	}
	public String getOperation() {
		return operation;
	}
	public void setOperation(String operation) {
		this.operation = operation;
	}
	public int getC() {
		return c;
	}
	public void setC(int c) {
		this.c = c;
	}
	
}
