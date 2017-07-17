package edu.umd.cs.mangrove.util;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class BugReportUtil {
	private static Pattern p = Pattern.compile("(U|S|T)(\\d+)");

	public static void main(String[] args) throws IOException, ParserConfigurationException, SAXException {
		String report = "/Users/ukoc/mangrove/findsecbugs/reports_owasp/09682TP.xml";
		parseXML(report);
	}

	public static BugReport parseXML(String filePath) throws IOException, ParserConfigurationException, SAXException {
		return parseXML(new File(filePath));
	}

	public static BugReport parseXML(File fXmlFile) throws IOException, ParserConfigurationException, SAXException {
		boolean isFP = fXmlFile.getName().endsWith("gP.xml") | fXmlFile.getName().endsWith("FP.xml");
		BugReport bugReport = new BugReport(new ArrayList<Integer>());
		DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
		DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
		org.w3c.dom.Document doc = dBuilder.parse(fXmlFile);
		doc.getDocumentElement().normalize();

		Node bugInstNode = null;
		NodeList methods = doc.getElementsByTagName("Method");
		for (int i = 0; i < methods.getLength(); i++) {
			if (methods.item(i).getNodeType() == Node.ELEMENT_NODE) {
				org.w3c.dom.Element m = (org.w3c.dom.Element) methods.item(i);
				String name = m.getAttribute("name");
				if ((isFP && !name.contains("bad")) || (!isFP && !name.contains("good"))) {
					bugInstNode = methods.item(i).getParentNode();
					bugReport.methodName = name;
					Node methodSourceLine = m.getElementsByTagName("SourceLine").item(0);
					bugReport.className = ((org.w3c.dom.Element) methodSourceLine).getAttribute("sourcefile");
					break;
				}
			}
		}
		if (bugInstNode == null) return null;

		org.w3c.dom.Element bugInstElement = (org.w3c.dom.Element) bugInstNode;
		bugReport.bugType = bugInstElement.getAttribute("type");
		NodeList childNodes = bugInstNode.getChildNodes();
		HashMap<Integer, String> localVariables = new HashMap<Integer, String>();
		for (int j = 0; j < childNodes.getLength(); j++) {
			if (childNodes.item(j).getNodeType() == Node.ELEMENT_NODE) {
				org.w3c.dom.Element item = (org.w3c.dom.Element) childNodes.item(j);
				if (item.getTagName().equals("SourceLine")) {
					int lineNumber = Integer.parseInt(item.getAttribute("start"));
					if (!bugReport.linenumbers.contains(lineNumber)) {
						bugReport.linenumbers.add(lineNumber);
					}
				} else if (item.getTagName().equals("String")) {
					String role = item.getAttribute("role");
					String name = item.getAttribute("value");
					if (role.equals("Parameter Taint") && name.length() > 0) {
						bugReport.paramTaint = name.substring(0, name.contains(" ") ? name.indexOf(' ') : 1);
					} else if (role.equals("Taint Frame") && name.length() > 0) {
						Matcher m = p.matcher(name.split("\\|")[0]);
						while (m.find())
							localVariables.put(Integer.parseInt(m.group(2)), m.group(1));
					} else if (role.equals("Sink method")) {
						bugReport.injectableMethod = name.substring(name.indexOf('.') + 1, name.indexOf('('));
					} else if (role.equals("Method Bytecode")) {
						String[] variables = name.split("LocalVariable");
						for (int i = 1; i < variables.length; i++) {
							String var = variables[i].substring(1, variables[i].indexOf(')'));
							//String[] split = var.split(" ");
							int index = Integer.parseInt(var.substring(var.indexOf("index = ") + 8, var.indexOf(":")));
							if (!bugReport.taintFrame.containsKey(index))
								bugReport.taintFrame.put(localVariables.get(index) + index, var);
						}
					}
				}
			}
		}
		String vardetail = bugReport.taintFrame.get(bugReport.paramTaint);
		if (vardetail != null) {
			bugReport.paramTaint = vardetail.replaceAll(".*, index = \\d:.*\\s", "");
		} else {

		}
		Collections.sort(bugReport.linenumbers);
		// System.out.println(bugReport);
		return bugReport;
	}

	public static BugReport parseHTML_old(String filePath) throws IOException {
		File input = new File(filePath);
		Document doc = Jsoup.parse(input, "UTF-8", "http://example.com/");
		Element extraElement = doc.getElementsMatchingOwnText("Extra").first();
		String ownText = extraElement.ownText();
		String debuginfo = ownText.substring(ownText.indexOf("Extra") + 6);
		String[] reportParts = debuginfo.split(" At ");
		BugReport bugReport = new BugReport(new ArrayList<Integer>());

		for (int i = 1; i < reportParts.length; i++) {
			String lineNumberStr = reportParts[i].substring(reportParts[i].indexOf("line ") + 5,
					reportParts[i].indexOf("]"));
			bugReport.linenumbers.add(Integer.parseInt(lineNumberStr));
		}
		String val = null;
		String[] pairs = reportParts[0].split(",");
		for (String pair : pairs) {
			if (pair.contains("injectableMethod")) {
				val = pair.split(":")[1];
				bugReport.injectableMethod = val.substring(val.indexOf('.') + 1, val.length() - 5);
			} else if (pair.contains("bugType")) {
				bugReport.bugType = pair.split(":")[1];
			} else if (pair.contains("sourceLineAt")) {
				val = pair.split(":")[1];
				val = val.substring(val.indexOf(' ') + 1, val.length() - 1);
				bugReport.linenumbers.add(Integer.parseInt(val));
			} else if (pair.contains("currentMethod")) {
				val = pair.split(":")[1];
				bugReport.methodName = val.substring(val.indexOf('.') + 1, val.indexOf('('));
			} else if (pair.contains("parameterTaint")) {
				val = pair.split(":")[1];
				bugReport.paramTaint = val.substring(val.indexOf('.') + 1, val.indexOf(' '));
			}
		}
		System.out.println(bugReport);
		return bugReport;
	}

	public static BugReport parseHTML(String filePath) throws IOException {
		File input = new File(filePath);
		Document doc = Jsoup.parse(input, "UTF-8", "http://example.com/");
		Element extraElement = doc.getElementsMatchingOwnText(filePath.contains("gP.") ? "good" : "bad").first();

		BugReport bugReport = new BugReport(new ArrayList<Integer>());
		String[] lines = extraElement.toString().split("<br>");
		// for (String line : lines) {
		// System.out.println(line);
		// }
		bugReport.bugType = lines[0].substring(lines[0].lastIndexOf("Bug type ") + 9, lines[0].lastIndexOf('(') - 1);
		bugReport.className = lines[1].substring(lines[1].lastIndexOf('.') + 1);
		bugReport.methodName = lines[2].substring(lines[2].lastIndexOf('.') + 1, lines[2].lastIndexOf('('));
		bugReport.injectableMethod = lines[4].substring(lines[4].indexOf('.') + 1, lines[4].lastIndexOf('('));
		bugReport.paramTaint = "U";
		// lines[7].substring(lines[7].lastIndexOf("Parameter Taint") + 16,
		// lines[7].lastIndexOf(' '));
		int lineNumber;
		for (int i = 9; i < lines.length; i++) {
			if (lines[i].contains("[line ")) {
				lineNumber = Integer.parseInt(lines[i].substring(lines[i].lastIndexOf(' ') + 1, lines[i].lastIndexOf(']')));
				bugReport.linenumbers.add(lineNumber);
			}
		}
		lineNumber = Integer.parseInt(lines[3].substring(lines[3].lastIndexOf(' ') + 1, lines[3].lastIndexOf(']')));
		bugReport.linenumbers.add(lineNumber);
		// System.out.println(bugReport);
		return bugReport;
	}

	static BugReport example1() {
		int priority = 3;
		int confidence = 5;
		int severity = 5;
		String bugType = "SQL_INJECTION_JDBC";
		String warningMethod = "doPost";
		String injectableMethod = "prepareStatement";
		String taintParam = "sql";
		HashMap<String, String> taintFrame = new HashMap<String, String>();
		String[] tf = { "U0,[2] {?}", "U1,[1](U) {[?]+[?]}", "U2,[0] {?}", "U3, {&lt;init&gt;()}", "U4, {getTheValue()}",
				"U5, {toString()}", "U6, {getSqlConnection()}", "U7, {?}|", "U6, {getSqlConnection()}", "U5, {toString()}",
				"S, {?}", "S, {?}", "S, {2}" };
		for (String pair : tf) {
			String keyvalue[] = pair.split(",");
			taintFrame.put(keyvalue[0], keyvalue[1]);
		}
		ArrayList<Integer> linenumbers = new ArrayList<Integer>();
		linenumbers.add(44);
		linenumbers.add(47);
		linenumbers.add(51);
		ArrayList<String> injectableArgs = null;
		return new BugReport(priority, confidence, severity, bugType, "fileName", warningMethod, injectableMethod,
				taintParam, taintFrame, linenumbers, injectableArgs);
	}

	static BugReport example2() {
		int priority = 3;
		int confidence = 5;
		int severity = 5;
		String bugType = "SQL_INJECTION_JDBC";
		String warningMethod = "doPost";
		String injectableMethod = "prepareCall";
		String taintParam = "sql";
		HashMap<String, String> taintFrame = new HashMap<String, String>();
		String[] tf = { "U0,[2] {?}", "U1,[1](U) {[?]+[?]}", "U2,[0] {?}", "U3, {&lt;init&gt;()}", "U4, {getTheValue()}",
				"U5, {toString()}", "U6, {getSqlConnection()}", "U7, {?}|", "U6, {getSqlConnection()}", "U5, {toString()}",
				"S, {?}", "S, {?}", "S, {2}" };
		for (String pair : tf) {
			String keyvalue[] = pair.split(",");
			taintFrame.put(keyvalue[0], keyvalue[1]);
		}
		ArrayList<Integer> linenumbers = new ArrayList<Integer>();
		linenumbers.add(49);
		linenumbers.add(62);
		linenumbers.add(64);
		linenumbers.add(68);
		ArrayList<String> injectableArgs = null;
		return new BugReport(priority, confidence, severity, bugType, "fileName", warningMethod, injectableMethod,
				taintParam, taintFrame, linenumbers, injectableArgs);
	}

	static BugReport example3() {
		int priority = 3;
		int confidence = 5;
		int severity = 5;
		String bugType = "SQL_INJECTION_JDBC";
		String warningMethod = "doPost";
		String injectableMethod = "prepareCall";
		String taintParam = "sql";
		HashMap<String, String> taintFrame = new HashMap<String, String>();
		String[] tf = { "U0,[2] {?}", "U1,[1](U) {[?]+[?]}", "U2,[0] {?}", "U3, {&lt;init&gt;()}", "U4, {getTheValue()}",
				"U5, {toString()}", "U6, {getSqlConnection()}", "U7, {?}|", "U6, {getSqlConnection()}", "U5, {toString()}",
				"S, {?}", "S, {?}", "S, {2}" };
		for (String pair : tf) {
			String keyvalue[] = pair.split(",");
			taintFrame.put(keyvalue[0], keyvalue[1]);
		}
		ArrayList<Integer> linenumbers = new ArrayList<Integer>();
		linenumbers.add(42);
		linenumbers.add(44);
		linenumbers.add(46);
		linenumbers.add(50);
		ArrayList<String> injectableArgs = null;
		return new BugReport(priority, confidence, severity, bugType, "fileName", warningMethod, injectableMethod,
				taintParam, taintFrame, linenumbers, injectableArgs);
	}

	static BugReport example4() {
		int priority = 3;
		int confidence = 5;
		int severity = 5;
		String bugType = "SQL_INJECTION_JDBC";
		String warningMethod = "doPost";
		String injectableMethod = "prepareCall";
		String taintParam = "sql";
		HashMap<String, String> taintFrame = new HashMap<String, String>();
		String[] tf = { "U0,[2] {?}", "U1,[1](U) {[?]+[?]}", "U2,[0] {?}", "U3, {&lt;init&gt;()}", "U4, {getTheValue()}",
				"U5, {toString()}", "U6, {getSqlConnection()}", "U7, {?}|", "U6, {getSqlConnection()}", "U5, {toString()}",
				"S, {?}", "S, {?}", "S, {2}" };
		for (String pair : tf) {
			String keyvalue[] = pair.split(",");
			taintFrame.put(keyvalue[0], keyvalue[1]);
		}
		ArrayList<Integer> linenumbers = new ArrayList<Integer>();
		linenumbers.add(64);
		linenumbers.add(67);
		linenumbers.add(71);
		ArrayList<String> injectableArgs = null;
		return new BugReport(priority, confidence, severity, bugType, "fileName", warningMethod, injectableMethod,
				taintParam, taintFrame, linenumbers, injectableArgs);
	}

	static BugReport example5() {
		int priority = 3;
		int confidence = 5;
		int severity = 5;
		String bugType = "SQL_INJECTION_JDBC";
		String warningMethod = "doPost";
		String injectableMethod = "prepareCall";
		String taintParam = "sql";
		HashMap<String, String> taintFrame = new HashMap<String, String>();
		String[] tf = { "U0,[2] {?}", "U1,[1](U) {[?]+[?]}", "U2,[0] {?}", "U3, {&lt;init&gt;()}", "U4, {getTheValue()}",
				"U5, {toString()}", "U6, {getSqlConnection()}", "U7, {?}|", "U6, {getSqlConnection()}", "U5, {toString()}",
				"S, {?}", "S, {?}", "S, {2}" };
		for (String pair : tf) {
			String keyvalue[] = pair.split(",");
			taintFrame.put(keyvalue[0], keyvalue[1]);
		}
		ArrayList<Integer> linenumbers = new ArrayList<Integer>();
		linenumbers.add(64);
		linenumbers.add(67);
		linenumbers.add(71);
		ArrayList<String> injectableArgs = null;
		return new BugReport(priority, confidence, severity, bugType, "fileName", warningMethod, injectableMethod,
				taintParam, taintFrame, linenumbers, injectableArgs);
	}
}
