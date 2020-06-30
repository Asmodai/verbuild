@echo off

if "%~1"=="" (
   echo No parameters provided
   exit /b 1
)

if NOT exist %1 (
   echo Cannot find %1
   exit /b 0
)

echo doing stuff
%1 -c -f '*.*.+.*' -i simple -g basic -y 2013 -o %2
