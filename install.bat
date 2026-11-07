@echo off
setlocal

set "APPNAME=SimpleBot"
set "VERSION=1.0"
set "SRC=%~dp0simplebot.exe"
set "DEST=%LocalAppData%\Programs\%APPNAME%"
set "UKEY=HKCU\Software\Microsoft\Windows\CurrentVersion\Uninstall\%APPNAME%"

if not exist "%SRC%" echo ERROR: simplebot.exe not found next to install.bat. Run compile.bat first.& pause& exit /b 1

tasklist /FI "IMAGENAME eq simplebot.exe" 2>nul | find /I "simplebot.exe" >nul
if not errorlevel 1 echo ERROR: SimpleBot is running. Close it and run this again.& pause& exit /b 1

if not exist "%DEST%" mkdir "%DEST%"

copy /Y "%SRC%" "%DEST%\simplebot.exe" >nul
if errorlevel 1 echo ERROR: Could not copy simplebot.exe.& pause& exit /b 1

if exist "%~dp0uninstall.bat" copy /Y "%~dp0uninstall.bat" "%DEST%\uninstall.bat" >nul

rem --- Desktop shortcut ---
powershell -NoProfile -ExecutionPolicy Bypass -Command "$desktop=[Environment]::GetFolderPath('Desktop'); $s=(New-Object -ComObject WScript.Shell).CreateShortcut($desktop+'\%APPNAME%.lnk'); $s.TargetPath='%DEST%\simplebot.exe'; $s.WorkingDirectory='%DEST%'; $s.Save()"
if errorlevel 1 echo ERROR: Could not create the desktop shortcut.& pause& exit /b 1

rem --- Apps and features entry (per-user, no admin needed) ---
reg add "%UKEY%" /v DisplayName /d "%APPNAME%" /f >nul
reg add "%UKEY%" /v DisplayVersion /d "%VERSION%" /f >nul
reg add "%UKEY%" /v Publisher /d "%USERNAME%" /f >nul
reg add "%UKEY%" /v InstallLocation /d "%DEST%" /f >nul
reg add "%UKEY%" /v DisplayIcon /d "%DEST%\simplebot.exe" /f >nul
reg add "%UKEY%" /v NoModify /t REG_DWORD /d 1 /f >nul
reg add "%UKEY%" /v NoRepair /t REG_DWORD /d 1 /f >nul
if exist "%DEST%\uninstall.bat" reg add "%UKEY%" /v UninstallString /d "cmd.exe /c \"%DEST%\uninstall.bat\"" /f >nul

echo.
echo Installed to: %DEST%
echo Desktop shortcut created: %APPNAME%
if exist "%DEST%\uninstall.bat" (echo Added to Apps and features.) else (echo NOTE: uninstall.bat was not next to install.bat, so no Apps and features entry works.)
echo.
pause