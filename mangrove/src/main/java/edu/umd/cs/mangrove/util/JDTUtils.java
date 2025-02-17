package edu.umd.cs.mangrove.util;

import java.util.HashSet;

import org.eclipse.core.runtime.NullProgressMonitor;
import org.eclipse.jdt.core.IJavaElement;
import org.eclipse.jdt.core.IMember;
import org.eclipse.jdt.core.IMethod;
import org.eclipse.jdt.internal.corext.callhierarchy.CallHierarchy;
import org.eclipse.jdt.internal.corext.callhierarchy.MethodWrapper;

public class JDTUtils {

	public static HashSet<IMethod> getCallersOf(IMethod m) {

		CallHierarchy callHierarchy = CallHierarchy.getDefault();

		MethodWrapper methodWrappers = callHierarchy.getCallerRoot(m);
		HashSet<IMethod> callers = new HashSet<IMethod>();
		MethodWrapper[] mw2 = methodWrappers.getCalls(new NullProgressMonitor());
		HashSet<IMethod> temp = getIMethods(mw2);
		callers.addAll(temp);

		return callers;
	}

	static HashSet<IMethod> getIMethods(MethodWrapper[] methodWrappers) {
		HashSet<IMethod> c = new HashSet<IMethod>();
		for (MethodWrapper m : methodWrappers) {
			IMethod im = getIMethodFromMethodWrapper(m);
			if (im != null) {
				c.add(im);
			}
		}
		return c;
	}

	static IMethod getIMethodFromMethodWrapper(MethodWrapper m) {
		try {
			IMember im = m.getMember();
			if (im.getElementType() == IJavaElement.METHOD) { return (IMethod) m.getMember(); }
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
}
