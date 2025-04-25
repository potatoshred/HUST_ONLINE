@echo off
set JAVA_HOME=D:\.jdks\ms-17.0.14
set PATH=%JAVA_HOME%/bin;%PATH%

rem 设置运行TestNG的依赖Jar包所在目录（当前目录的lib子目录）
set LIB_DIR=.\lib

rem 设置被测试类的目录（顶级包目录的父目录）
set TO_BE_TEST_CLASSPAH=.\betest

rem 设置测试类的目录(顶级包目录的父目录）,为当前目录的test子目录
set TEST_SUITE_CLASSPATH=.\test

rem 将运行TestNG的依赖Jar包放进CLASSPATH
setlocal EnableDelayedExpansion
set DEP_JAR=""
for /r %LIB_DIR% %%i in (*.jar) do if !DEP_JAR!=="" (set DEP_JAR=%%i) else (set DEP_JAR=!DEP_JAR!;%%i) 

set CLASSPATH=%CLASSPATH%;%TO_BE_TEST_CLASSPAH%;%TEST_SUITE_CLASSPATH%;%DEP_JAR%


java  --add-opens java.base/java.lang=ALL-UNNAMED --add-opens java.base/java.math=ALL-UNNAMED --add-opens java.base/sun.net.util=ALL-UNNAMED org.testng.TestNG testng.xml -d test-output