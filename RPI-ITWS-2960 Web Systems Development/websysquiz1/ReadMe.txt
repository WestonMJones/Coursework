I believe I managed to finish all the parts of the lab.

First, was able to get the website served from a virtual host. I edited the vhosts file from my apache conf and the windows hosts files as well.

For the purposes of this quiz, I created the my-restaurant directory on my desktop so I could easily refer back to it quickly -- that's where the paths in my hosts files point to fyi.

I've also included a screenshot of my rendered site -- note the URL on top -- it is just http://my-restuarant.


I created a JSON file with four common dishes that I wouldn't have to waste much time specifically choosing. I included the main content that would be displayed in an array called "items". Note that my food pictures are URLs to the web, not image files I eneded up saving.

FOr my HTML, I used an HTML5 doctype, so to use the up to date standard. I used a few divs and some CSS to add a little bit of style and to make a clear title and content section on the website. Note that I used a image from the web to add a patterned background to the top of my website. The image is included in my img resources folder.

For the dynamic menu generation, I used jQuery and AJAX to loop through the items in my JSON file and output each one -- wrapping them in HTML tags
as I went to help with styling later on.


