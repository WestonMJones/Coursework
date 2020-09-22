<?php

  require 'config.php';

  $host = $config['DB_HOST'];
  $database = $config['DB_NAME'];
  $user = $config['DB_USERNAME'];
  $password = $config['DB_PASSWORD'];
  $charset = $config['DB_COL'];



  // Create connection
  $conn = new mysqli($host, $user, $password, $database);
  // Check connection
  if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
  } 

  $sql = "INSERT INTO labs (title, descr, link)
  VALUES ('Course Schedule','Overview of the class','https://lms.rpi.edu./bbcswebdav/pid-143106-dt-content-rid-4857833_1/xid-4857833_1')";

  if ($conn->query($sql) === TRUE) {
      echo "New record created successfully";
  } else {
      echo "Error: " . $sql . "<br>" . $conn->error;
  }

  $conn->close();
  header("Location: main.php");





?>





