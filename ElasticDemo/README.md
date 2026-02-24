# Elastic IDS Demo

This project demonstrates a simple Elastic Stack GUI for monitoring system metrics.  
It uses Docker to run:

- **Elasticsearch** – stores metrics
- **Kibana** – visualizes metrics
- **Metricbeat** – collects system metrics

This is intended as a **demo dashboard**, no intrusion detection functionality is included yet.

---

## Prerequisites

- [Docker Desktop](https://www.docker.com/products/docker-desktop) installed and running
- Minimum 8GB RAM recommended
- PowerShell / Terminal access

---

## How to Run

1. Open PowerShell (or terminal) and navigate to the project folder:

```powershell
cd path\to\elastic-demo
docker compose up -d
Go-to http://localhost:5601
