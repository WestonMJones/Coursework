<?php

  require 'config.php';

  $host = $config['DB_HOST'];
  $database = $config['DB_NAME'];
  $user = $config['DB_USERNAME'];
  $password = $config['DB_PASSWORD'];
  $charset = $config['DB_COL'];

  $dsn = "mysql:host=$host;port=3306;dbname=$database;charset=$charset";

  try {

    $connection = new PDO($dsn, $user, $password);

    if ($connection) {

      //echo "Connected";
      $user = $_POST['name'];
      $pass = $_POST['pass'];

      $stmt = $connection->prepare('SELECT * FROM users WHERE name = :userName');
      $stmt->execute(['userName' => $user]);

      $record = $stmt->fetch();
      $stored_user = $record['name'];
      $stored_pass = $record['pass'];

      //echo $stored_user;
      //echo $stored_pass;

    if ($user==$stored_user) {
       
       if ($pass==$stored_pass) {
          header("Location: main.php");
       } else {
        header("Location: index.php");
        echo "<br>Entered wrong info!";
       }

    } else {
      header("Location: index.php");
      echo "<br>Entered wrong info!";
    }

    }
  } catch (\PDOException $e) {

    echo 'ERROR: ' . $e->getMessage();

  }


// $stmt = $connection->('SELECT * FROM TEST WHERE ID = :ID');
// $stmt->execute(['ID' => $id]);
// $user = $stmt->fetch();

/* $stmt = "CREATE TABLE ORDERS(

ID INT(11) AUTO_INCREMENT PRIMARY KEY,
MENUITEM INT(11),
FOREIGN KEY (MENUITEM)
REFEREMCES MENU(ID)
ON DELETE CASCADE
)"
$connection -> exec($stmt);*/

?>





