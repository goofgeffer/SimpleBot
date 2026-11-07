@echo off
setlocal

set "APPNAME=SimpleBot"
set "DEST=%LocalAppData%\Programs\%APPNAME%"
set "UKEY=HKCU\Software\Microsoft\Windows\CurrentVersion\Uninstall\%APPNAME%"

rem If this copy lives in the install folder, rerun from TEMP so the folder can be deleted
if /I "%~dp0"=="%DEST%\" copy /Y "%~f0" "%TEMP%\simplebot_uninstall.bat" >nul & start "" "%TEMP%\simplebot_uninstall.bat" & exit /b

tasklist /FI "IMAGENAME eq simplebot.exe" 2>nul | find /I "simplebot.exe" >nul
if not errorlevel 1 echo ERROR: SimpleBot is running. Close it and run this again.& pause& exit /b 1

echo Removing %APPNAME%...

powershell -NoProfile -ExecutionPolicy Bypass -Command "Remove-Item ([Environment]::GetFolderPath('Desktop')+'\%APPNAME%.lnk') -ErrorAction SilentlyContinue"

reg delete "%UKEY%" /f >nul 2>nul

if exist "%DEST%" rd /s /q "%DEST%"

echo.
echo %APPNAME% has been uninstalled.
echo Your dev folder (source and compiled exe) was not touched.
echo.
pause