@echo off
cd /d %~dp0
powershell -ExecutionPolicy Bypass -File start-demo.ps1
pause