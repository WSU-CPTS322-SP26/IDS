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
echo   Waiting for Kibana to become ready
echo ============================================
:wait_for_kibana
curl.exe http://localhost:5601 >nul 2>&1
if %errorlevel% neq 0 (
    echo Kibana not ready yet... retrying in 3 seconds
    timeout /t 3 >nul
    goto wait_for_kibana
)
echo Kibana is up!

echo.
echo ============================================
echo   Importing Dashboard
echo ============================================
curl -X POST "http://localhost:5601/api/saved_objects/_import?overwrite=true" ^
  -H "kbn-xsrf: true" ^
  --form file=@dashboard.ndjson

echo.
echo ============================================
echo   Starting REAL IDS
echo ============================================
start "" python IDS_tutorial.py

echo.
echo ============================================
echo   Waiting for first packet to index
echo ============================================
:wait_for_packet
curl.exe -s "http://localhost:9200/ids-packets/_search?size=1&pretty" | findstr "\"value\" : 1" >nul
if %errorlevel% neq 0 (
    echo No packets yet... retrying
    timeout /t 2 >nul
    goto wait_for_packet
)
echo Packet index exists!

echo.
echo ============================================
echo   Opening Kibana in your browser
echo ============================================
start http://localhost:5601/app/dashboards#/view/3e9fd275-ec0d-4759-9e36-8813c18c8862?_g=(filters:!(),refreshInterval:(pause:!f,value:5000),time:(from:now-15m,to:now))

echo.
echo ============================================
echo   IDS Pipeline Complete
echo ============================================
pause
