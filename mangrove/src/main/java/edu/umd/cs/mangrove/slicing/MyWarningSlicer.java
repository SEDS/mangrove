package edu.umd.cs.mangrove.slicing;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

import org.eclipse.jdt.core.dom.AST;
import org.eclipse.jdt.core.dom.ASTParser;
import org.eclipse.jdt.core.dom.ASTVisitor;
import org.eclipse.jdt.core.dom.CompilationUnit;
import org.eclipse.jdt.core.dom.MethodDeclaration;

import com.ibm.wala.shrikeCT.InvalidClassFileException;
import com.ibm.wala.util.CancelException;
import com.ibm.wala.util.WalaException;

public class MyWarningSlicer {
	static final Charset utf8 = StandardCharsets.UTF_8;
	static String julietExclusionsFile = "data/JulietSpecificExclusions.txt";
	static String owaspExclusionsFile = "data/OwaspSpecificExclusions.txt";
	static String julietDom = "Ltestcases/CWE89_SQL_Injection/";
	static String owaspDom = "Lorg/owasp/benchmark/testcode/";
	static String julietDir = "/Users/ukoc/workspace/Juliet4J/src/testcases/CWE89_SQL_Injection/";
	static String owaspDir = "/Users/ukoc/workspace/owasp-1.1/src/main/java/org/owasp/benchmark/testcode/";

	public static void owaspSingleRun()
			throws IllegalArgumentException, IOException, CancelException, WalaException, InvalidClassFileException {
		String className = "Lorg/owasp/benchmark/testcode/BenchmarkTest09682";
		String funcDesc = "(Ljavax/servlet/http/HttpServletRequest;Ljavax/servlet/http/HttpServletResponse;)V";
		String exclusionsFile = "data/OwaspSpecificExclusions.txt";
		WarningSlicer slicer = new WarningSlicer("data/owaspdata.txt", Files.readAllLines(Paths.get(exclusionsFile)));
		System.out.println(slicer.sliceOwasp(className, "doPost", funcDesc, "execute", 54));
	}

	public static void julietSingleRun()
			throws IllegalArgumentException, IOException, CancelException, WalaException, InvalidClassFileException {
		String className, funcDesc, functionName, callee, scopeFileName;
		className = "Ltestcases/CWE89_SQL_Injection/s04/CWE89_SQL_Injection__Property_executeBatch_75b";
		// testcases\/CWE89_SQL_Injection\/s01\/(?!(CWE89_SQL_Injection__Property_executeBatch_75)$).*
		funcDesc = "([B)V";
		callee = "addBatch";
		functionName = "goodG2BSink";
		scopeFileName = "data/juliet/CWE89_s04.txt";
		WarningSlicer slicer = new WarningSlicer(scopeFileName, Files.readAllLines(Paths.get(julietExclusionsFile)));
		String sliceJuliet = slicer.sliceJuliet(className, functionName, funcDesc, callee, 164);
		System.out.println(sliceJuliet);
	}

	public static void main(String[] args)
			throws IOException, IllegalArgumentException, CancelException, WalaException, InvalidClassFileException {
		if (args.length >= 1) {
			processWarningOwasp(args[0]);
		} else {
			// julietSingleRun();
			//runExp("/Users/ukoc/mangrove/phase2/lstm/data/java/CWE89JulietStatsBalanced.txt");
			runExp("/Users/ukoc/mangrove/phase2/lstm/data/java/CWE89OwaspStatsAll.txt");
			// owaspSingleRun();
		}
	}

	public static void processWarningOwasp(String warning)
			throws IOException, FileNotFoundException, UnsupportedEncodingException, CancelException, WalaException,
			IllegalArgumentException, InvalidClassFileException {
		List<String> specificExclusions = Files.readAllLines(Paths.get(owaspExclusionsFile), StandardCharsets.UTF_8);
		String scopeFileName = "data/owaspdata.txt";
		String className, callee, exlcusion;
		String[] pair = warning.split(",");
		className = pair[0];
		int lineNumber = Integer.parseInt(pair[1]);
		String[] detail = pair[2].split(" ");
		callee = detail[0].substring(detail[0].indexOf('.') + 1);
		exlcusion = "org\\/owasp\\/benchmark\\/testcode\\/(?!(" + className + "(\\$(\\w*|\\d))*)$).*";
		specificExclusions.add(exlcusion);
		try {
			String[] fNameAndDesc = findEnclosingMethod(lineNumber, owaspDir + className + ".java",
					"Lorg/owasp/benchmark/testcode/");
			WarningSlicer slicer = new WarningSlicer(scopeFileName, specificExclusions);
			System.out.println("className:" + className + ", callee:" + callee + ", function:" + fNameAndDesc[0]
					+ ", desc:" + fNameAndDesc[1] + ", lineNumber:" + lineNumber);
			String sliceJuliet = slicer.sliceOwasp(owaspDom + className, fNameAndDesc[0], fNameAndDesc[1], callee,
					lineNumber);
			printToFile("/Users/ukoc/mangrove/phase2/slices/owasp/" + className + pair[3] + ".txt", sliceJuliet);
		} catch (com.ibm.wala.util.debug.UnimplementedError e) {
			System.err.println(e.getLocalizedMessage());
		} catch (IllegalArgumentException e) {
			System.err.println(e.getLocalizedMessage());
		} finally {
			specificExclusions.remove(exlcusion);
		}
	}

	public static void processWarningJuliet(String warning)
			throws IOException, FileNotFoundException, UnsupportedEncodingException, CancelException, WalaException,
			IllegalArgumentException, InvalidClassFileException {
		List<String> specificExclusions = Files.readAllLines(Paths.get(julietExclusionsFile), StandardCharsets.UTF_8);
		String className, callee, subFolder, exlcusion;
		String[] pair = warning.split(",");
		String filePath = pair[0].substring(0, pair[0].length() - 5);
		int lineNumber = Integer.parseInt(pair[1]);
		String[] subFolderAndClassName = filePath.split("/");
		String[] warningDesc = pair[2].split(" ");
		callee = warningDesc[0].split("\\.")[1];
		subFolder = subFolderAndClassName[0];
		className = subFolderAndClassName[1];
		exlcusion = "testcases\\/CWE89_SQL_Injection\\/" + subFolder + "\\/(?!(" + className + ")$).*";
		boolean isDigit = Character.isDigit(filePath.charAt(filePath.length() - 1));
		if (!isDigit) {
			String substring = className.substring(0, className.length() - 1);
			exlcusion = "testcases\\/CWE89_SQL_Injection\\/" + subFolder + "\\/(?!(" + substring + "\\w(\\$\\w+)*)$).*";
		}
		specificExclusions.add(exlcusion);
		try {
			String[] fNameAndDesc = findEnclosingMethod(lineNumber, julietDir + pair[0],
					"Ltestcases/CWE89_SQL_Injection/" + subFolder + "/");
			String scopeFileName = "data/juliet/CWE89_" + subFolder + ".txt";
			System.out.println("className:" + className + ", callee:" + callee + ", function:" + fNameAndDesc[0]
					+ ", desc:" + fNameAndDesc[1] + ", lineNumber:" + lineNumber);
			WarningSlicer slicer = new WarningSlicer(scopeFileName, specificExclusions);
			String sliceJuliet = slicer.sliceJuliet(julietDom + filePath, fNameAndDesc[0], fNameAndDesc[1], callee,
					lineNumber);
			printToFile("/Users/ukoc/mangrove/phase2/slices/juliet/" + className + pair[3] + ".txt", sliceJuliet);
		} catch (com.ibm.wala.util.debug.UnimplementedError e) {
			System.err.println(e.getLocalizedMessage());
		} catch (IllegalArgumentException e) {
			System.err.println(e.getLocalizedMessage());
		} finally {
			specificExclusions.remove(exlcusion);
		}
	}

	public static void printToFile(String fName, String slice) throws FileNotFoundException {
		PrintWriter writer = new PrintWriter(fName);
		writer.print(slice);
		writer.flush();
		writer.close();
	}

	public static void runExp(String warningFile)
			throws IOException, FileNotFoundException, UnsupportedEncodingException, CancelException, WalaException,
			IllegalArgumentException, InvalidClassFileException {
		List<String> warnings = Files.readAllLines(Paths.get(warningFile), utf8);
		for (String warning : warnings) {
			processWarningOwasp(warning);
			//processWarningJuliet(warning);
		}
	}

	public static String[] findEnclosingMethod(int lineNumber, String fileName, String subFolder) throws IOException {
		List<String> statements = Files.readAllLines(Paths.get(fileName), utf8);
		String prog = String.join("\n", statements);
		ASTParser astParser = ASTParser.newParser(AST.JLS8);
		astParser.setSource(prog.toCharArray());
		astParser.setKind(ASTParser.K_COMPILATION_UNIT);
		CompilationUnit cu = (CompilationUnit) (astParser.createAST(null));
		MethodExtractor astVisitor = new MethodExtractor(cu, lineNumber, subFolder);
		cu.accept(astVisitor);
		String[] rslt = { astVisitor.enclosingFunction, astVisitor.fDescription };
		return rslt;
	}
}

class MethodExtractor extends ASTVisitor {
	CompilationUnit cu;
	int warningLine;
	String enclosingFunction = null;
	String fDescription = null;
	String localTypesPrefix;

	public MethodExtractor(CompilationUnit cu, int warningLine, String localTypesPrefix) {
		this.cu = cu;
		this.warningLine = warningLine;
		this.localTypesPrefix = localTypesPrefix;
	}

	public boolean visit(MethodDeclaration node) {
		if (enclosingFunction != null) {
			return true;
		}
		int startPosition = node.getStartPosition();
		int startLineNumber = cu.getLineNumber(startPosition);
		int length = node.getLength();
		int endLineNumber = cu.getLineNumber(startPosition + length);
		if (startLineNumber < warningLine && endLineNumber > warningLine) {
			String identifier = node.getName().getIdentifier();
			enclosingFunction = identifier;
			String params = "";
			// System.out.println(identifier + ":");
			for (Object param : node.parameters()) {
				System.out.println("\t " + param);
				String[] paramTypeName = param.toString().split(" ");
				if (paramTypeName[0].contains("HttpServletRequest")) {
					params += "Ljavax/servlet/http/HttpServletRequest;";
				} else if (paramTypeName[0].contains("HttpServletResponse")) {
					params += "Ljavax/servlet/http/HttpServletResponse;";
				} else if (paramTypeName[0].contains("LinkedList")) {
					params += "Ljava/util/LinkedList;";
				} else if (paramTypeName[0].contains("Vector")) {
					params += "Ljava/util/Vector;";
				} else if (paramTypeName[0].contains("HashMap")) {
					params += "Ljava/util/HashMap;";
				} else if (paramTypeName[0].contains("Container")) {
					params += localTypesPrefix + paramTypeName[0].replace('.', '$') + ";";
				} else if (paramTypeName[0].equals("String")) {
					params += paramTypeName[1].contains("[]") ? "[Ljava/lang/String;" : "Ljava/lang/String;";
				} else if (paramTypeName[0].equals("Object")) {
					params += "Ljava/lang/Object;";
				} else if (paramTypeName[0].contains("byte")) {
					params += "[B";
				}
			}
			fDescription = "(" + params + ")V";
		}
		return true;
	}
}