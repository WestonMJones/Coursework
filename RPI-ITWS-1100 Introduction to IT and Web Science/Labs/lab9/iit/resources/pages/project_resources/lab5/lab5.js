/* Lab 5 JavaScript File 
   Place variables and functions in this file */

function identify() {
	var first = document.getElementById("firstName").value;
	var last = document.getElementById("lastName").value;
	var nick = document.getElementById("pseudonym").value;

	if (first!="" && last!="" && nick !="") {
		alert(first + " " + last + " is " + nick);
	} else {
		alert("Incomplete Info!");
	}

}

function clearContents(formObj) {
  	if (formObj.value == "Please enter your comments") {
  		formObj.value = "";
  	}
}

function validate(formObj) {
  // put your validation code here
  // it will be a series of if statements
  
  if (formObj.firstName.value == "") {
    alert("You must enter a first name");
    formObj.firstName.focus();
    return false;
  } else if (formObj.lastName.value == "") {
  	alert("You must enter a last name");
  	formObj.lastName.focus();
  	return false;
  } else if (formObj.title.value == "") {
  	alert("You must enter a title");
  	formObj.title.focus();
  	return false;
  } else if (formObj.org.value == "") {
  	alert("You must enter an organization");
  	formObj.org.focus();
  	return false;
  } else if (formObj.pseudonym.value == "") {
  	alert("You must enter a pseudonym");
  	formObj.pseudonym.focus();
  	return false;
  } else if (formObj.comments.value == "") {
  	alert("You must enter some comments");
  	formObj.comments.focus();
  	return false;
  } else {
  	alert("Submitted successfully!");
  	return true;
  }  
}
