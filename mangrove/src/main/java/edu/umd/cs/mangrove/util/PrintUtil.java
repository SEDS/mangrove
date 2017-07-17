package edu.umd.cs.mangrove.util;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

import com.github.javaparser.ast.CompilationUnit;

public class PrintUtil {

	public static String postprocess(CompilationUnit cu) {
		String reducedCode = cu.toString();
		reducedCode = reducedCode.replaceAll("throws \\w+(,\\s\\w+\\s)?", "");
		reducedCode = reducedCode.replaceAll("try \\{", "\\{");
		reducedCode = reducedCode.replaceAll("/\\*\\*\\*/\n", "");
		reducedCode = reducedCode.replaceAll("/\\*\\*/\n", "");
		reducedCode = reducedCode.replaceAll("\\s*//(\\s\\w+)*\\s?\n", "\n");
		reducedCode = reducedCode.replaceAll("\\s\\.", " ");
		reducedCode = reducedCode.replaceAll("\\(\\.", "(");
		reducedCode = reducedCode.replaceAll("injectableMethod\\(\\)", "injectableMethod(paramTaint)");
		reducedCode = reducedCode.replaceAll("\\=\\.", "=");
		reducedCode = reducedCode.replaceAll("\n", " ");
		reducedCode = reducedCode.replaceAll("    ", " ");
		reducedCode = reducedCode.replaceAll("   ", " ");
		reducedCode = reducedCode.replaceAll("  ", " ");
		return reducedCode.replaceAll("  ", " ");
	}

	public static void printToFile(String fileName, String str) throws FileNotFoundException {
		PrintWriter printWriter = new PrintWriter(new File(fileName));
		printWriter.print(str);
		printWriter.close();
	}
}