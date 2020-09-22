1) Explain what each of your classes and methods does, the order in which methods are invoked, and the flow of execution after one of the operation buttons has been clicked.

	The abstract class Operation provides and a template and some definitions for the rest of the named operation classes (adition, subtraction, etc). It contains
	the operand variables and a construtor function that makes sure the operands are numbers. It also contains the templated functons operate and getEquation.

	The named operation classes (addition, subtraction, etc), inherit the variables and constructor function from the operation abstract class. Each class has it's own definitions for the operate method which returns the result of the numberical operations on the two operands and the getEquation function which returns a string representation showing the numerical operation on the two operands and the result.

	When a button on the form is clicked, the operation is stored in the POST variable. The code checks the operation name, then initializes the correct
	named operation class. Next the code checks to see if an operation class has been initialized, and if so, calls the getEquation method which calls the operate method to generate the equation string. This string is echoed above the "calculator."

2) Also explain how the application would differ if you were to use $_GET, and why this may or may not be preferable.

	If GET were used, the buttons values would be encoded into the URL of the page on each submission rather than in a the HTTP request as in POST.
	While less secure, GET is simpler and more convient because its easier to store user input (It's literally in the URL of the page, so refreshing / navigating forward and back is easier). For a simple application like this, that doesn't need to be very secure, GET probably makes a bit more sense. 

3) Finally, please explain whether or not there might be another (better +/-) way to determine which button has been pressed and take the appropriate action

	To further modularize the code, I suppose the whole "which operator to use" process could be put inside a single class that would take two operators and the operation passed in from the POST variable. If this code were to be expanded upon or extended in some way, having the long series
	of if statements in a single place would reduce the complexity of the code. 

Questions inside Php file:

"// Then tell me if there is a way to do this without the ifs" (referring to the code from part 2)

	See above!
