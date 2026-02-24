# start-demo.ps1

# Navigate to the folder where the script is located
cd "$PSScriptRoot"

# Start Docker containers in detached mode
docker compose up -d

# Give services time to start (Elasticsearch & Kibana need ~30 sec)
Write-Output "Waiting 30 seconds for Elasticsearch and Kibana to start..."
Start-Sleep -Seconds 30

# Open Kibana in the default browser
Start-Process "http://localhost:5601"

Write-Output "Elastic demo should now be open in your browser!"