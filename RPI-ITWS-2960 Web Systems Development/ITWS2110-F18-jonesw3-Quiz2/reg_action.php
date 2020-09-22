<?php
$servername = "localhost";
$username = "root";
$password = "73Weserrang";
$dbname = "itws2110-f18-jonesw3-quiz2";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "INSERT INTO users (userID, firstName, lastName,nickName,pass)
VALUES ('".$_POST['uname']."', '".$_POST['fname']."', '".$_POST['lname']."','".$_POST['nname']."','".$_POST['pass']."')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
header("Location: index.php");
?>

