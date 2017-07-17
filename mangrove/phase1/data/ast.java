|Kids:9 , line1, class com.github.javaparser.ast.CompilationUnit: /** * OWASP Benchmark Project v1.1 * * This file is part of the Open Web Application Security Project (OWASP) * Benchmark Project. For details, please see * <a href="https://www.owasp.org/index.php/Benchmark">https://www.owasp.org/index.php/Benchmark</a>. * * The Benchmark is free software: you can redistribute it and/or modify it under the terms * of the GNU General Public License as published by the Free Software Foundation, version 2. * * The Benchmark is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the * GNU General Public License for more details * * @author Dave Wichers <a href="https://www.aspectsecurity.com">Aspect Security</a> * @created 2015 */ package org.owasp.benchmark.testcode;  import java.io.IOException; import javax.servlet.ServletException; import javax.servlet.annotation.WebServlet; import javax.servlet.http.HttpServlet; import javax.servlet.http.HttpServletRequest; import javax.servlet.http.HttpServletResponse;  @WebServlet("/BenchmarkTest09682") public class BenchmarkTest09682 extends HttpServlet {      private static final long serialVersionUID = 1L;      @Override     public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {         doPost(request, response);     }      @Override     public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {         String param = "";         java.util.Enumeration<String> headers = request.getHeaders("foo");         if (headers.hasMoreElements()) {             // just grab first element             param = headers.nextElement();         }         String bar = new Test().doSomething(param);         String sql = "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar + "'";         try {             java.sql.Statement statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement();             statement.execute(sql, new int[] { 1, 2 });         } catch (java.sql.SQLException e) {             throw new ServletException(e);         }     }      private class Test {          public String doSomething(String param) throws ServletException, IOException {             String bar = org.apache.commons.lang.StringEscapeUtils.escapeHtml(param);             return bar;         }     }     // end innerclass Test } // end DataflowThruInnerClass 
|-Kids:1 , line19, class com.github.javaparser.ast.PackageDeclaration: package org.owasp.benchmark.testcode;  
|--Kids:1 , line19, class com.github.javaparser.ast.expr.Name: org.owasp.benchmark.testcode
|---Kids:1 , line19, class com.github.javaparser.ast.expr.Name: org.owasp.benchmark
|----Kids:1 , line19, class com.github.javaparser.ast.expr.Name: org.owasp
|-----Kids:0 , line19, class com.github.javaparser.ast.expr.Name: org
|-Kids:1 , line21, class com.github.javaparser.ast.imports.SingleTypeImportDeclaration: import java.io.IOException; 
|--Kids:1 , line21, class com.github.javaparser.ast.type.ClassOrInterfaceType: java.io.IOException
|---Kids:1 , line21, class com.github.javaparser.ast.type.ClassOrInterfaceType: java.io
|----Kids:0 , line21, class com.github.javaparser.ast.type.ClassOrInterfaceType: java
|-Kids:1 , line23, class com.github.javaparser.ast.imports.SingleTypeImportDeclaration: import javax.servlet.ServletException; 
|--Kids:1 , line23, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet.ServletException
|---Kids:1 , line23, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet
|----Kids:0 , line23, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax
|-Kids:1 , line24, class com.github.javaparser.ast.imports.SingleTypeImportDeclaration: import javax.servlet.annotation.WebServlet; 
|--Kids:1 , line24, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet.annotation.WebServlet
|---Kids:1 , line24, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet.annotation
|----Kids:1 , line24, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet
|-----Kids:0 , line24, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax
|-Kids:1 , line25, class com.github.javaparser.ast.imports.SingleTypeImportDeclaration: import javax.servlet.http.HttpServlet; 
|--Kids:1 , line25, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet.http.HttpServlet
|---Kids:1 , line25, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet.http
|----Kids:1 , line25, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet
|-----Kids:0 , line25, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax
|-Kids:1 , line26, class com.github.javaparser.ast.imports.SingleTypeImportDeclaration: import javax.servlet.http.HttpServletRequest; 
|--Kids:1 , line26, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet.http.HttpServletRequest
|---Kids:1 , line26, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet.http
|----Kids:1 , line26, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet
|-----Kids:0 , line26, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax
|-Kids:1 , line27, class com.github.javaparser.ast.imports.SingleTypeImportDeclaration: import javax.servlet.http.HttpServletResponse; 
|--Kids:1 , line27, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet.http.HttpServletResponse
|---Kids:1 , line27, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet.http
|----Kids:1 , line27, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax.servlet
|-----Kids:0 , line27, class com.github.javaparser.ast.type.ClassOrInterfaceType: javax
|-Kids:9 , line29, class com.github.javaparser.ast.body.ClassOrInterfaceDeclaration: @WebServlet("/BenchmarkTest09682") public class BenchmarkTest09682 extends HttpServlet {      private static final long serialVersionUID = 1L;      @Override     public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {         doPost(request, response);     }      @Override     public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {         String param = "";         java.util.Enumeration<String> headers = request.getHeaders("foo");         if (headers.hasMoreElements()) {             // just grab first element             param = headers.nextElement();         }         String bar = new Test().doSomething(param);         String sql = "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar + "'";         try {             java.sql.Statement statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement();             statement.execute(sql, new int[] { 1, 2 });         } catch (java.sql.SQLException e) {             throw new ServletException(e);         }     }      private class Test {          public String doSomething(String param) throws ServletException, IOException {             String bar = org.apache.commons.lang.StringEscapeUtils.escapeHtml(param);             return bar;         }     }     // end innerclass Test }
|--Kids:2 , line29, class com.github.javaparser.ast.expr.SingleMemberAnnotationExpr: @WebServlet("/BenchmarkTest09682")
|---Kids:0 , line29, class com.github.javaparser.ast.expr.Name: WebServlet
|---Kids:0 , line29, class com.github.javaparser.ast.expr.StringLiteralExpr: "/BenchmarkTest09682"
|--Kids:0 , line30, class com.github.javaparser.ast.expr.SimpleName: BenchmarkTest09682
|--Kids:2 , line32, class com.github.javaparser.ast.body.FieldDeclaration: private static final long serialVersionUID = 1L;
|---Kids:0 , line32, class com.github.javaparser.ast.type.PrimitiveType: long
|---Kids:2 , line32, class com.github.javaparser.ast.body.VariableDeclarator: serialVersionUID = 1L
|----Kids:1 , line32, class com.github.javaparser.ast.body.VariableDeclaratorId: serialVersionUID
|-----Kids:0 , line32, class com.github.javaparser.ast.expr.SimpleName: serialVersionUID
|----Kids:0 , line32, class com.github.javaparser.ast.expr.LongLiteralExpr: 1L
|--Kids:8 , line34, class com.github.javaparser.ast.body.MethodDeclaration: @Override public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {     doPost(request, response); }
|---Kids:1 , line34, class com.github.javaparser.ast.expr.MarkerAnnotationExpr: @Override
|----Kids:0 , line34, class com.github.javaparser.ast.expr.Name: Override
|---Kids:0 , line35, class com.github.javaparser.ast.type.VoidType: void
|---Kids:0 , line35, class com.github.javaparser.ast.expr.SimpleName: doGet
|---Kids:2 , line35, class com.github.javaparser.ast.body.Parameter: HttpServletRequest request
|----Kids:1 , line35, class com.github.javaparser.ast.body.VariableDeclaratorId: request
|-----Kids:0 , line35, class com.github.javaparser.ast.expr.SimpleName: request
|----Kids:0 , line35, class com.github.javaparser.ast.type.ClassOrInterfaceType: HttpServletRequest
|---Kids:2 , line35, class com.github.javaparser.ast.body.Parameter: HttpServletResponse response
|----Kids:1 , line35, class com.github.javaparser.ast.body.VariableDeclaratorId: response
|-----Kids:0 , line35, class com.github.javaparser.ast.expr.SimpleName: response
|----Kids:0 , line35, class com.github.javaparser.ast.type.ClassOrInterfaceType: HttpServletResponse
|---Kids:0 , line35, class com.github.javaparser.ast.type.ClassOrInterfaceType: ServletException
|---Kids:0 , line35, class com.github.javaparser.ast.type.ClassOrInterfaceType: IOException
|---Kids:1 , line35, class com.github.javaparser.ast.stmt.BlockStmt: {     doPost(request, response); }
|----Kids:1 , line36, class com.github.javaparser.ast.stmt.ExpressionStmt: doPost(request, response);
|-----Kids:3 , line36, class com.github.javaparser.ast.expr.MethodCallExpr: doPost(request, response)
|------Kids:0 , line36, class com.github.javaparser.ast.expr.SimpleName: doPost
|------Kids:1 , line36, class com.github.javaparser.ast.expr.NameExpr: request
|-------Kids:0 , line36, class com.github.javaparser.ast.expr.SimpleName: request
|------Kids:1 , line36, class com.github.javaparser.ast.expr.NameExpr: response
|-------Kids:0 , line36, class com.github.javaparser.ast.expr.SimpleName: response
|--Kids:8 , line39, class com.github.javaparser.ast.body.MethodDeclaration: @Override public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {     String param = "";     java.util.Enumeration<String> headers = request.getHeaders("foo");     if (headers.hasMoreElements()) {         // just grab first element         param = headers.nextElement();     }     String bar = new Test().doSomething(param);     String sql = "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar + "'";     try {         java.sql.Statement statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement();         statement.execute(sql, new int[] { 1, 2 });     } catch (java.sql.SQLException e) {         throw new ServletException(e);     } }
|---Kids:1 , line39, class com.github.javaparser.ast.expr.MarkerAnnotationExpr: @Override
|----Kids:0 , line39, class com.github.javaparser.ast.expr.Name: Override
|---Kids:0 , line40, class com.github.javaparser.ast.type.VoidType: void
|---Kids:0 , line40, class com.github.javaparser.ast.expr.SimpleName: doPost
|---Kids:2 , line40, class com.github.javaparser.ast.body.Parameter: HttpServletRequest request
|----Kids:1 , line40, class com.github.javaparser.ast.body.VariableDeclaratorId: request
|-----Kids:0 , line40, class com.github.javaparser.ast.expr.SimpleName: request
|----Kids:0 , line40, class com.github.javaparser.ast.type.ClassOrInterfaceType: HttpServletRequest
|---Kids:2 , line40, class com.github.javaparser.ast.body.Parameter: HttpServletResponse response
|----Kids:1 , line40, class com.github.javaparser.ast.body.VariableDeclaratorId: response
|-----Kids:0 , line40, class com.github.javaparser.ast.expr.SimpleName: response
|----Kids:0 , line40, class com.github.javaparser.ast.type.ClassOrInterfaceType: HttpServletResponse
|---Kids:0 , line40, class com.github.javaparser.ast.type.ClassOrInterfaceType: ServletException
|---Kids:0 , line40, class com.github.javaparser.ast.type.ClassOrInterfaceType: IOException
|---Kids:6 , line40, class com.github.javaparser.ast.stmt.BlockStmt: {     String param = "";     java.util.Enumeration<String> headers = request.getHeaders("foo");     if (headers.hasMoreElements()) {         // just grab first element         param = headers.nextElement();     }     String bar = new Test().doSomething(param);     String sql = "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar + "'";     try {         java.sql.Statement statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement();         statement.execute(sql, new int[] { 1, 2 });     } catch (java.sql.SQLException e) {         throw new ServletException(e);     } }
|----Kids:1 , line42, class com.github.javaparser.ast.stmt.ExpressionStmt: String param = "";
|-----Kids:2 , line42, class com.github.javaparser.ast.expr.VariableDeclarationExpr: String param = ""
|------Kids:0 , line42, class com.github.javaparser.ast.type.ClassOrInterfaceType: String
|------Kids:2 , line42, class com.github.javaparser.ast.body.VariableDeclarator: param = ""
|-------Kids:1 , line42, class com.github.javaparser.ast.body.VariableDeclaratorId: param
|--------Kids:0 , line42, class com.github.javaparser.ast.expr.SimpleName: param
|-------Kids:0 , line42, class com.github.javaparser.ast.expr.StringLiteralExpr: ""
|----Kids:1 , line43, class com.github.javaparser.ast.stmt.ExpressionStmt: java.util.Enumeration<String> headers = request.getHeaders("foo");
|-----Kids:2 , line43, class com.github.javaparser.ast.expr.VariableDeclarationExpr: java.util.Enumeration<String> headers = request.getHeaders("foo")
|------Kids:2 , line43, class com.github.javaparser.ast.type.ClassOrInterfaceType: java.util.Enumeration<String>
|-------Kids:1 , line43, class com.github.javaparser.ast.type.ClassOrInterfaceType: java.util
|--------Kids:0 , line43, class com.github.javaparser.ast.type.ClassOrInterfaceType: java
|-------Kids:0 , line43, class com.github.javaparser.ast.type.ClassOrInterfaceType: String
|------Kids:2 , line43, class com.github.javaparser.ast.body.VariableDeclarator: headers = request.getHeaders("foo")
|-------Kids:1 , line43, class com.github.javaparser.ast.body.VariableDeclaratorId: headers
|--------Kids:0 , line43, class com.github.javaparser.ast.expr.SimpleName: headers
|-------Kids:3 , line43, class com.github.javaparser.ast.expr.MethodCallExpr: request.getHeaders("foo")
|--------Kids:1 , line43, class com.github.javaparser.ast.expr.NameExpr: request
|---------Kids:0 , line43, class com.github.javaparser.ast.expr.SimpleName: request
|--------Kids:0 , line43, class com.github.javaparser.ast.expr.SimpleName: getHeaders
|--------Kids:0 , line43, class com.github.javaparser.ast.expr.StringLiteralExpr: "foo"
|----Kids:2 , line44, class com.github.javaparser.ast.stmt.IfStmt: if (headers.hasMoreElements()) {     // just grab first element     param = headers.nextElement(); }
|-----Kids:2 , line44, class com.github.javaparser.ast.expr.MethodCallExpr: headers.hasMoreElements()
|------Kids:1 , line44, class com.github.javaparser.ast.expr.NameExpr: headers
|-------Kids:0 , line44, class com.github.javaparser.ast.expr.SimpleName: headers
|------Kids:0 , line44, class com.github.javaparser.ast.expr.SimpleName: hasMoreElements
|-----Kids:1 , line44, class com.github.javaparser.ast.stmt.BlockStmt: {     // just grab first element     param = headers.nextElement(); }
|------Kids:1 , line45, class com.github.javaparser.ast.stmt.ExpressionStmt: // just grab first element param = headers.nextElement();
|-------Kids:2 , line45, class com.github.javaparser.ast.expr.AssignExpr: param = headers.nextElement()
|--------Kids:1 , line45, class com.github.javaparser.ast.expr.NameExpr: param
|---------Kids:0 , line45, class com.github.javaparser.ast.expr.SimpleName: param
|--------Kids:2 , line45, class com.github.javaparser.ast.expr.MethodCallExpr: headers.nextElement()
|---------Kids:1 , line45, class com.github.javaparser.ast.expr.NameExpr: headers
|----------Kids:0 , line45, class com.github.javaparser.ast.expr.SimpleName: headers
|---------Kids:0 , line45, class com.github.javaparser.ast.expr.SimpleName: nextElement
|----Kids:1 , line48, class com.github.javaparser.ast.stmt.ExpressionStmt: String bar = new Test().doSomething(param);
|-----Kids:2 , line48, class com.github.javaparser.ast.expr.VariableDeclarationExpr: String bar = new Test().doSomething(param)
|------Kids:0 , line48, class com.github.javaparser.ast.type.ClassOrInterfaceType: String
|------Kids:2 , line48, class com.github.javaparser.ast.body.VariableDeclarator: bar = new Test().doSomething(param)
|-------Kids:1 , line48, class com.github.javaparser.ast.body.VariableDeclaratorId: bar
|--------Kids:0 , line48, class com.github.javaparser.ast.expr.SimpleName: bar
|-------Kids:3 , line48, class com.github.javaparser.ast.expr.MethodCallExpr: new Test().doSomething(param)
|--------Kids:1 , line48, class com.github.javaparser.ast.expr.ObjectCreationExpr: new Test()
|---------Kids:0 , line48, class com.github.javaparser.ast.type.ClassOrInterfaceType: Test
|--------Kids:0 , line48, class com.github.javaparser.ast.expr.SimpleName: doSomething
|--------Kids:1 , line48, class com.github.javaparser.ast.expr.NameExpr: param
|---------Kids:0 , line48, class com.github.javaparser.ast.expr.SimpleName: param
|----Kids:1 , line50, class com.github.javaparser.ast.stmt.ExpressionStmt: String sql = "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar + "'";
|-----Kids:2 , line50, class com.github.javaparser.ast.expr.VariableDeclarationExpr: String sql = "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar + "'"
|------Kids:0 , line50, class com.github.javaparser.ast.type.ClassOrInterfaceType: String
|------Kids:2 , line50, class com.github.javaparser.ast.body.VariableDeclarator: sql = "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar + "'"
|-------Kids:1 , line50, class com.github.javaparser.ast.body.VariableDeclaratorId: sql
|--------Kids:0 , line50, class com.github.javaparser.ast.expr.SimpleName: sql
|-------Kids:2 , line50, class com.github.javaparser.ast.expr.BinaryExpr: "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar + "'"
|--------Kids:2 , line50, class com.github.javaparser.ast.expr.BinaryExpr: "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar
|---------Kids:0 , line50, class com.github.javaparser.ast.expr.StringLiteralExpr: "SELECT * from USERS where USERNAME='foo' and PASSWORD='"
|---------Kids:1 , line50, class com.github.javaparser.ast.expr.NameExpr: bar
|----------Kids:0 , line50, class com.github.javaparser.ast.expr.SimpleName: bar
|--------Kids:0 , line50, class com.github.javaparser.ast.expr.StringLiteralExpr: "'"
|----Kids:2 , line52, class com.github.javaparser.ast.stmt.TryStmt: try {     java.sql.Statement statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement();     statement.execute(sql, new int[] { 1, 2 }); } catch (java.sql.SQLException e) {     throw new ServletException(e); }
|-----Kids:2 , line52, class com.github.javaparser.ast.stmt.BlockStmt: {     java.sql.Statement statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement();     statement.execute(sql, new int[] { 1, 2 }); }
|------Kids:1 , line53, class com.github.javaparser.ast.stmt.ExpressionStmt: java.sql.Statement statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement();
|-------Kids:2 , line53, class com.github.javaparser.ast.expr.VariableDeclarationExpr: java.sql.Statement statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement()
|--------Kids:1 , line53, class com.github.javaparser.ast.type.ClassOrInterfaceType: java.sql.Statement
|---------Kids:1 , line53, class com.github.javaparser.ast.type.ClassOrInterfaceType: java.sql
|----------Kids:0 , line53, class com.github.javaparser.ast.type.ClassOrInterfaceType: java
|--------Kids:2 , line53, class com.github.javaparser.ast.body.VariableDeclarator: statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement()
|---------Kids:1 , line53, class com.github.javaparser.ast.body.VariableDeclaratorId: statement
|----------Kids:0 , line53, class com.github.javaparser.ast.expr.SimpleName: statement
|---------Kids:2 , line53, class com.github.javaparser.ast.expr.MethodCallExpr: org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement()
|----------Kids:2 , line53, class com.github.javaparser.ast.expr.FieldAccessExpr: org.owasp.benchmark.helpers.DatabaseHelper
|-----------Kids:2 , line53, class com.github.javaparser.ast.expr.FieldAccessExpr: org.owasp.benchmark.helpers
|------------Kids:2 , line53, class com.github.javaparser.ast.expr.FieldAccessExpr: org.owasp.benchmark
|-------------Kids:2 , line53, class com.github.javaparser.ast.expr.FieldAccessExpr: org.owasp
|--------------Kids:1 , line53, class com.github.javaparser.ast.expr.NameExpr: org
|---------------Kids:0 , line53, class com.github.javaparser.ast.expr.SimpleName: org
|--------------Kids:0 , line53, class com.github.javaparser.ast.expr.SimpleName: owasp
|-------------Kids:0 , line53, class com.github.javaparser.ast.expr.SimpleName: benchmark
|------------Kids:0 , line53, class com.github.javaparser.ast.expr.SimpleName: helpers
|-----------Kids:0 , line53, class com.github.javaparser.ast.expr.SimpleName: DatabaseHelper
|----------Kids:0 , line53, class com.github.javaparser.ast.expr.SimpleName: getSqlStatement
|------Kids:1 , line54, class com.github.javaparser.ast.stmt.ExpressionStmt: statement.execute(sql, new int[] { 1, 2 });
|-------Kids:4 , line54, class com.github.javaparser.ast.expr.MethodCallExpr: statement.execute(sql, new int[] { 1, 2 })
|--------Kids:1 , line54, class com.github.javaparser.ast.expr.NameExpr: statement
|---------Kids:0 , line54, class com.github.javaparser.ast.expr.SimpleName: statement
|--------Kids:0 , line54, class com.github.javaparser.ast.expr.SimpleName: execute
|--------Kids:1 , line54, class com.github.javaparser.ast.expr.NameExpr: sql
|---------Kids:0 , line54, class com.github.javaparser.ast.expr.SimpleName: sql
|--------Kids:3 , line54, class com.github.javaparser.ast.expr.ArrayCreationExpr: new int[] { 1, 2 }
|---------Kids:0 , line54, class com.github.javaparser.ast.ArrayCreationLevel: []
|---------Kids:0 , line54, class com.github.javaparser.ast.type.PrimitiveType: int
|---------Kids:2 , line54, class com.github.javaparser.ast.expr.ArrayInitializerExpr: { 1, 2 }
|----------Kids:0 , line54, class com.github.javaparser.ast.expr.IntegerLiteralExpr: 1
|----------Kids:0 , line54, class com.github.javaparser.ast.expr.IntegerLiteralExpr: 2
|-----Kids:2 , line55, class com.github.javaparser.ast.stmt.CatchClause:  catch (java.sql.SQLException e) {     throw new ServletException(e); }
|------Kids:2 , line55, class com.github.javaparser.ast.body.Parameter: java.sql.SQLException e
|-------Kids:1 , line55, class com.github.javaparser.ast.body.VariableDeclaratorId: e
|--------Kids:0 , line55, class com.github.javaparser.ast.expr.SimpleName: e
|-------Kids:1 , line55, class com.github.javaparser.ast.type.ClassOrInterfaceType: java.sql.SQLException
|--------Kids:1 , line55, class com.github.javaparser.ast.type.ClassOrInterfaceType: java.sql
|---------Kids:0 , line55, class com.github.javaparser.ast.type.ClassOrInterfaceType: java
|------Kids:1 , line55, class com.github.javaparser.ast.stmt.BlockStmt: {     throw new ServletException(e); }
|-------Kids:1 , line56, class com.github.javaparser.ast.stmt.ThrowStmt: throw new ServletException(e);
|--------Kids:2 , line56, class com.github.javaparser.ast.expr.ObjectCreationExpr: new ServletException(e)
|---------Kids:0 , line56, class com.github.javaparser.ast.type.ClassOrInterfaceType: ServletException
|---------Kids:1 , line56, class com.github.javaparser.ast.expr.NameExpr: e
|----------Kids:0 , line56, class com.github.javaparser.ast.expr.SimpleName: e
|--Kids:2 , line60, class com.github.javaparser.ast.body.ClassOrInterfaceDeclaration: private class Test {      public String doSomething(String param) throws ServletException, IOException {         String bar = org.apache.commons.lang.StringEscapeUtils.escapeHtml(param);         return bar;     } }
|---Kids:0 , line60, class com.github.javaparser.ast.expr.SimpleName: Test
|---Kids:6 , line62, class com.github.javaparser.ast.body.MethodDeclaration: public String doSomething(String param) throws ServletException, IOException {     String bar = org.apache.commons.lang.StringEscapeUtils.escapeHtml(param);     return bar; }
|----Kids:0 , line62, class com.github.javaparser.ast.type.ClassOrInterfaceType: String
|----Kids:0 , line62, class com.github.javaparser.ast.expr.SimpleName: doSomething
|----Kids:2 , line62, class com.github.javaparser.ast.body.Parameter: String param
|-----Kids:1 , line62, class com.github.javaparser.ast.body.VariableDeclaratorId: param
|------Kids:0 , line62, class com.github.javaparser.ast.expr.SimpleName: param
|-----Kids:0 , line62, class com.github.javaparser.ast.type.ClassOrInterfaceType: String
|----Kids:0 , line62, class com.github.javaparser.ast.type.ClassOrInterfaceType: ServletException
|----Kids:0 , line62, class com.github.javaparser.ast.type.ClassOrInterfaceType: IOException
|----Kids:2 , line62, class com.github.javaparser.ast.stmt.BlockStmt: {     String bar = org.apache.commons.lang.StringEscapeUtils.escapeHtml(param);     return bar; }
|-----Kids:1 , line64, class com.github.javaparser.ast.stmt.ExpressionStmt: String bar = org.apache.commons.lang.StringEscapeUtils.escapeHtml(param);
|------Kids:2 , line64, class com.github.javaparser.ast.expr.VariableDeclarationExpr: String bar = org.apache.commons.lang.StringEscapeUtils.escapeHtml(param)
|-------Kids:0 , line64, class com.github.javaparser.ast.type.ClassOrInterfaceType: String
|-------Kids:2 , line64, class com.github.javaparser.ast.body.VariableDeclarator: bar = org.apache.commons.lang.StringEscapeUtils.escapeHtml(param)
|--------Kids:1 , line64, class com.github.javaparser.ast.body.VariableDeclaratorId: bar
|---------Kids:0 , line64, class com.github.javaparser.ast.expr.SimpleName: bar
|--------Kids:3 , line64, class com.github.javaparser.ast.expr.MethodCallExpr: org.apache.commons.lang.StringEscapeUtils.escapeHtml(param)
|---------Kids:2 , line64, class com.github.javaparser.ast.expr.FieldAccessExpr: org.apache.commons.lang.StringEscapeUtils
|----------Kids:2 , line64, class com.github.javaparser.ast.expr.FieldAccessExpr: org.apache.commons.lang
|-----------Kids:2 , line64, class com.github.javaparser.ast.expr.FieldAccessExpr: org.apache.commons
|------------Kids:2 , line64, class com.github.javaparser.ast.expr.FieldAccessExpr: org.apache
|-------------Kids:1 , line64, class com.github.javaparser.ast.expr.NameExpr: org
|--------------Kids:0 , line64, class com.github.javaparser.ast.expr.SimpleName: org
|-------------Kids:0 , line64, class com.github.javaparser.ast.expr.SimpleName: apache
|------------Kids:0 , line64, class com.github.javaparser.ast.expr.SimpleName: commons
|-----------Kids:0 , line64, class com.github.javaparser.ast.expr.SimpleName: lang
|----------Kids:0 , line64, class com.github.javaparser.ast.expr.SimpleName: StringEscapeUtils
|---------Kids:0 , line64, class com.github.javaparser.ast.expr.SimpleName: escapeHtml
|---------Kids:1 , line64, class com.github.javaparser.ast.expr.NameExpr: param
|----------Kids:0 , line64, class com.github.javaparser.ast.expr.SimpleName: param
|-----Kids:1 , line66, class com.github.javaparser.ast.stmt.ReturnStmt: return bar;
|------Kids:1 , line66, class com.github.javaparser.ast.expr.NameExpr: bar
|-------Kids:0 , line66, class com.github.javaparser.ast.expr.SimpleName: bar
|--Kids:0 , line30, class com.github.javaparser.ast.type.ClassOrInterfaceType: HttpServlet
|--Kids:0 , line58, class com.github.javaparser.ast.comments.LineComment: // end doPost 
|--Kids:0 , line68, class com.github.javaparser.ast.comments.LineComment: // end innerclass Test 
|-Kids:0 , line70, class com.github.javaparser.ast.comments.LineComment: // end DataflowThruInnerClass 
/**
* OWASP Benchmark Project v1.1
*
* This file is part of the Open Web Application Security Project (OWASP)
* Benchmark Project. For details, please see
* <a href="https://www.owasp.org/index.php/Benchmark">https://www.owasp.org/index.php/Benchmark</a>.
*
* The Benchmark is free software: you can redistribute it and/or modify it under the terms
* of the GNU General Public License as published by the Free Software Foundation, version 2.
*
* The Benchmark is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
* even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details
*
* @author Dave Wichers <a href="https://www.aspectsecurity.com">Aspect Security</a>
* @created 2015
*/
package org.owasp.benchmark.testcode;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/BenchmarkTest09682")
public class BenchmarkTest09682 extends HttpServlet {

 private static final long serialVersionUID = 1L;

 @Override
 public void doGet(HttpServletRequest request, HttpServletResponse response) {
 doPost(request, response);
 }

 @Override
 public void doPost(HttpServletRequest request, HttpServletResponse response) {
 String param = "";
 java.util.Enumeration<String> headers = request.getHeaders("foo");
 if (headers.hasMoreElements()) {
 param = headers.nextElement();
 }
 String bar = new Test().doSomething(param);
 String sql = "SELECT * from USERS where USERNAME='foo' and PASSWORD='" + bar + "'";
 {
 java.sql.Statement statement = org.owasp.benchmark.helpers.DatabaseHelper.getSqlStatement();
 statement.execute(sql, new int[] { 1, 2 });
 } catch (java.sql.SQLException e) {
 throw new ServletException(e);
 }
 }

 private class Test {

 public String doSomething(String param) {
 String bar = org.apache.commons.lang.StringEscapeUtils.escapeHtml(param);
 return bar;
 }
 }
}

