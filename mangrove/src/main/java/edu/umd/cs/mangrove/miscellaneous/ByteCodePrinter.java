package edu.umd.cs.mangrove.miscellaneous;

import javassist.ClassPool;
import javassist.CtClass;
import javassist.CtField;
import javassist.CtMethod;
import javassist.NotFoundException;

public class ByteCodePrinter {

	public static void main(String[] args) throws NotFoundException {
		ClassPool classPool=new ClassPool();
		///Users/ukoc/workspace/owasp-1.1/bin/main/java/
		String classname = "org.owasp.benchmark.testcode.BenchmarkTest09682";
		CtClass clazz  = classPool.getCtClass(classname);
		CtField[] fields = clazz.getFields();
		for (CtField ctField : fields) {
			System.out.println(ctField);
		}
		
		CtMethod[] methods = clazz.getMethods();
		for (CtMethod ctMethod : methods) {
			System.out.println(ctMethod);
		}

	}

	public static CtClass getCtClass(String clazz) {
		ClassPool cp = ClassPool.getDefault();
		try {
			return cp.get(clazz);
		} catch (NotFoundException e) {
			throw new RuntimeException(e);
		}
	}
	
	public static CtMethod getMethod(CtClass ctClass, String name) {
		for(CtMethod ctMethod : ctClass.getMethods()) {
			if(ctMethod.getName().equals(name)) {
				return ctMethod;
			}
		}
		throw new RuntimeException("method '" + name + "' not found in class " + ctClass);
	}
}
