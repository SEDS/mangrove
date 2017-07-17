package edu.umd.cs.mangrove.smutator;

import javassist.ClassClassPath;
import javassist.ClassPool;
import javassist.CtClass;
import javassist.CtMethod;
import javassist.NotFoundException;
import javassist.bytecode.BadBytecode;
import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

public class ByteCodeParserTest extends TestCase {

	public ByteCodeParserTest(String testName) {
		super(testName);
	}

	public static Test suite() {
		return new TestSuite(ByteCodeParserTest.class);
	}

	public void testParser() throws NotFoundException, BadBytecode {

		MutateOwasp myApp = new MutateOwasp();
		ClassPool pool = ClassPool.getDefault();
		ClassClassPath ccpath = new ClassClassPath(myApp.getClass());
		pool.insertClassPath(ccpath);
		CtClass ctClass = pool.get("com.mutator.SMutator.Mutator");

		for (CtMethod method : ctClass.getMethods()) {
			Class<? extends CtMethod> class1 = method.getClass();
			String name = method.getName() + " : " + class1.getName();
			System.out.println(name);
		}
	}
}
