$(document).ready(function() {
    $.ajax({
      type: "GET",
      url: "../js/labs.js",
      dataType: "json",
      success: function(responseData, status){
        var output = "";  
        $.each(responseData.items, function(i, item) {
          output +="<h2>" + item.name + ":</h2>";
          output += "<p>" + item.desc + "</p>";
          output += "<p>You can find a link to the project files <a href="+item.URL+">"+"here:"+"</a></p>";
        });
        output += "";
        $('#projects_WORK_PLZ').html(output);
      }, error: function(msg) {
              // there was a problem
        alert("There was a problem: " + msg.status + " " + msg.statusText);
      }
    });
});