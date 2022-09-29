@echo off

if "%TEMP%" == "" set TEMP=%TMP%
if "%TMP%" == "" set TMP=%TEMP%
if "%TEMP%" == "" md C:\TEMP
if "%TEMP%" == "" set TMP=C:\TEMP
if "%TEMP%" == "" set TEMP=C:\TEMP
