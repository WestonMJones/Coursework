
// Initalize a global variable to keep track of which song in the list should be displayed.
var count=1;


$(document).ready(function() {


  // Everytime the cover art is clicked...
  $("#coverart").click(function(){

    // Keep track of which JSOn data we're on
    var current = 1;

    // Use AJAX to grab the JSON data.
    $.ajax({
      type: "GET",
      url: "lab4.json",
      dataType: "json",
      success: function(responseData, status){


        $.each(responseData.items, function(i, item) {
          
          // Grab the next song in the list.
          if (count==current) {
            
            // Update the HTML to reflect the new song
            $("#site").attr("href",item.website);
            $("#site").attr("target","_blank");
            $("#coverart").attr("src",item.cover_art);
            $("#title").html(item.track_name);
            $("#artist").html(item.artist);
            $("#album").html(item.album);
            $("#date").html(item.date);

            // Use another loop for the genre array
            var genre_list = "";

            $.each(item.genres, function(g, genre) {
              genre_list += "<li>"+genre+"</li>"
            });

            $("#genres").html(genre_list);

            // Update the count so the next song is grabbed the next time.
            if (count==6) {
              count = 1;
            } else {
              count++;
            }
            current=7;

          } else {
            current++;
          }

        });
    }, error: function(msg) {
              // there was a problem
        alert("There was a problem: " + msg.status + " " + msg.statusText);
      }
    });

    
  }); 
});