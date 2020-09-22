(function ( $ ) {
 
    $.fn.hexed = function( settings ) {


 
            // Set settings
            var options = $.extend({
                // These are the defaults.
                difficulty: 5,
                turns: 10
            }, settings );


            // Set variables
            var turn = 1;
            var score = 0;
            var last = 0;

            var red=128;
            var green=128;
            var blue=128;

            var tred = 0;
            var tgreen = 0;
            var tblue = 0;

            // Clear out existing content. 
            this.empty();

            // Generate game board.
            this.append('<div id="gameboard"> <div id="guess" class=swatch> <h3>Guess:</h3> <div class="containerz"></div> </div> <div id="target" class="swatch"> <h3>Target:</h3> <div class="containerz"></div> </div> <h4 id="red-label">Red: 128</h4> <div id="red"></div> <h4 id="green-label">Green: 128</h4> <div id="green"></div> <h4 id="blue-label">Blue: 128</h4> <div id="blue"></div> <button id="calculate">Got it!</button><br> <h5 id="total-score">Total Score: 0</h5> <h5 id="last-score">Last Color\'s Score: 0 </h5> <h5 id="turn">Turn Number: X of Y</h5> <h5 id="difficulty">Difficulty: X</h5> </div> ');
        
            // Create red slider
            $( "#red" ).slider({
                orientation: "horizontal",
                range: "min",
                max: 255,
                value: 128,
                slide: function(event, ui) {
                    $("#red-label").html("Red: " + ui.value);
                    red = ui.value;
                    $("#guess .containerz").css("background-color", "rgb(" + red + "," + green + "," + blue + ")");



                }
            });

            // Create green slider
            $( "#green" ).slider({
                orientation: "horizontal",
                range: "min",
                max: 255,
                value: 128,
                slide: function(event, ui) {
                    $("#green-label").html("Green: " + ui.value);
                    green = ui.value;
                    $("#guess .containerz").css("background-color", "rgb(" + red + "," + green + "," + blue + ")");

                }
            });

            // Create blue slider
            $( "#blue" ).slider({
                orientation: "horizontal",
                range: "min",
                max: 255,
                value: 128,
                slide: function(event, ui) {
                    $("#blue-label").html("Blue: " + ui.value);
                    blue = ui.value;
                    $("#guess .containerz").css("background-color", "rgb(" + red + "," + green + "," + blue + ")");
                }
            });

            // Set turn, difficulty, and score info
            $('#turn').html("Turn Number: "+turn+" of "+options.turns);
            $('#difficulty').html("Difficulty: "+options.difficulty);
            $('#total-score').html("Total Score: "+score);
            $('#last-score').html("Last Color's Score: "+last);
            $("#guess .containerz").css("background-color", "rgb(" + red + "," + green + "," + blue + ")");

            // Set intial colors of guess and target
            tred = Math.floor(Math.random()*(256));
            tgreen = Math.floor(Math.random()*(256));
            tblue = Math.floor(Math.random()*(256));
            $("#target .containerz").css("background-color", "rgb(" + tred + "," + tgreen + "," + tblue + ")");

            // Record start time

            var time1 = Date.now();

            // Wait for submission
            $("#calculate").click(function() {
                // Calulcate elasped time
                var time2 = Date.now();
                var elapsed = time2-time1;


                // Increment turn count 
                turn = turn + 1;

                // calculate score
                //(|expected value – actual value| / 255) * 100 
                var percentoff_red = (((Math.abs(tred - red)) / 255) * 100);
                var percentoff_green = (((Math.abs(tgreen - green)) / 255) * 100);
                var percentoff_blue = (((Math.abs(tblue - blue)) / 255) * 100);
                var percentoff_avg = ((percentoff_red+percentoff_green+percentoff_blue)/3)

                //((15 – difficulty – percent_off) / (15 – difficulty)) * (15000 – milliseconds_taken)
                var temp = ((15 - options.difficulty - percentoff_avg) / (15 - options.difficulty)) * (15000 - elapsed);

                // get rid of negatives and round
                temp = Math.max(0,Math.ceil(temp * 100) / 100);
                score = score + temp;
                last = temp;

                // Show result.
                alert("You guessed: ("+red+","+green+","+blue+").\nCorrect response was: ("+tred+","+tgreen+","+tblue+")\nYou earned "+last+" points!");

                // Update game state
                $('#turn').html("Turn Number: "+turn+" of "+options.turns);
                $('#total-score').html("Total Score: "+score);
                $('#last-score').html("Last Color's Score: "+last);
                tred = Math.floor(Math.random()*(256));
                tgreen = Math.floor(Math.random()*(256));
                tblue = Math.floor(Math.random()*(256));
                $("#target .containerz").css("background-color", "rgb(" + tred + "," + tgreen + "," + tblue + ")" );
                time1 = Date.now();

                if (turn>options.turns) {
                    alert("Game Over. Final score was: "+score);
                    location.reload();
                }


            });
            

    };
} ( jQuery ));

