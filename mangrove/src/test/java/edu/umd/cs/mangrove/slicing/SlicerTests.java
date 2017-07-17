package edu.umd.cs.mangrove.slicing;

import java.io.IOException;

import com.ibm.wala.util.CancelException;
import com.ibm.wala.util.WalaException;

import junit.framework.TestCase;

public class SlicerTests extends TestCase {

	public void testPDFSlicer() throws IllegalArgumentException, WalaException, CancelException, IOException {
		String[] args = { "-appJar", "/Users/ukoc/.m2/repository/fr/inria/gforge/spoon/spoon-core/5.4.0/spoon-core-5.4.0.jar", 
				"-mainClass", "spoon/Launcher.class",
				"-srcCaller", "Launcher", 
				"-srcCallee", "processArguments", 
				"-dd", "full", 
				"-cd", "none", 
				"-dir", "backward" };
		PDFSlicer.run(args);
	}
}
