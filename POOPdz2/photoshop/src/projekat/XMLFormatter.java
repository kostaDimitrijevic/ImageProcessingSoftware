package projekat;

import org.w3c.dom.*;
import org.xml.sax.SAXException;

import gui.Prozor;

import javax.xml.parsers.*;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import java.io.*;
import java.util.ArrayList;

public class XMLFormatter {
	public CompositOperation importComposit(Image im, String file) {
		CompositOperation temp = new CompositOperation(file);
		try {		
			DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = factory.newDocumentBuilder();;
			Document doc = dBuilder.parse(file);
			doc.getDocumentElement().normalize();
			
			Element root = doc.getDocumentElement();
			NodeList children = root.getChildNodes();
			
			Node comp = children.item(1);
			NodeList fun = comp.getChildNodes();
			int i = 1;
			
			for(Node n = fun.item(i); n!=null; n = fun.item(i)) {
				NamedNodeMap att = n.getAttributes();
				if(n.getNodeName().equals("Add") || n.getNodeName().equals("Subtraction") || n.getNodeName().equals("InvertedSubtraction")
						|| n.getNodeName().equals("Multiplication") || n.getNodeName().equals("Divide") || n.getNodeName().equals("InvertedDivision")
						|| n.getNodeName().equals("Power") || n.getNodeName().equals("Log") || n.getNodeName().equals("Absolute")
						|| n.getNodeName().equals("Minimum") || n.getNodeName().equals("Maximum") || n.getNodeName().equals("Inversion") || n.getNodeName().equals("Grey") || n.getNodeName().equals("BlackAndWhite")
						|| n.getNodeName().equals("Median")) {
					String c = att.getNamedItem("Konstanta").getNodeValue();
					if(c.equals("nema")) {
						BasicOperation o = new BasicOperation(n.getNodeName(), 0);
						o.setNema(false);
						temp.addOperation(o);
					}
					else {
						BasicOperation o = new BasicOperation(n.getNodeName(), Integer.parseInt(c));
						o.setNema(true);
						temp.addOperation(o);
					}
					
				}
				else {				
					//if(im.getCompOperations().isEmpty()) {
					CompositOperation o = importComposit(im, n.getNodeName());
					//}
					//else {
					//	for(CompositOperation co : im.getCompOperations()) {
					//		String name = n.getNodeName();
					//		if(!co.getName().equals(name)) {
					//			CompositOperation o = importComposit(im, n.getNodeName());
						//		temp.addOperation(o);
						//		break;
						//	}
					//	}		
				//	}
				}
				i=i+2;
			}
			im.addComp(temp);
			return temp;
		} catch (ParserConfigurationException | SAXException | IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	
	}

	public void exportComposit(CompositOperation c) {
		try {
			DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = factory.newDocumentBuilder();
			Document doc = dBuilder.newDocument();

			Element root = doc.createElement("Composit");
			doc.appendChild(root);

			Element comp = doc.createElement(c.getName());
			root.appendChild(comp);

			for (Operation o : c.getComp()) {
				if (o instanceof BasicOperation) {
					Element oper = doc.createElement(((BasicOperation) o).getOperation());
					if (((BasicOperation) o).isNema())
						oper.setAttribute("Konstanta", "nema");
					else {
						oper.setAttribute("Konstanta", Integer.toString(((BasicOperation) o).getC()));
					}
					comp.appendChild(oper);
				} else {
					String s = (((CompositOperation) o).getName());
					Element oper = doc.createElement(s);
					oper.setAttribute("Konstanta", "nema");
					comp.appendChild(oper);
					exportComposit((CompositOperation) o);
				}
			}
			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			transformer.setOutputProperty("omit-xml-declaration", "yes");
			transformer.setOutputProperty(OutputKeys.INDENT, "yes");
			transformer.setOutputProperty(OutputKeys.METHOD, "xml");
			transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
			DOMSource domSource = new DOMSource(doc);
			StreamResult streamResult = new StreamResult(new File(c.getName()));
			transformer.transform(domSource, streamResult);

		} catch (ParserConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (TransformerConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (TransformerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public Image myImport(String file) {
		Image i = new Image();
		ArrayList<Layer> layList = new ArrayList<Layer>();
		try {
			DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = factory.newDocumentBuilder();
			Document doc = dBuilder.parse(file);
			doc.getDocumentElement().normalize();
			Element root = doc.getDocumentElement();
			NodeList children = root.getChildNodes();

			Node dimensions = children.item(1);
			NodeList dim = dimensions.getChildNodes();
			Node w = dim.item(1);
			Node h = dim.item(3);
			int width = Integer.parseInt(w.getAttributes().getNamedItem("width").getNodeValue());
			int height = Integer.parseInt(h.getAttributes().getNamedItem("height").getNodeValue());

			Node layer = children.item(3);
			NodeList layers = layer.getChildNodes();
			int j = 1;
			for (Node n = layers.item(j); n != null; n = layers.item(j)) {
				NamedNodeMap atributes = n.getAttributes();
				String layName = atributes.getNamedItem("name").getNodeValue();
				int transparency = Integer.parseInt(atributes.getNamedItem("transparency").getNodeValue());
				boolean active = Boolean.parseBoolean(atributes.getNamedItem("active").getNodeValue());
				int selected = Integer.parseInt(atributes.getNamedItem("selected").getNodeValue());
				boolean visible = Boolean.parseBoolean(atributes.getNamedItem("visible").getNodeValue());

				BMPFormatter f = new BMPFormatter();
				Layer l = f.myImport(layName);
				if(!Prozor.chLayers.isEmpty())
					l.setChName(Prozor.chLayers.get(layName).getLabel());
				l.setName(layName);
				l.setActive(active);
				for (int jj = 0; jj < selected; jj++)
					;
				l.setSelected();
				l.setTransparency(transparency);
				l.setVisible(visible);
				layList.add(l);
				j = j + 2;
			}
			for (Layer l : layList) {
				i.addLayer(l);
			}

			j = 1;
			Node selection = children.item(5);
			NodeList selections = selection.getChildNodes();
			for (Node n = selections.item(j); n != null; n = selections.item(j)) {
				NamedNodeMap atributes = n.getAttributes();
				String name = atributes.getNamedItem("name").getNodeValue();
				boolean active = Boolean.parseBoolean(atributes.getNamedItem("active").getNodeValue());
				NodeList rectangles = n.getChildNodes();
				int k = 1;
				ArrayList<Rectangle> recList = new ArrayList<Rectangle>();
				for (Node m = rectangles.item(k); m != null; m = rectangles.item(k)) {
					NamedNodeMap atr = m.getAttributes();
					int y = Integer.parseInt(atr.getNamedItem("y").getNodeValue());
					int x = Integer.parseInt(atr.getNamedItem("x").getNodeValue());
					int heightR = Integer.parseInt(atr.getNamedItem("height").getNodeValue());
					int widthR = Integer.parseInt(atr.getNamedItem("width").getNodeValue());
					recList.add(new Rectangle(x, y, widthR, heightR));
					k = k + 2;
				}
				i.addSelection(name, new Selection(recList, name, active));
				j = j + 2;
			}
		//	Node comp = children.item(7);
		//	NodeList comps = comp.getChildNodes();
			//j=1;
			//for(Node n = comps.item(j); n!=null; n=comps.item(j)) {
			//	importComposit(i, n.getAttributes().getNamedItem("name").getNodeValue());
			//	j= j+2;
			//}

		} catch (ParserConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SAXException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return i;

	}

	public void myExport(String file, Image i) {
		BMPFormatter bmp = new BMPFormatter();
		PAMFormatter pam = new PAMFormatter();
		try {
			DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = factory.newDocumentBuilder();
			Document doc = dBuilder.newDocument();
			Element root = doc.createElement("Image");
			doc.appendChild(root);

			Element dimensions = doc.createElement("Dimensions");
			root.appendChild(dimensions);

			Element width = doc.createElement("Width");
			Element height = doc.createElement("Height");
			width.setAttribute("width", Integer.toString(i.getWidth()));
			height.setAttribute("height", Integer.toString(i.getHeight()));
			dimensions.appendChild(width);
			dimensions.appendChild(height);

			Element layers = doc.createElement("Layers");
			root.appendChild(layers);
			Image temp = new Image();
			for (int j = 0; j < i.getImage().size(); j++) {
				temp.addLayer(i.getImage().get(j));
				//bmp.myExport(i.getImage().get(j).getName() + ".bmp", temp);
				temp.getImage().remove(0);
				Element layer = doc.createElement("Layer");
				layer.setAttribute("transparency", Integer.toString(i.getImage().get(j).getTransparency()));
				layer.setAttribute("name", i.getImage().get(j).getName());
				layer.setAttribute("active", Boolean.toString(i.getImage().get(j).isActive()));
				layer.setAttribute("selected", Integer.toString(i.getImage().get(j).getSelected()));
				layer.setAttribute("visible", Boolean.toString(i.getImage().get(j).isVisible()));
				layers.appendChild(layer);
			}

			Element selections = doc.createElement("Selections");
			root.appendChild(selections);
			for (String s : i.getSelection_map().keySet()) {
				Element selection = doc.createElement("Selection");
				selections.appendChild(selection);
				selection.setAttribute("name", s);
				selection.setAttribute("active", Boolean.toString(i.getSelection_map().get(s).isActive()));
				for (Rectangle r : i.getSelection_map().get(s).getSelection()) {
					Element rectangle = doc.createElement("Rectangle");
					selection.appendChild(rectangle);
					rectangle.setAttribute("y", Integer.toString(r.getY()));
					rectangle.setAttribute("x", Integer.toString(r.getX()));
					rectangle.setAttribute("height", Integer.toString(r.getHeight()));
					rectangle.setAttribute("width", Integer.toString(r.getWidth()));
				}

			}

			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			transformer.setOutputProperty("omit-xml-declaration", "yes");
			transformer.setOutputProperty(OutputKeys.INDENT, "yes");
			transformer.setOutputProperty(OutputKeys.METHOD, "xml");
			transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
			DOMSource domSource = new DOMSource(doc);
			StreamResult streamResult = new StreamResult(new File(file));
			transformer.transform(domSource, streamResult);
		} catch (ParserConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (TransformerConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (TransformerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
