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

$sql = "INSERT INTO projects (projectID, name, description)
VALUES ('1',".$_POST['uname']."', '".$_POST['fname']."')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
header("Location: index.php");
?>

