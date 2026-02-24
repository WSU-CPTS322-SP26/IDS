@echo off
cd /d %~dp0

echo Starting Docker Desktop...

REM Start Docker Desktop (if not already running)
start "" "C:\Program Files\Docker\Docker\Docker Desktop.exe"

echo Waiting for Docker to initialize...

REM Wait until Docker is ready
:waitloop
docker info >nul 2>&1
if errorlevel 1 (
    timeout /t 5 >nul
    goto waitloop
)

echo Docker is running!

REM Start containers
docker compose up -d

echo Waiting 30 seconds for Elasticsearch and Kibana...
timeout /t 30 >nul

REM Open Kibana
start http://localhost:5601/app/dashboards#/view/3e9fd275-ec0d-4759-9e36-8813c18c8862

echo Demo is ready!
pause