$.fn.hexed = function(settings) {
  //initial settings and variables to keep track of turns
  var difficulty = 5;
  var turns=0;
  var maxTurns=10;
  var totalScore=0;

  //function to create the landing page of the website
  //where the user selects difficulty and number of turns before starting the game
  function init(init) {
    $(init).html(""); //clear out document to make room for the game
    //reset initial settings
    maxTurns=10;
    turns=0;
    totalScore=0;
    difficulty=5;

    //create the html for the starting page with two sliders
    $(init).append('<h2 class="demoHeaders">Hexed</h2>');
    $(init).append('<div id="difficultySlider" class="slider"></div>');
    $(init).append('<label for="difficultyAmount">Difficulty Level: </label>');
    $(init).append('<label id="difficultyAmount">5</label>')
    $(init).append('<p></p>')
    $(init).append('<div id="turnsSlider" class = "slider"></div>');
    $(init).append('<label for="turnsAmount">Number of Turns: </label>');
    $(init).append('<label id="turnsAmount">10</label>')
    $(init).append('<p></p>');
    $(init).append('<button id="start">Start</button>');
    
    //create the slider for the difficulty of the game
    $("#difficultySlider").slider({
      orientation: "horizontal",
      range: "min",
      max: 10,
      min: 1,
      value: 5,
      slide: function(event, ui) {
          $("#difficultyAmount").html("" + ui.value);
          difficulty = ui.value;
      }
    });

    //create the slider for the amount of turns in the game
    $("#turnsSlider").slider({
      orientation: "horizontal",
      range: "min",
      min: 1,
      max: 100,
      value: 10,
      slide: function(event, ui) {
          $("#turnsAmount").html("" + ui.value);
          maxTurns = ui.value;
      }
    });

    //add event listener to start button to start the game
    $("#start").click(function() {
      start(init);
    });
  }
  
  init(this); //initialize the page

  //function to build the game page
  //contains three sliders and two boxes of color, one for the guess and one for the target
  function start(init) {
    $(init).html(""); //clear out page to build game page
    

    //add html for the page
    //includes the sliders, color boxes, and scores table
    $(init).append("<h2 class='demoHeaders'>Hexed</h2>");
    $(init).append('<label for="redAm">R: </label>');
    $(init).append('<label id="redAm">255</label>');
    $(init).append('<div id="red"></div>');
    $(init).append('<label for="GreenAm">G: </label>');
    $(init).append('<label id="GreenAm">255</label>');
    $(init).append('<div id="green"></div>');
    $(init).append('<label for="blueAm">B: </label>');
    $(init).append('<label id="blueAm">255</label>');
    $(init).append('<div id="blue"></div>');
    $(init).append('<label id="time"></label>');
    $(init).append('<label id="endTime"></label>');
    $(init).append('<br>');
    $(init).append('<button id="submit">Submit</button> ');
    $(init).append('<div class="container"><h3>Guess</h3><div id="guess" class="ui-widget-content ui-corner-all"></div></div>');
    $(init).append('<div class="container"><h3>Target</h3><div id="target" class="ui-widget-content ui-corner-all"></div></div>');
    $(init).append('<table id="board"> </table>');

    //when the document is ready, change css to make the colors of the squares
    $(document).ready(function(){
        $("#guess").css("background-color", "rgb(" + 255 + "," + 255 + "," + 255 + ")");
        $("#target").css("background-color", randomColor());
        $("#time").html(Date.now); //start timer for first round
        $("#board").append("<tr>;" +
                    "<th> Turn</th>;" +
                    "<th> Score</th>;" +
                    "<th> Time</th>;" +
                    "<th> Total Score</th>;" +
                    "</tr>;");
        
    });
   
    //create red slider, update the guess color square when this slider is changed
    $( "#red" ).slider({
        orientation: "horizontal",
        range: "min",
        max: 255,
        value: 255,
        slide: function(event, ui) {
            $("#redAm").html("" + ui.value);
            var redVal=document.getElementById("redAm").innerHTML;
            var blueVal=document.getElementById("blueAm").innerHTML;
            var greenVal=document.getElementById("GreenAm").innerHTML;
            $("#guess").css("background-color", "rgb(" + redVal + "," + greenVal + "," + blueVal + ")");
        }
    });

    //create blue slider, update the guess color square when this slider is changed
    $( "#blue" ).slider({
        orientation: "horizontal",
        range: "min",
        max: 255,
        value: 255,
        slide: function(event, ui) {
            $("#blueAm").html("" + ui.value);
            var redVal=document.getElementById("redAm").innerHTML;
            var blueVal=document.getElementById("blueAm").innerHTML;
            var greenVal=document.getElementById("GreenAm").innerHTML;
            $("#guess").css("background-color", "rgb(" + redVal + "," + greenVal + "," + blueVal + ")");
        }
    });

    //create green slider, update the guess square when slider moves
    $( "#green" ).slider({
        orientation: "horizontal",
        range: "min",
        max: 255,
        value: 255,
        slide: function(event, ui) {
            $("#GreenAm").html("" + ui.value);
            var redVal=document.getElementById("redAm").innerHTML;
            var blueVal=document.getElementById("blueAm").innerHTML;
            var greenVal=document.getElementById("GreenAm").innerHTML;;
            $("#guess").css("background-color", "rgb(" + redVal + "," + greenVal + "," + blueVal + ")");
        }
    });

    //when the submit button is clicked, stop timer and calculate score
    $("#submit").click(function(){

        //Calculates time taken for turn.
        turns+=1;
        
        $("#endTime").html(Date.now); //stops timer

        //find the final values of the user guess
        var redVal=document.getElementById("redAm").innerHTML;
        var blueVal=document.getElementById("blueAm").innerHTML;
        var greenVal=document.getElementById("GreenAm").innerHTML;

        //calculate the difference in start and end time
		    var timeTakenMs= parseInt($("#endTime").html()) - parseInt($("#time").html());

        //calculate the score based on the time, difficulty, and guess values
        var scoreTurn = score(timeTakenMs,difficulty, redVal, greenVal, blueVal);

        //update total score and alert the user on how they did this round
        totalScore+=scoreTurn;
        alert("Correct Answer:  " + document.getElementById("target").style.backgroundColor + "\n" + "Your answer:  " + document.getElementById("guess").style.backgroundColor + "\n" + "Points:  " + scoreTurn);
    
        $("#target").css("background-color",randomColor() ); //reset guess square
        $("#time").html(Date.now); //resart timer

        //update the scoreboard to hold latest rounds info
        $("#board").append("<tr>;" +
                "<td> " + turns + "</td>;" +
                "<td> " + scoreTurn + "</td>;" +
                "<td> " + timeTakenMs + "ms" + "</td>;" +
                "<td> " + totalScore + "</td>;" +
                "</tr>;");

        //if this was the last turn, show final score and then restart the page 
        //to the landing page where difficulty and turn count is selected
        if(turns >= maxTurns){
            alert("Final Score: " + totalScore);
            console.log(document.getElementById("hexed"));
            location.reload();
        }
    });
  }
  
  //function to calculate the score for a given guess
  //takes into account the time the guesser took, the difficulty setting, 
  // and the rgb values of the guess as arguments of function
  function score(time_taken, difficulty, r, g, b) {
    
    //find the values of the target color square
    var targetColor = document.getElementById("target").style.backgroundColor;
    var targetVals = targetColor.substring(targetColor.indexOf('(') + 1, targetColor.length - 1).split(', ');
    
    //calculate percent off for the three colors and then average them
    var rpo = (Math.abs(r - targetVals[0])/255) * 100;
    var gpo = (Math.abs(g - targetVals[1])/255) * 100;
    var bpo = (Math.abs(b - targetVals[2])/255) * 100;
    var avgPercOff = Math.floor((rpo + gpo + bpo) / 3);

    //calculate total score based on formula given
    var score = ((15 - difficulty - avgPercOff) / (15 - difficulty)) * (15000 - time_taken);
    score = Math.max(0, score);

    score = Math.round(100 * score)/100; //round to nearest hundreth

    return score;
  }

  //generate a random color and return it in terms of css color settings
  function randomColor() {
    var r = Math.floor(Math.random() * 256);
    var g = Math.floor(Math.random() * 256);
    var b = Math.floor(Math.random() * 256);
    return "rgb(" + r + ", " + g + ", " + b + ")";
  }

}
var settings = {
    "difficulty": 5,
    "turns": 10
}

$("#hexed").hexed(settings);
