// Wait until the document is ready
$(document).ready(function() {

    // Use a jQuery Ajax function
    $.ajax({
      type: "GET",
      url: "../js/labs.js",
      dataType: "json",
      success: function(responseData, status){
        var output = "";  

        // Loop through the array of lab data items
        $.each(responseData.items, function(i, item) {

          // Wrap the data in html consistent with the aesthetic of my website.

          // Lab titles get the <h2> heading to make them stand out and demarcate separate items
          output +="<h2>" + item.name + ":</h2>";

          // Extra details and links to relevant files just the simple <p> tags.
          output += "<p>" + item.desc + "</p>";

          // Links get a new line though, so separate them from the lab descriptions.
          output += "<p>You can find a link to the project files <a href="+item.URL+">"+"here:"+"</a></p>";
        });
        // Apply the formatted HTML to the div holding all the labs.
        $('#projects_WORK_PLZ').html(output);
      }, error: function(msg) {
              // there was a problem
        alert("There was a problem: " + msg.status + " " + msg.statusText);
      }
    });
});