$(document).ready(function() {
    $.ajax({
      type: "GET",
      url: "../data/dishes.js",
      dataType: "json",
      success: function(responseData, status){
        var output = "";  
        $.each(responseData.items, function(i, item) {
          output +="<div class='item'>";
          output +="<img src="+item.image+">";
          output +="<h1>" + item.name + ""+ "</h1>";
          output +="<p>" + item.category + " / " + item.cuisine + "</p>";
          output +="<p>" + item.description + " -- " + item.price + "</p>";
          output +="<p>Contains: " + item.ingredients  + "</p>";
          output +="<br><br></div>";
        });
        output += "";
        $('#menu').html(output);
      }, error: function(msg) {
              // there was a problem
        alert("There was a problem: " + msg.status + " " + msg.statusText);
      }
    });
});