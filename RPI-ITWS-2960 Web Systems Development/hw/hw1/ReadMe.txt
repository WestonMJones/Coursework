Why did you select the doctype you used?

	HTML5 is the most up to date and current version of HTML, so I figured the best resources would refer to it. 

How does your doctype compare to other commonly seen (strict) doctypes?

	From what I can see, there are three main categories of document type: 1. HTML5, 2. HTML4.0.1, and 3. XHTML 1.0. The latter two have various different types, but as per the question we'll focus on the strict types.

	HTML4 is the oldest version of HTML and thus is based off of SGML rules for marking up documents and hence also requires a Document Type definition -- HTML 4 document declarations are somewhat longer. HTML4 is somewhat loose with its rules -- some tags don't need to be closed for example.

	XHTML is also based off of SGML and hence requires a longer declaration in the header. It all imposes the requirement that the markup must also be welformed XML (so you have to close all your tags).

	HTML5 is the newest doctype and doesn't use SGML (hence requiring a small declaration). HTML is very similar to HTML4 but has a few new features implement that make it easier to do things like embed videos and utilize location services.

How is the markup for your document semantically correct? Are there any non-semantic elements that you needed for styling purposes? If you used divs and /or spans, be sure to account for them in your explanation.

	I'm fairly certain that my document is semantically correct. I've closed all tags properly, the page displays properly in browsers, and it passes online HTML validators.

	I did use quite a few non sematic elements in my page. First, I used two div containers to hold elements that would appear on the side bar and elements that would appear in the main, right hand side of my page.

	Within the side bar, I used a "title" div to center my picture, name, and other title-like information.

	For my contact information I used one set of spans to bold some of the text for stylistic effect and other spans / divs to markup my contact information in accordance with the hcard specification for part 2 of the lab.

	I didn't need to use any more divs and spans for the right hand side of my page because most of the content just reads straight down. I just used CSS to adjust the size / style of some of the text to delineate titles and details.

In your own words, how is the hCard information you added useful to both humans and automated user agents trying to access your content?

	For humans, the hcard format encloses a lot of contact information details in their own separate classes to make it easier to style them and make them standout to a human reader. For machines, these classes also allow web scrapers to look for certain standardized tags in your website, grab your contact information, then automatically enter that information into a database or application.

References:

For splitting my resume into a side bar / content area, I used this w3 schools example as inspiration: https://www.w3schools.com/css/tryit.asp?filename=trycss_template4

I recolored ome of the icons in this online pack to add more style to this assignment (I don't intend to use this an actual resume) :https://www.123rf.com/photo_50433372_stock-vector-icons-set-for-your-resume-cv-job.html