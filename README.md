# NIDS

## A simple Network Intrusion Detection System (NIDS) created by Maxwell Reese, Mitchell Milander, and Blake Platt.

This NIDS captures packets, analyzes them, sends data to a dashboard, and alerts the user of any malicious traffic.

### Additional information

Similar to other independent IDS systems, this IDS consists of four main modules: packet capture, traffic analysis, threat detection, and alert generation. Throughout development, the team has ensured code stays organized and maintainable for future development. The application’s front-end uses Qt to display incoming packets from Npcap, similar to Wireshark. Python is extensively used for back-end processes like packet analysis, packet detection, and sending alerts. Alerts are both sent to the Qt GUI and an Elasticsearch dashboard that displays other metrics like CPU usage. Before the front-end and back-end were connected, the Python IDS was using the libary, Scapy, to capture packets. The Scapy-related tutorial code has been left in (but commented out) incase anyone is interested in observing it. A stretch goal is to implement a SSH Honeypot to attract malicious traffic and add windows to the Qt GUI that can be expanded to display detailed packet information, similar to Wireshark.

## Installation

Python 3.10+
Npcap installed
Npcap sdk

## Prerequisites

* Docker

### Add-ons

N/A

### Installation Steps
* Clone the GitHub

## Functionality

- Start Docker
- cd into the folder 'IDS Deployable' 
- Start run_ids.bat which will show in terminal and open an Elastic metrics dashboard
- Then from 'IDS Deployable', cd into Qt_IDS_Interface and run the Qt Project file

## Known Problems

- Requires administrative privileges
- High traffic volumes may impact performance
- Detection is currently rule-based (limited ML integration)
- Windows-dependent due to Npcap
- Issues with connection to kibana -- most issues currently get solved by either reloading the page or restarting the bat after closing everything
- Issues with conncting with elastic/docker -- if these pop up (mostly after running and closing) delete the docker container and then run the bat

## Additional Documentation
* [Sprint Report 1](https://github.com/WSU-CPTS322-SP26/IDS/blob/2af636bd5e15bb4326fc570639b3dcf47da079a1/SPRINT_REPORT_1)
* [Sprint Report 2](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/CPT_S%20322%20Class%20Assignments/Sprint_2/Sprint%202%20Report.md)
* [Sprint Report 3](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/CPT_S%20322%20Class%20Assignments/Sprint_3/Sprint_3_report.md)
* [Final Report](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/CPT_S%20322%20Class%20Assignments/FinalReport.pdf)
* [sources](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/Sources.md)
* [Licence](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/LICENSE.txt)

## Screenshots of Final Prototype
### Qt Interface
![Qt Interface](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/Tests%20%26%20Research/FinalPrototypeScreenshot/Qt%20Interface.png)

### Elastic Dashboard
![Elastic Dashboard](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/Tests%20%26%20Research/FinalPrototypeScreenshot/Elastic%20Dashboard.png)

