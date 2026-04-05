# Sprint 2 Report (3/1/26 - 4/4/2026)
## What's New (User Facing)
* Complete Elasticsearch GUI with PC statistics such as #packets in, #packets out, Memory usage, and CPU usage along with a table to display packet information.
* Complete Npcap integration with Qt for capturing UDP packets over a user-chosen network and displaying them akin to Wireshark.
* Connect the Elastic dashboard to the simple python ids system, allowing data to be shown to the dashboard.
* Once dashboard was connected we made sure that the alerts were shown to the dashboard in the correct way
* Expanded elastic dashboard to shown all packet information, changing a few lines of code to allow for that
* Updated code so it can easier run on other systems, putting in automated code to know what interface should be used by the ids
* Feature n or Bug Fix n

## Work Summary (Developer Facing)
Provide a one paragraph synposis of what your team accomplished this sprint. Don't
repeat the "What's New" list of features. Instead, help the instructor understand
how you went about the work described there, any barriers you overcame, and any
significant learnings for your team.

Response: For Sprint 2, we continued to work on our respective tasks with Mitchell focusing on the Qt UI, Blake hashing out packet analysis in Python, and Max updating the WA reports in addition to completing the Elasticsearch results dashboard. Blake made a decent amount of progress connecting the ids to the dashboard, aloowing alerts to be shown and normal packet info. Given its our first time building an IDS, the barrier to entry was steep, but with the online help & teacher guidance, we have been able to meet our Sprint 2 goals. One significant learning is that threading is integral for smooth capturing logic and a responsive UI. 

## Unfinished Work
If applicable, explain the work you did not finish in this sprint. For issues/user
stories in the current sprint that have not been closed, (a) any progress toward
completion of the issues has been clearly tracked (by checking the checkboxes of
acceptance criteria), (b) a comment has been added to the issue to explain why the
issue could not be completed (e.g., "we ran out of time" or "we did not anticipate
it would be so much work"), and (c) the issue is added to a subsequent sprint, so
that it can be addressed later.

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint:
* https://github.com/orgs/WSU-CPTS322-SP26/projects/12?pane=issue&itemId=161193823&issue=WSU-CPTS322-SP26%7CIDS%7C13
* https://github.com/orgs/WSU-CPTS322-SP26/projects/12/views/1?pane=issue&itemId=169561797&issue=WSU-CPTS322-SP26%7CIDS%7C32
* https://github.com/WSU-CPTS322-SP26/IDS/issues/37
* https://github.com/WSU-CPTS322-SP26/IDS/issues/12
* URL of issue n

Reminders (Remove this section when you save the file):
* Each issue should be assigned to a milestone
* Each completed issue should be assigned to a pull request
* Each completed pull request should include a link to a "Before and After" video
* All team members who contributed to the issue should be assigned to it on
GitHub
* Each issue should be assigned story points using a label
* Story points contribution of each team member should be indicated in a comment

## Incomplete Issues/User Stories
Here are links to issues we worked on but did not complete in this sprint:
* URL of issue 1 <<One sentence explanation of why issue was not completed>>
* URL of issue 2 <<One sentence explanation of why issue was not completed>>
* URL of issue n <<One sentence explanation of why issue was not completed>>
Examples of explanations (Remove this section when you save the file):
* "We ran into a complication we did not anticipate (explain briefly)."
* "We decided that the feature did not add sufficient value for us to work on it
in this sprint (explain briefly)."
* "We could not reproduce the bug" (explain briefly).
* "We did not get to this issue because..." (explain briefly)

## Code Files for Review
Please review the following code files, which were actively developed during this
sprint, for quality:
* [Name of code file 1](https://github.com/your_repo/file_extension)
* [Name of code file 2](https://github.com/your_repo/file_extension)
* [Qt_IDS_Interface](https://github.com/WSU-CPTS322-SP26/IDS/tree/main/Qt_IDS_Interface)
* [NpcapPlayground](https://github.com/WSU-CPTS322-SP26/IDS/tree/main/NpcapPlayground)
* [Qt Npcap Test](https://github.com/WSU-CPTS322-SP26/IDS/tree/main/Qt%20Npcap%20Test)

## Retrospective Summary
Here's what went well:
* The team put in solid effort to complete the issues.
* Each member has a deliverable for Sprint 2 to showcase.
* Item x

Here's what we'd like to improve:
* Work better as a team instead of as individuals.
* Meet more often to discuss progress and next steps.
* Item x

Here are changes we plan to implement in the next sprint:
* Refactor and update Mitchell's Qt code with added functionality & organization.
* Connect each member's deliverables to form a cohesive IDS
* Item x
