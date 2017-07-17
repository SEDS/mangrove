package edu.umd.cs.mangrove.smutator;

import java.io.File;
import java.io.FileNotFoundException;

import edu.umd.cs.mangrove.miscellaneous.MutationProcessor;
import junit.framework.TestCase;
import spoon.compiler.SpoonResourceHelper;
import spoon.support.compiler.jdt.JDTBasedSpoonCompiler;

public class SpoonTests extends TestCase {

	public void testMutation() {
		MutationProcessor mutationProcessor = new MutationProcessor();
		System.out.println(mutationProcessor.toString());
	}

	public void testASTPrint() throws FileNotFoundException {
		JDTBasedSpoonCompiler compiler = new JDTBasedSpoonCompiler(null);
		// TODO factory
		compiler.getFactory().getEnvironment().setLevel("OFF");
		compiler.addInputSource(
				SpoonResourceHelper.createResource(new File("src/test/java/com/mutator/SMutator/AppTest.java")));
		compiler.build();

		// if (factory.Type().getAll().size() != 0)
		// System.out.println(factory.Type().getAll().get(0).toString());
	}
}
