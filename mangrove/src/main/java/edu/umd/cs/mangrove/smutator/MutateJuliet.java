package edu.umd.cs.mangrove.smutator;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.eclipse.jdt.core.dom.AST;
import org.eclipse.jdt.core.dom.ASTParser;
import org.eclipse.jdt.core.dom.ASTVisitor;
import org.eclipse.jdt.core.dom.CompilationUnit;
import org.eclipse.jdt.core.dom.MethodDeclaration;

public class MutateJuliet {
	public static String warningStats = "/Users/ukoc/mangroveL/sa-lstm/data/java/CWE89JulietStatsBalanced.txt";
	public static String julietDir = "/Users/ukoc/workspace/Juliet4J/src/testcases/CWE89_SQL_Injection/";
	public static String mutantDir = "/Users/ukoc/workspace/Juliet4J/mutants/";

	public void createMutants() {
		try {
			List<String> warnings = Files.readAllLines(Paths.get(warningStats), StandardCharsets.UTF_8);
			for (String warning : warnings) {
				// System.out.print(warning + ",");
				String[] pair = warning.split(",");
				Mutator mutator = new Mutator(mutantDir);
				int lineNumber = Integer.parseInt(pair[1]);
				mutator.mutateFunction(julietDir + pair[0], lineNumber, pair[3], pair[2]);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		MutateJuliet julietHandler = new MutateJuliet();
		julietHandler.createMutants();
	}

	public void printDP(String mutantFile, int warningLine, String label) throws IOException {
		String prog = new String(Files.readAllBytes(Paths.get(mutantFile)), StandardCharsets.UTF_8);
		CompilationUnit cu = getCompilationUnit(prog);
		MyAstFlatten astVisitor = new MyAstFlatten(cu, label, warningLine);
		cu.accept(astVisitor);

		// System.out.println(cu.toString());
	}

	public CompilationUnit getCompilationUnit(String source) {
		ASTParser astParser = ASTParser.newParser(AST.JLS8);
		astParser.setSource(source.toCharArray());
		astParser.setKind(ASTParser.K_COMPILATION_UNIT);
		CompilationUnit result = (CompilationUnit) (astParser.createAST(null));
		return result;
	}
}

class MyAstFlatten extends ASTVisitor {
	List<Integer> indexes = new ArrayList<Integer>();
	CompilationUnit cu;
	HashMap<Integer, Integer> functionPositions = new HashMap<Integer, Integer>();
	String label;
	int warningLine;

	public MyAstFlatten(CompilationUnit cu, String label, int warningLine) {
		this.cu = cu;
		this.warningLine = warningLine;
		this.label = label;
	}

	public boolean visit(MethodDeclaration node) {
		int startPosition = node.getStartPosition();
		int length = node.getLength();
		int startLineNumber = cu.getLineNumber(startPosition);
		int endLineNumber = cu.getLineNumber(startPosition + length);
		if (!node.getName().getIdentifier().contains(label)) {
			System.out.println(node.toString());
		}

		functionPositions.put(startLineNumber, endLineNumber);
		indexes.add(startLineNumber);
		return true;
	}
}