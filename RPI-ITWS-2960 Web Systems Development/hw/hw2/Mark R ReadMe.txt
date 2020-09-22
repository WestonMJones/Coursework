1) What are the advantages to writing a jQuery plugin over regular JavaScript that uses jQuery?
An advantage is that it saves development time.


2) Explain how your jQuery plugin adheres to best practices in JavaScript and jQuery development.
At the beginning of our jQuery plugin we declare global variables which makes our code easier to understand. We made bound event handlers to know when/what to do when elements update 



3) Does anything prevent you from POSTing high scores to a server on a different domain? If so, what? If not, how would we go about it (written explanation/pseudocode is fine here)?
Nothing currently prevents us from POSTing high scores to a server on a different domain, since we are just running Apache locally. I would use websockets via Google firebase realtime database since it is easiest to develop and free.