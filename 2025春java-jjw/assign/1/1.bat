@echo off

set JAVA_HOME=%JAVA_HOME%
set path=%JAVA_HOME%\bin;%path%

set PROJ_HOME=D:\D2B\java\assign\1\chapter1
set class_path=%class_path%;%PROJ_HOME%\jar\run.jar

java -classpath %class_path% homework.ch1.Welcome

echo.
jar cvf %PROJ_HOME%\myjar\run.jar %PROJ_HOME%\class\homework\ch1\Welcome.class

echo.
echo --ls %PROJ_HOME%\myjar
ls %PROJ_HOME%\myjar