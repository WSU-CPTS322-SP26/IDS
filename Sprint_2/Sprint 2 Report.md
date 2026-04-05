# Sprint 2 Report (3/1/26 - 4/4/2026)
## What's New (User Facing)
* Complete Elasticsearch GUI with PC statistics such as #packets in, #packets out, Memory usage, and CPU usage along with a table to display packet information.
* Complete Npcap integration with Qt for capturing UDP packets over a user-chosen network and displaying them akin to Wireshark.
* Connect the Elastic dashboard to the simple python ids system, allowing data to be shown to the dashboard.
* Once dashboard was connected we made sure that the alerts were shown to the dashboard in the correct way
* Expanded elastic dashboard to shown all packet information, changing a few lines of code to allow for that
* Updated code so it can easier run on other systems, putting in automated code to know what interface should be used by the ids

## Work Summary (Developer Facing)

Response: For Sprint 2, we continued to work on our respective tasks with Mitchell focusing on the Qt UI, Blake hashing out packet analysis in Python, and Max updating the WA reports in addition to completing the Elasticsearch results dashboard. Blake made a decent amount of progress connecting the ids to the dashboard, aloowing alerts to be shown and normal packet info. Given its our first time building an IDS, the barrier to entry was steep, but with the online help & teacher guidance, we have been able to meet our Sprint 2 goals. One significant learning is that threading is integral for smooth capturing logic and a responsive UI. 

## Unfinished Work
N/A

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint:
* https://github.com/orgs/WSU-CPTS322-SP26/projects/12?pane=issue&itemId=161193823&issue=WSU-CPTS322-SP26%7CIDS%7C13
* https://github.com/orgs/WSU-CPTS322-SP26/projects/12/views/1?pane=issue&itemId=169561797&issue=WSU-CPTS322-SP26%7CIDS%7C32
* https://github.com/WSU-CPTS322-SP26/IDS/issues/37
* https://github.com/WSU-CPTS322-SP26/IDS/issues/12

## Incomplete Issues/User Stories
N/A

## Code Files for Review
Please review the following code files, which were actively developed during this
sprint, for quality:
* [ids code](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/IDS-tutorial/IDS_tutorial.py)
* [ids test code](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/IDS-tutorial/IDS_tutorial_test.py)
* [screenshot of dash](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/IDS-tutorial/Screenshot%202026-04-01%20224326.png)
* [Qt_IDS_Interface](https://github.com/WSU-CPTS322-SP26/IDS/tree/main/Qt_IDS_Interface)
* [NpcapPlayground](https://github.com/WSU-CPTS322-SP26/IDS/tree/main/NpcapPlayground)
* [Qt Npcap Test](https://github.com/WSU-CPTS322-SP26/IDS/tree/main/Qt%20Npcap%20Test)

## Retrospective Summary
Here's what went well:
* The team put in solid effort to complete the issues.
* Each member has a deliverable for Sprint 2 to showcase.
* Kept up with documentation

Here's what we'd like to improve:
* Work better as a team instead of as individuals.
* Meet more often to discuss progress and next steps.
* Better understand eachother's commits

Here are changes we plan to implement in the next sprint:
* Refactor and update Mitchell's Qt code with added functionality & organization.
* Connect each member's deliverables to form a cohesive IDS
* Update and polish the Final WA Report
