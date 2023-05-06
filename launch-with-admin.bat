@echo off
set launch_launcher=D:/darkEngine.sh
powershell -Command "Start-Process powershell -ArgumentList '-Command Set-ExecutionPolicy Unrestricted' -Verb RunAs"
powershell -Command "Start-Process -FilePath '%WINDIR%\System32\bash.exe' -ArgumentList '-c', '%launch_launcher%' -Verb RunAs"