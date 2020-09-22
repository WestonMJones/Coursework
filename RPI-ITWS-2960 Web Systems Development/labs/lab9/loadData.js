$(document).ready(function() {
  please();

  $("#reload").click(function(){

    please();
  });


  $("#logout").click(function(){
    $(location).attr('href', 'index.php');
  });


  $("#store").click(function(){

    $(location).attr('href', 'insert.php');

  });

  



});


function please() {

  var output = "<h2>Nav Bar</h2>";

  $.getJSON("data.js", function(result){

    var count = 0;
    var output = "";

    $.each(result, function(i, item){
      if (count==0) {
        count++;
      } else if (count==1) {
        output+="<h3>Lecture</h3><div id='lecs'>";
        for (i = 0; i < item.length; i++) { 
          output +="<h4 id='"+i+"'>-" + item[i].title + "</h4>";
        }
        output+="</div>";
        count++;
      } else {
          output+="<br><h3>Labs</h3><div id='labs'>";
         for (i = 0; i < item.length; i++) { 
          output +="<h4 id='"+i+"'>-" + item[i].title + "</h4>";
        }
        output+="</div>";
      }
    });
    $('#nav').html(output);
  });


}



$(document).on( "click", "#lecs h4", function(){

  var matchID = this.id

  $.getJSON("data.js", function(result){
    var count = 0;
    $.each(result, function(i, item){
      if (count!=1) {
        count++;
      } else if (count==1) {
        for (i = 0; i < item.length; i++) { 
          currentID = "";
          currentID += i;
          if (matchID.valueOf()==currentID.valueOf()) {
            $("#title").text("Title: "+item[i].title);
            $("#desc").text("Description: "+item[i].desc);
            $("#link").text("Link: "+item[i].link);

          }
        }
        count++;
      }

    });
  });

} );


$(document).on( "click", "#labs h4", function(){
 
  var matchID = this.id

  $.getJSON("data.js", function(result){
    var count = 0;
    $.each(result, function(i, item){
      if (count!=2) {
        count++;
      } else if (count==2) {
        for (i = 0; i < item.length; i++) { 
          currentID = "";
          currentID += i;
          if (matchID.valueOf()==currentID.valueOf()) {
            $("#title").text("Title: "+item[i].title);
            $("#desc").text("Description: "+item[i].desc);
            $("#link").text("Link: "+item[i].link);

          }
        }
      }

    });
  });

} );

