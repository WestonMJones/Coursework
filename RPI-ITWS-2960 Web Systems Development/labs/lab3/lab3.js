


window.onload = function() {

	// Drive the recursive function by pointing it at the document root
	var start = document.documentElement;
	document.getElementById("info").innerHTML="";

	// Call the recursive DOM tree generator
  	printDOMTree(0,start);

  	partThree();
  
};

function printDOMTree(depth,element) { 

	// Part 2 Code
	element.addEventListener("click", function(){ alert(element.tagName); });

	// Part 1 Code

	// Calculate number of dashes
	var dashes = "-";
	dashes = dashes.repeat(depth);
	dashes += element.tagName;
	dashes += "\n";

	// Append current element onto DOM tree
	document.getElementById("info").innerHTML += dashes;

	// Increase depth by 1
	depth=depth+1

	// Do another recursive DFS on all children of current node
	var children = element.children;
	for (var i = 0; i < children.length; i++) {
    	printDOMTree(depth,children[i]);
	}

};

function partThree() {

	// Create a new node at the end of the body and bind text to it.
	var quote = document.getElementsByTagName("BODY")[0].appendChild(document.createElement('h1'));
	var text = document.createTextNode("To be or not to be, that is the question...");
	quote.appendChild(text);

	// Bind event listeners and styling to every div
	var divs = document.getElementsByTagName("div");
	for (var i = 0; i < divs.length; i++) { 
		// First the on mouse overs
		
	    divs[i].addEventListener("mouseover", function() {	this.style.background = "cyan";
	    													this.style.margin = "0px 10px";
														});

	    // Next the mouse out listeners
	    divs[i].addEventListener("mouseout", function() {	this.style.background = "white";
	    													this.style.margin = "0px 0px";
														});

	}

}