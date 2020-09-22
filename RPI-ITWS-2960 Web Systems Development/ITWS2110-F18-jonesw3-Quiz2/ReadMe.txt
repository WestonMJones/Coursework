Design Decisions:


I ignored most styling concerns because the quiz seems to be more about backend functionality. Hopefully we don't get points taken off for things
no explicitly required.

Very first time:


The login page would check for the existance of the database. If it doesn't exist, create it then proceed as normal perhaps as an separat install file.


Duplicate entries:

Query the database when the page loads and keep an array of existing entries in memory.

When the user submits a new entry, loop thru the array of existing projects and makes sure there are no duplicates.


Voting question:


Just one additional table, votes, that contains the colums studentID and projectID. Each row represrnts a vote that matches a student to a project.
It's a simple structure. Just two foriegn keys necessary to match students to projects.

To stop duplicate votes, the page would query that projectID, look for memberIDs and see if the current student ID matches with any of the 
project member IDS.



There's a lot of stuff I didn't finish because a lot of the instructions were unclear and this quiz was super long and annoying.

My database password isn't blank.
The passwords aren't salted.
The index page has a form that allows you to submit, but I couldn't finish / understand what was exactly supposed to happen
when a project was added successfully.
