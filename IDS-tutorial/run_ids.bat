@echo off
title IDS + Elasticsearch Launcher

echo ============================================
echo   Starting Docker Desktop (if not running)
echo ============================================
start "" "C:\Program Files\Docker\Docker\Docker Desktop.exe"
echo Waiting for Docker to start...
timeout /t 10 >nul

echo.
echo ============================================
echo   Starting Elasticsearch + Kibana
echo ============================================
docker compose up -d

echo.
echo ============================================
echo   Waiting for Elasticsearch to become ready
echo ============================================

:wait_for_es
curl.exe http://localhost:9200 >nul 2>&1
if %errorlevel% neq 0 (
    echo Elasticsearch not ready yet... retrying in 3 seconds
    timeout /t 3 >nul
    goto wait_for_es
)

echo Elasticsearch is up!

echo.
echo ============================================
echo   Running IDS Test Script
echo ============================================
python IDS_tutorial_test.py

echo.
echo ============================================
echo   Opening Kibana in your browser
echo ============================================
start http://localhost:5601/app/dashboards#/view/3e9fd275-ec0d-4759-9e36-8813c18c8862?_g=(filters:!(),refreshInterval:(pause:!t,value:60000),time:(from:now-15w,to:now))

curl -X POST "http://localhost:5601/api/saved_objects/_import?overwrite=true" ^
  -H "kbn-xsrf: true" ^
  --form file=@export(2).ndjson

echo.
echo ============================================
echo   IDS Pipeline Complete
echo ============================================
pause