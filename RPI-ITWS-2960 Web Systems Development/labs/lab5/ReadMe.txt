Part 1:

After modifying the code to use a delegate event handler, I compared the load times of the new code versus the load time of the old code.
While sometimes results are inconclusive because of varying internet speeds at any time, on average, the new code with the delegated event 
handler seems to perform better. This makes sense because the code is binding a single event handler to a specifc parent element rather
than searching all child elements and binding event handlers to them.

Part 2:

Here are the five performance improvements detailed below.

1. Moving the javascript to the bottom. Javascript should never be a make-or-break component of a webpage. It's designed to enhance existing content and some web browsers disable it outright. Moving it the bottom of the page ensures that it gets executed later, after the rest of the content has loaded. Keeping it at the top can have the page load stall on excecuting a javascript function, something that isn't as important. This change shows the content of the webpage -- the series of list elements -- earlier, because it doesn't have to wait for the javascript to finish executing.

2. Deleting Empty CSS Tags. In the header of the document, there is a style tag tag without a source attribute. This tag doesn't add anything to the document and only increases the size of the page, potentially increasing load time. This seems like a trivial detail, one tag doesn't change much in terms of performance and I didn't notice any difference in load time, but it's a good practice to have.

3. Simplifying javascript selectors. The selector that appends more list elements to the "foo" div uses multiple selectors that all refer to the same thing. I know that ids are the fastest selectors, so I just used the "#foo" selector to get the best possible runtime on the javascript. This was just one selector, so I didn't notice a functional change in page load time, but again, uses precise javascript selectors is a good habit to get into.

4. Adding list elements dynamically. There are another 5000 <li> elements that are embedded in the page itself in addition to the 5000 that the javascript adds. I deleted the in page elements and modified the javascript function to add 10000 elements -- preserving the look of the page.
While this makes the file size of the page much smaller and thus able to be delivered to a client faster on slower wifi, it increases the runtime of the javascript function. I reasoned however that it's better to increase client side processing than server side processing -- one can assume that someone's device will almost always be faster than someones internet connection. When testing, I noticed that the page "processed" for longer, but I could see content and start clicking on list elements almost instantly, which is a good thing.

5. Removing White space. The last change I made was to remove all whitepspace and returns from the document. This further reduces the size of the file and makes it easier for the server to deliver it. On my machine with my internet connection it wasn't a noticeable difference, but it's a good habit to get into and might make more of a difference on slower internet or with much bigger files.

I saved the non minified version of the lab5 code as lab5 readable. Lab5.html contains the minified code with my other performance improvements and Lab5Start.html contains the starter code without any performance improvements.

