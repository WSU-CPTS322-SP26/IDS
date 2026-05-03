# Sprint 3 Report (4/4/26 - 5/2/2026)
# Demo video link: https://www.youtube.com/watch?v=0e_LJgPDHRQ
## What's New (User Facing)
 * Elasticsearch post queue and worker thread 
 * TCP socket listener for incoming JSON packet messages in both Qt and Python
 * Updated Qt interface

## Work Summary (Developer Facing)
This was an important final Sprint because it is where everything came together. To make this happen, we had to open up sockets for Python and Qt to communicate, so that packet data and alerts were being analyzed in real time. We also had to think about the extra load on the Python IDS and the possibility for backup which is why we delgated the POST request functionality to its own thread. All in all, we were able to get everything connected how we wanted to so that Elastic and Qt could receive alerts at the same time, and do it on real traffic.

## Unfinished Work
Non applicable because all of our work was completed on time.

## Completed Issues/User Stories
Here are links to the issues that we completed in this sprint:

 * [URL of issue 1](https://github.com/WSU-CPTS322-SP26/IDS/issues/42)
 * [URL of issue 2](https://github.com/WSU-CPTS322-SP26/IDS/issues/43)
 * [URL of issue 3](https://github.com/WSU-CPTS322-SP26/IDS/issues/47)
 * [URL of issue 3](https://github.com/WSU-CPTS322-SP26/IDS/issues/53)
 * [URL of issue 4](https://github.com/WSU-CPTS322-SP26/IDS/issues/54)
 * [URL of issue 5](https://github.com/WSU-CPTS322-SP26/IDS/issues/55)
 * [URL of issue 6](https://github.com/WSU-CPTS322-SP26/IDS/issues/56)
 * [URL of issue 7](https://github.com/WSU-CPTS322-SP26/IDS/issues/57)
 * [URL of issue 8](https://github.com/WSU-CPTS322-SP26/IDS/issues/58)
 * [URL of issue 9](https://github.com/WSU-CPTS322-SP26/IDS/issues/59)
 * [URL of issue 10](https://github.com/WSU-CPTS322-SP26/IDS/issues/73)
 * [URL of issue 11](https://github.com/WSU-CPTS322-SP26/IDS/issues/65)
 * [URL of issue 12](https://github.com/WSU-CPTS322-SP26/IDS/issues/64)
 
 ## Incomplete Issues/User Stories
 Non applicable because all of our issues were completed on time.

## Code Files for Review
Please review the following code files, which were actively developed during this sprint, for quality:
 * [Python IDS](https://github.com/WSU-CPTS322-SP26/IDS/blob/main/IDS%20Deployable/IDS_test.py)
 * [Qt Interface](https://github.com/WSU-CPTS322-SP26/IDS/tree/main/IDS%20Deployable/Qt_IDS_Interface)
 
## Retrospective Summary
Here's what went well:
  * We worked very well to complete our sprint 3 goals in an efficient and timely manner.
  * The Leison was very good at splitting and assigning work to other members of the team.
  * The weekly meetings with AJ helped keep us on track.
 
Here's what we'd like to improve:
   * We could have worked harder to come up with more features instead of just refining current ones.
   * We left a few things till last minute which made us rush at the end.
   * We wish we would have made more time for further testing.
  
Here are changes we plan to implement in the next sprint:
   * Non applicable since this is the final sprint.
