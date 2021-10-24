package gui;

import projekat.*;
import projekat.Image;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Prozor extends Frame implements ActionListener, ItemListener {
	private Panel layers;
	private Panel osnovni;
	private Panel operations;
	private Panel selection;
	private Panel left;
	public static HashMap<String, Checkbox> chLayers = new HashMap<String, Checkbox>();
	private HashMap<String, Checkbox> chSelections = new HashMap<String, Checkbox>();
	public static HashMap<Checkbox, Operation> chOperation = new HashMap<Checkbox, Operation>();

	private Image image = new Image();
	private BMPFormatter bmp = new BMPFormatter();
	private PAMFormatter pam = new PAMFormatter();
	private XMLFormatter xml = new XMLFormatter();
	private Button napraviLejer;
	private Button ukloniLejer;
	private Button sacuvajSliku;
	private Button napraviSelekciju;
	private Button konst;
	private Button dodajOp;
	private Button napraviComp;
	private Button forOperation;
	private Button meni;
	private CompositOperation nComp = new CompositOperation("comp");
	private Button da;
	private Button ne;
	boolean promena = true;
	boolean export = false;

	public Prozor() {
		super("Photoshop");
		setSize(1500, 1500);
		setVisible(true);
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				if (promena) {
					popZavrsno();
				}
			}
		});
		createMenu();
		createPanels();
	}

	public void popZavrsno() {
		Frame kraj = new Frame("?");
		Label l1 = new Label("Da li hocete da sacuvate promene?");
		l1.setBounds(50, 50, 300, 20);
		l1.setFont(new Font(l1.getText(), Font.BOLD, 15));
		da = new Button();
		da.setLabel("DA");
		da.setBounds(100, 150, 50, 30);
		da.addActionListener(e -> {
			export = true;
			popupSacuvaj();
			kraj.dispose();
		});
		ne = new Button();
		ne.setLabel("NE");
		ne.setBounds(180, 150, 50, 30);
		ne.addActionListener(e -> {
			kraj.dispose();
			dispose();
		});
		kraj.add(l1);
		kraj.add(da);
		kraj.add(ne);
		kraj.setSize(350, 300);
		kraj.setLayout(null);
		kraj.setVisible(true);
		kraj.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				kraj.dispose();
			}
		});
	}

	void createMenu() {
		MenuBar trakaMenija = new MenuBar();
		Menu prviMeni = new Menu("File");
		Menu drugiMeni = new Menu("Save");
		Menu operacije = new Menu("Operations");
		operacije.add("Add");
		operacije.add("Subtraction");
		operacije.add("InvertedSubtraction");
		operacije.add("Multiplication");
		operacije.add("Divide");
		operacije.add("InvertedDivision");
		operacije.add("Power");
		operacije.add("Log");
		operacije.add("Absolute");
		operacije.add("Minimum");
		operacije.add("Maximum");
		operacije.add("Inversion");
		operacije.add("Grey");
		operacije.add("BlackAndWhite");
		operacije.add("Median");
		operacije.add("Composit operation");
		operacije.addActionListener(this);

		drugiMeni.add("Sacuvaj sliku");
		drugiMeni.addActionListener(this);

		prviMeni.add("Dodaj sloj");
		prviMeni.add("Obrisi sloj");
		prviMeni.add("Promeni vidljivost sloja");
		prviMeni.add("Ubaci sliku");
		prviMeni.add("Napravi selekciju");
		prviMeni.addActionListener(this);

		trakaMenija.add(prviMeni);
		trakaMenija.add(operacije);
		trakaMenija.add(drugiMeni);
		setMenuBar(trakaMenija);
	}

	void createPanels() {
		osnovni = new Panel();
		osnovni.setLayout(new BorderLayout());

		layers = new Panel();
		layers.setBackground(new Color(204, 204, 179));
		Label l = new Label("SLOJEVI:	");
		l.setFont(new Font(l.getText(), Font.BOLD, 25));
		layers.add(l);
		layers.setLayout(new GridLayout(20, 1));

		left = new Panel();
		left.setLayout(new BorderLayout());

		operations = new Panel();
		operations.setLayout(new GridLayout(20, 1));
		Label l1 = new Label("OPERACIJE:	");
		l1.setFont(new Font(l1.getText(), Font.BOLD, 25));
		operations.setBackground(new Color(204, 204, 179));
		operations.add(l1);
		forOperation = new Button();
		forOperation.setLabel("Izvrši");
		forOperation.setFont(new Font(forOperation.getLabel(), Font.BOLD, 15));
		forOperation.addActionListener(e -> {
			promena = true;
			CompositOperation toExport = new CompositOperation("fun.fun");
			for (Operation o : image.getOperations()) {
				toExport.addOperation(o);
			}
			for (Operation o : image.getCompOperations()) {
				toExport.addOperation(o);
			}
			xml.exportComposit(toExport);
			xml.myExport("slika.xml", image);

			String file = "POOPdz.exe slika.xml fun.fun";
			Runtime runtime = Runtime.getRuntime();

			try {
				Process process = runtime.exec(file);
				process.waitFor();

				Image ii = xml.myImport("slika.xml");
				for (int i = 0; i < ii.getImage().size(); i++) {
					image.getImage().remove(0);
					image.addLayer(ii.getImage().get(i));
				}
				left.add(operations, BorderLayout.WEST);
				left.add(selection, BorderLayout.EAST);

				osnovni.add(left, BorderLayout.WEST);
				osnovni.add(layers, BorderLayout.EAST);
				image.repaint();
				// setVisible(true);
				osnovni.add(image, BorderLayout.CENTER);
				// repaint();
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}

		});
		operations.add(forOperation);

		selection = new Panel();
		selection.setLayout(new GridLayout(20, 1));
		Label l2 = new Label("SELEKCIJE:	");
		l2.setFont(new Font(l1.getText(), Font.BOLD, 25));
		selection.add(l2);
		selection.setBackground(new Color(107, 107, 71));

		left.add(operations, BorderLayout.WEST);
		left.add(selection, BorderLayout.EAST);

		osnovni.add(left, BorderLayout.WEST);
		osnovni.add(layers, BorderLayout.EAST);
		osnovni.add(image, BorderLayout.CENTER);

		add(osnovni, BorderLayout.CENTER);

	}

	public Layer addLayer(String nameLayer) {
		Pattern pattPam = Pattern.compile(".+(.pam)");
		Pattern pattBmp = Pattern.compile(".+(.bmp)");

		Matcher mPam = pattPam.matcher(nameLayer);
		boolean isPam = mPam.matches();

		Matcher mBmp = pattBmp.matcher(nameLayer);
		boolean isBmp = mBmp.matches();

		Layer l = null;
		if (isPam)
			l = pam.myImport(nameLayer);
		else if (isBmp)
			l = bmp.myImport(nameLayer);

		return l;
	}

	public static void main(String[] args) {
		Prozor p = new Prozor();
	}

	public void popupFrame() {
		Frame dodaj = new Frame("Dodavanje novog sloja:");
		Label l1 = new Label("Putanja do vaseg sloja:");
		l1.setBounds(50, 70, 200, 30);
		TextField t1 = new TextField();
		t1.setBounds(50, 100, 200, 30);

		Label l2 = new Label("Ime sloja:");
		l2.setBounds(50, 130, 200, 30);
		TextField t2 = new TextField();
		t2.setBounds(50, 160, 200, 30);

		Label l3 = new Label("Vidljivost vaseg sloja:");
		l3.setBounds(50, 190, 200, 30);
		TextField t3 = new TextField();
		t3.setBounds(50, 220, 200, 30);

		napraviLejer = new Button();
		napraviLejer.setLabel("Napravi");
		napraviLejer.setFont(new Font(napraviLejer.getLabel(), Font.BOLD, 15));
		napraviLejer.setBounds(80, 280, 100, 50);
		napraviLejer.addActionListener(e1 -> {
			String path = t1.getText();
			String fileName = t2.getText();
			String transparency = t3.getText();
			Layer l = addLayer(path);
			l.setTransparency(Integer.parseInt(transparency));
			l.setName(path);
			l.setChName(fileName);

			Checkbox ch = new Checkbox(fileName, true);
			Font f = new Font(fileName, Font.BOLD, 20);
			ch.setFont(f);
			ch.addItemListener(this);
			chLayers.put(path, ch);
			layers.add(ch);
			setVisible(true);
			osnovni.add(layers, BorderLayout.EAST);

			image.addLayer(l);
			image.repaint();
			osnovni.add(image, BorderLayout.CENTER);
			dodaj.dispose();
		});

		dodaj.add(l1);
		dodaj.add(t1);
		dodaj.add(l2);
		dodaj.add(t2);
		dodaj.add(l3);
		dodaj.add(t3);
		dodaj.add(napraviLejer);
		dodaj.setSize(400, 400);
		dodaj.setLayout(null);
		dodaj.setVisible(true);
		dodaj.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				dodaj.dispose();
			}
		});
	}

	public void popupDeleteLayer() {
		Frame ukloni = new Frame("Brisanje");
		Label l1 = new Label("Naziv sloja kojeg zelite da obrisete:");
		l1.setBounds(50, 70, 200, 40);
		TextField t1 = new TextField();
		t1.setBounds(50, 110, 200, 30);

		ukloniLejer = new Button();
		ukloniLejer.setLabel("Obrisi");
		ukloniLejer.setFont(new Font(ukloniLejer.getLabel(), Font.BOLD, 15));
		ukloniLejer.setBounds(100, 200, 100, 50);
		ukloniLejer.addActionListener(e1 -> {
			String fileName = t1.getText();
			image.removeLayer(fileName);
			layers.remove(chLayers.get(fileName));
			chLayers.remove(fileName);
			image.repaint();
			ukloni.dispose();
		});

		ukloni.add(l1);
		ukloni.add(t1);
		ukloni.add(ukloniLejer);
		ukloni.setSize(300, 300);
		ukloni.setLayout(null);
		ukloni.setVisible(true);
		ukloni.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				ukloni.dispose();
			}
		});
	}

	public void popupSacuvaj() {
		Frame sacuvaj = new Frame("Cuvanje slike");
		Label l1 = new Label("Naziv vase slike koju zelite da sacuvate:");
		l1.setBounds(40, 70, 220, 40);
		TextField t1 = new TextField();
		t1.setBounds(50, 110, 200, 30);

		sacuvajSliku = new Button();
		sacuvajSliku.setLabel("Save");
		sacuvajSliku.setFont(new Font(sacuvajSliku.getLabel(), Font.BOLD, 15));
		sacuvajSliku.setBounds(100, 200, 100, 50);
		sacuvajSliku.addActionListener(e -> {
			String file = t1.getText();
			Pattern pattPam = Pattern.compile(".+(.pam)");
			Pattern pattBmp = Pattern.compile(".+(.bmp)");
			Pattern pattXml = Pattern.compile(".+(.xml)");

			Matcher mPam = pattPam.matcher(file);
			boolean isPam = mPam.matches();

			Matcher mBmp = pattBmp.matcher(file);
			boolean isBmp = mBmp.matches();

			Matcher mXml = pattXml.matcher(file);
			boolean isXml = mXml.matches();
			if (isPam)
				pam.myExport(file, image);
			else if (isBmp)
				bmp.myExport(file, image);
			else if (isXml)
				xml.myExport(file, image);
			promena = false;
			if (export) {
				sacuvaj.dispose();
				dispose();
			}
			sacuvaj.dispose();
		});
		sacuvaj.add(l1);
		sacuvaj.add(t1);
		sacuvaj.add(sacuvajSliku);
		sacuvaj.setSize(300, 300);
		sacuvaj.setLayout(null);
		sacuvaj.setVisible(true);
		sacuvaj.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				sacuvaj.dispose();
				dispose();
			}
		});
	}

	public void popupSelekcija() {
		Frame selekcija = new Frame("Pravljenje selekcije");
		Label l1 = new Label("Naziv vase selekcije koju zelite da napravite:");
		l1.setBounds(40, 70, 220, 40);
		TextField t1 = new TextField();
		t1.setBounds(50, 110, 200, 30);

		napraviSelekciju = new Button();
		napraviSelekciju.setLabel("Sacuvaj");
		napraviSelekciju.setFont(new Font(napraviSelekciju.getLabel(), Font.BOLD, 15));
		napraviSelekciju.setBounds(100, 200, 100, 50);
		napraviSelekciju.addActionListener(e -> {
			String name = t1.getText();
			Selection s = new Selection(name, true);
			for (int i = 0; i < image.getTempRect().size(); i++) {
				s.addRectangle(image.getTempRect().get(i));
			}
			image.getSelection_map().put(name, s);
			s.setPocetak(image.getBeg());
			s.setKraj(image.getbrLine());

			ArrayList<Line> ll = new ArrayList<Line>();
			for (int i = s.getPocetak(); i < s.getKraj(); i++) {
				ll.add(image.getLines().get(i));
			}

			image.getLine_map().put(s, ll);

			image.setBeg(image.getbrLine());

			for (int i = 0; i < image.getTempRect().size(); i++) {
				image.getTempRect().remove(i);
			}

			Checkbox ch = new Checkbox(name, true);
			Font f = new Font(name, Font.BOLD, 20);
			ch.setFont(f);
			ch.addItemListener(this);
			chSelections.put(ch.getLabel(), ch);
			selection.add(ch);
			setVisible(true);
			left.add(selection, BorderLayout.EAST);

			osnovni.add(left, BorderLayout.WEST);
			selekcija.dispose();
		});
		selekcija.add(l1);
		selekcija.add(t1);
		selekcija.add(napraviSelekciju);
		selekcija.setSize(300, 300);
		selekcija.setLayout(null);
		selekcija.setVisible(true);
		selekcija.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				selekcija.dispose();
			}
		});
	}

	public void popupOperacijaSaKonstantom(String op) {
		Frame f = new Frame("Upis konstante");
		Label l1 = new Label("Upisite konstantu sa kojom zelite da izvrsite operaciju");
		l1.setBounds(40, 60, 300, 50);
		TextField t1 = new TextField();
		t1.setBounds(80, 110, 200, 30);

		konst = new Button();
		konst.setLabel("Izvrsi");
		konst.setFont(new Font(konst.getLabel(), Font.BOLD, 15));
		konst.setBounds(130, 200, 100, 50);
		konst.addActionListener(e -> {
			String c = t1.getText();
			BasicOperation o = new BasicOperation(op, Integer.parseInt(c));
			image.addOperation(o);

			Checkbox ch = new Checkbox(o.getOperation() + c, true);
			ch.setFont(new Font(ch.getLabel(), Font.BOLD, 20));
			ch.addItemListener(this);

			operations.add(ch);
			chOperation.put(ch, o);
			setVisible(true);
			left.add(operations, BorderLayout.WEST);
			osnovni.add(left, BorderLayout.WEST);
			f.dispose();
		});

		f.add(l1);
		f.add(t1);
		f.add(konst);
		f.setSize(380, 300);
		f.setLayout(null);
		f.setVisible(true);
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				f.dispose();
			}
		});
	}

	public void popupComposit() {
		Frame f = new Frame("Pravljenje kompozitne");
		Label l1 = new Label("Ime vase kompozitne:");
		l1.setBounds(50, 70, 200, 30);
		TextField t1 = new TextField();
		t1.setBounds(50, 100, 200, 30);

		Label l2 = new Label("Naziv operacije:");
		l2.setBounds(50, 130, 200, 30);
		TextField t2 = new TextField();
		t2.setBounds(50, 160, 200, 30);

		Label l3 = new Label("konstanta za operaciju:");
		l3.setBounds(50, 190, 200, 30);
		TextField t3 = new TextField();
		t3.setBounds(50, 220, 200, 30);
		CompositOperation temp = new CompositOperation(t1.getText());

		napraviComp = new Button();
		napraviComp.setLabel("Napravi");
		napraviComp.setFont(new Font(napraviComp.getLabel(), Font.BOLD, 15));
		napraviComp.setBounds(200, 250, 100, 30);
		napraviComp.addActionListener(e -> {
			temp.setName(t1.getText());
			for (Operation o : temp.getComp()) {
				nComp.addOperation(o);
			}
			nComp.setName(temp.getName() + ".fun");
			image.addComp(nComp);
			
			Checkbox ch = new Checkbox(nComp.getName(), true);
			ch.setFont(new Font(ch.getLabel(), Font.BOLD, 20));
			ch.addItemListener(this);
			chOperation.put(ch, nComp);
			
			operations.add(ch);
			setVisible(true);
			left.add(operations, BorderLayout.WEST);
			osnovni.add(left, BorderLayout.WEST);

			for (int i = 0; i < temp.getComp().size(); i++) {
				temp.getComp().remove(i);
			}
			f.dispose();
		});

		dodajOp = new Button();
		dodajOp.setLabel("Dodaj");
		dodajOp.setFont(new Font(dodajOp.getLabel(), Font.BOLD, 15));
		dodajOp.setBounds(50, 250, 100, 30);
		dodajOp.addActionListener(e -> {
			String op = t2.getText();
			String c = t3.getText();
			boolean flag = false;
			for (CompositOperation cmp : image.getCompOperations()) {
				if (op.equals(cmp.getName())) {
					temp.addOperation(cmp);
					flag = true;
					break;
				}
			}
			if (!flag) {
				BasicOperation o = new BasicOperation(op, Integer.parseInt(c));
				if (op.equals("Inversion") || op.equals("Grey") || op.equals("BlackAndWhite") || op.equals("Median")) {
					o.setNema(true);
				}
				temp.addOperation(o);
			}
			t2.setText("");
			t3.setText("");
			for (Operation o : temp.getComp()) {
				System.out.println(((BasicOperation) o).getOperation());
			}
		});
		f.add(l1);
		f.add(l2);
		f.add(l3);
		f.add(t1);
		f.add(t2);
		f.add(t3);
		f.add(napraviComp);
		f.add(dodajOp);
		f.setSize(400, 400);
		f.setLayout(null);
		f.setVisible(true);
		f.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				f.dispose();
			}
		});
	}

	public void popupSlika() {
		Frame dodaj = new Frame("Ubacivanje slike:");
		Label l1 = new Label("Putanja do vase slike:");
		l1.setBounds(50, 70, 200, 30);
		TextField t1 = new TextField();
		t1.setBounds(50, 100, 200, 30);
		Label l2 = new Label("Putanja do operacija:");
		l2.setBounds(50, 140, 200, 30);
		TextField t2 = new TextField();
		t2.setBounds(50, 180, 200, 30);

		meni = new Button();
		meni.setLabel("Napravi");
		meni.setFont(new Font(meni.getLabel(), Font.BOLD, 15));
		meni.setBounds(80, 220, 100, 50);
		meni.addActionListener(e -> {
			Image temp = xml.myImport(t1.getText());
			xml.importComposit(temp, t2.getText());
			for (CompositOperation cc : temp.getCompOperations()) {
				image.addComp(cc);
			}
			for (Layer l : temp.getImage()) {
				image.addLayer(l);
				Checkbox ch = new Checkbox(l.getName(), true);
				Font f = new Font(l.getName(), Font.BOLD, 20);
				ch.setFont(f);
				ch.addItemListener(this);
				chLayers.put(ch.getLabel(), ch);
				l.setChName(ch.getLabel());
				layers.add(ch);
				setVisible(true);
				osnovni.add(layers, BorderLayout.EAST);
			}

			for (String s : temp.getSelection_map().keySet()) {
				image.getSelection_map().put(s, temp.getSelection_map().get(s));
				Checkbox ch = new Checkbox(s, true);
				Font f = new Font(s, Font.BOLD, 20);
				ch.setFont(f);
				ch.addItemListener(this);
				chSelections.put(ch.getLabel(), ch);
				selection.add(ch);
				setVisible(true);
				left.add(selection, BorderLayout.EAST);

				osnovni.add(left, BorderLayout.WEST);
			}

			for (BasicOperation o : image.getOperations()) {
				Label l;
				if (o.getOperation().equals("Inversion") || o.getOperation().equals("Grey")
						|| o.getOperation().equals("BlackAndWhite") || o.getOperation().equals("Median")) {
					l = new Label(o.getOperation());
				} else
					l = new Label(o.getOperation() + " " + o.getC());
				l.setFont(new Font(l.getText(), Font.BOLD, 15));
				setVisible(true);
				operations.add(l);
				left.add(operations, BorderLayout.WEST);
				osnovni.add(left, BorderLayout.WEST);
			}
			for (CompositOperation o : image.getCompOperations()) {
				Label l = new Label(o.getName());
				l.setFont(new Font(l.getText(), Font.BOLD, 15));
				operations.add(l);
				setVisible(true);
				left.add(operations, BorderLayout.WEST);
				osnovni.add(left, BorderLayout.WEST);
			}
			image.repaint();
			osnovni.add(image, BorderLayout.CENTER);
			dodaj.dispose();
		});
		dodaj.add(l1);
		dodaj.add(t1);
		dodaj.add(l2);
		dodaj.add(t2);
		dodaj.add(meni);
		dodaj.setSize(380, 300);
		dodaj.setLayout(null);
		dodaj.setVisible(true);
		dodaj.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent we) {
				dodaj.dispose();
			}
		});
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String komanda = e.getActionCommand();
		if (komanda.equals("Dodaj sloj")) {
			popupFrame();
		}
		if (komanda.equals("Obrisi sloj")) {
			popupDeleteLayer();
		}
		if (komanda.equals("Sacuvaj sliku")) {
			popupSacuvaj();
		}
		if (komanda.equals("Napravi selekciju")) {
			popupSelekcija();
		}
		if (komanda.equals("Add") || komanda.equals("Subtraction") || komanda.equals("InvertedSubtraction")
				|| komanda.equals("Multiplication") || komanda.equals("Divide") || komanda.equals("InvertedDivision")
				|| komanda.equals("Power") || komanda.equals("Log") || komanda.equals("Absolute")
				|| komanda.equals("Minimum") || komanda.equals("Maximum")) {
			popupOperacijaSaKonstantom(komanda);
		}
		if (komanda.equals("Inversion") || komanda.equals("Grey") || komanda.equals("BlackAndWhite")
				|| komanda.equals("Median")) {
			BasicOperation o = new BasicOperation(komanda, 0);
			image.addOperation(o);
			
			Checkbox ch = new Checkbox(o.getOperation(), true);
			ch.setFont(new Font(ch.getLabel(), Font.BOLD, 20));
			ch.addItemListener(this);
			chOperation.put(ch, o);
			operations.add(ch);
			setVisible(true);
			left.add(operations, BorderLayout.WEST);
			osnovni.add(left, BorderLayout.WEST);
		}
		if (komanda.equals("Composit operation")) {
			popupComposit();
		}
		if (komanda.equals("Ubaci sliku")) {
			popupSlika();
		}
		if (komanda.equals("Promeni vidljivost sloja")) {
			Frame f = new Frame("Menjanje vidljivosti");
			Label l = new Label("Unesite ime sloja ciju vidljivost zelite da promenite");
			l.setBounds(20, 50, 400, 20);
			TextField t = new TextField();
			t.setBounds(20, 80, 200, 20);

			Label l1 = new Label("Unesite vidljivost");
			l1.setBounds(20, 110, 200, 20);
			TextField t1 = new TextField();
			t1.setBounds(20, 140, 200, 20);
			Button ok = new Button();
			ok.setLabel("OK");
			ok.setBounds(20, 180, 50, 30);
			ok.addActionListener(ee -> {
				for (Layer lay : image.getImage()) {
					if (lay.getChName().equals(t.getText())) {
						lay.setTransparency(Integer.parseInt(t1.getText()));
					}
				}
				image.repaint();
				osnovni.add(image, BorderLayout.CENTER);
				f.dispose();
			});
			f.add(l);
			f.add(t);
			f.add(l1);
			f.add(t1);
			f.add(ok);
			f.setSize(400, 300);
			f.setLayout(null);
			f.setVisible(true);
			f.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent we) {
					f.dispose();
				}
			});
		}

	}

	public void itemStateChanged(ItemEvent e) {
		if (!image.getImage().isEmpty()) {
			Checkbox change = (Checkbox) e.getSource();
			for (Layer l : image.getImage()) {
				if (l.getChName().equals(change.getLabel())) {
					if (!change.getState()) {
						l.setActive(false);
						l.setVisible(false);
					} else {
						l.setActive(true);
						l.setVisible(true);
					}
					osnovni.add(image, BorderLayout.CENTER);
					image.repaint();
				}
			}
			for (String s : image.getSelection_map().keySet()) {
				if (s.equals(change.getLabel())) {
					if (!change.getState()) {
						image.getSelection_map().get(s).setActive(false);
						osnovni.add(image, BorderLayout.CENTER);
						image.repaint();
					} else {
						image.getSelection_map().get(s).setActive(true);
						osnovni.add(image, BorderLayout.CENTER);
						image.repaint();
					}
				}
			}
			Operation op = chOperation.get(change);
			if (op != null) {
				if (!change.getState()) {
					if (op instanceof BasicOperation) {
						for (int i = 0; i < image.getOperations().size(); i++) {
							if (((BasicOperation) op).getOperation().equals(image.getOperations().get(i).getOperation())) {
								image.getOperations().remove(i);
							}
						}
					} else {
						for (int i = 0; i < image.getOperations().size(); i++) {
							if (((CompositOperation) op).getComp().equals(image.getCompOperations().get(i).getComp())) {
								image.getCompOperations().remove(i);
							}
						}
					}
				}
				else {
					if (op instanceof BasicOperation) {
						image.getOperations().add((BasicOperation)op);
					} else {			
						image.getCompOperations().add((CompositOperation)op);
					}
				}
			}

		}

	}
}
