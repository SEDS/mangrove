package edu.umd.cs.mangrove.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;

public class BugReport {
	int priority;
	int confidence;
	int severity;

	String bugType = null;
	String className = null;
	String methodName = null;
	String methodSignature;
	int lineNumber;
	String injectableMethod = null;
	String paramTaint = null;
	String taintSrc = null;
	HashMap<String, String> taintFrame = null;
	ArrayList<Integer> linenumbers = null;
	ArrayList<String> injectableArgs = null;
	HashMap<String, String> artifacts;
	
	public int getPriority() {
		return priority;
	}

	public void setPriority(int priority) {
		this.priority = priority;
	}

	public int getConfidence() {
		return confidence;
	}

	public void setConfidence(int confidence) {
		this.confidence = confidence;
	}

	public int getSeverity() {
		return severity;
	}

	public void setSeverity(int severity) {
		this.severity = severity;
	}

	public String getBugType() {
		return bugType;
	}

	public void setBugType(String bugType) {
		this.bugType = bugType;
	}

	public String getClassName() {
		return className;
	}

	public void setClassName(String className) {
		this.className = className;
	}

	public String getMethodName() {
		return methodName;
	}

	public void setMethodName(String methodName) {
		this.methodName = methodName;
	}

	public String getMethodSignature() {
		return methodSignature;
	}

	public void setMethodSignature(String methodSignature) {
		this.methodSignature = methodSignature;
	}

	public int getLineNumber() {
		return lineNumber;
	}

	public void setLineNumber(int lineNumber) {
		this.lineNumber = lineNumber;
	}

	public String getInjectableMethod() {
		return injectableMethod;
	}

	public void setInjectableMethod(String injectableMethod) {
		this.injectableMethod = injectableMethod;
	}

	public String getParamTaint() {
		return paramTaint;
	}

	public void setParamTaint(String paramTaint) {
		this.paramTaint = paramTaint;
	}

	public String getTaintSrc() {
		return taintSrc;
	}

	public void setTaintSrc(String taintSrc) {
		this.taintSrc = taintSrc;
	}

	public HashMap<String, String> getTaintFrame() {
		return taintFrame;
	}

	public void setTaintFrame(HashMap<String, String> taintFrame) {
		this.taintFrame = taintFrame;
	}

	public ArrayList<Integer> getLinenumbers() {
		return linenumbers;
	}

	public void setLinenumbers(ArrayList<Integer> linenumbers) {
		this.linenumbers = linenumbers;
	}

	public ArrayList<String> getInjectableArgs() {
		return injectableArgs;
	}

	public void setInjectableArgs(ArrayList<String> injectableArgs) {
		this.injectableArgs = injectableArgs;
	}

	public HashMap<String, String> getArtifacts() {
		return artifacts;
	}

	public void setArtifacts(HashMap<String, String> artifacts) {
		this.artifacts = artifacts;
	}

	public BugReport(String bugType) {
		super();
		this.bugType = bugType;
		this.className = null;
		this.methodName = null;
		this.methodSignature = null;
		this.lineNumber = -1;
		artifacts = new HashMap<String, String>();
	}

	public BugReport(String bugType, String className, String methodName, String methodSignature, int lineNumber) {
		super();
		this.bugType = bugType;
		this.className = className;
		this.methodName = methodName;
		this.methodSignature = methodSignature;
		this.lineNumber = lineNumber;
		artifacts = new HashMap<String, String>();
	}

	public BugReport(int priority, int confidence, int severity, String bugType, String fileName, String warningMethod,
			String injectableMethod, String taintParam, HashMap<String, String> taintFrame, ArrayList<Integer> linenumbers,
			ArrayList<String> injectableArgs) {
		super();
		this.priority = priority;
		this.confidence = confidence;
		this.severity = severity;
		this.bugType = bugType;
		this.methodName = warningMethod;
		this.injectableMethod = injectableMethod;
		this.paramTaint = taintParam;
		this.taintFrame = taintFrame;
		this.linenumbers = linenumbers;
		this.injectableArgs = injectableArgs;
	}

	public BugReport(ArrayList<Integer> lines) {
		this.linenumbers = lines;
		taintFrame = new HashMap<String, String>();
	}

	@Override
	public String toString() {
		String lines = "{";
		for (Integer integer : linenumbers) {
			lines += integer + ",";
		}

		String frameStr = "";
		for (Entry<String, String> entry : taintFrame.entrySet()) {
			frameStr += entry.getKey() + " => " + entry.getValue() + "\n";
		}
		return "BugReport [bugType=" + bugType + ", className=" + className + ", methodName=" + methodName
				+ ", methodSignature=" + methodSignature + ", lineNumber=" + lineNumber + ", artifacts=" + artifacts
				+ ", paramTaint:" + paramTaint + ", injectableMethod:" + injectableMethod + ", Lines:" + lines
				+ ", TaintFrame:" + frameStr + "]";
	}

	public void addArtifact(String key, String nodeValue) {
		artifacts.put(key, nodeValue);
	}

	public String getArtifact(String key) {
		return artifacts.get(key);
	}
}
