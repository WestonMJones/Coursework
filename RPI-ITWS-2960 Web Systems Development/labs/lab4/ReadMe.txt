The instructions for this lab were somewhat unclear.

We're expected to display the list of songs as they in Lab 2 dynamically using AJAX, but the HTML we're given only has the IDs and placeholders for a single song. I suppose I could have used javascript to duplicate the IDs and given HTML tags 5 times over, but I thought we were supposed to leave the 
given HTML the way we found it, espically since the instructions mention using the attr function to modify existing HTML element attributes.

Instead, I just coded the AJAX request so that it only displays the data for one song at a time. Clicking on the album art again loads the website
of the current artist in a new tab and also grabs the data for the next song then used the attr function to update the HTML. When you reach the end of the song list, it goes back to the first song in the list.

I wasn't sure if this is exactly what we were supposed to do, but my code still uses AJAX to load data dynamically and does it in a way that is
argueably more complicated than the traditional "for each json item in returned json, generate tags to display the data," so hopefully my mastery of the concept is demonstrated.

Aside from the AJAX stuff, I used the CSS from lab 2 to format the look of the song list in roughly the same way.