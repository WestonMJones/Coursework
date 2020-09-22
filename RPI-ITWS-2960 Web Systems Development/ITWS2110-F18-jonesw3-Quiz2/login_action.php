<?php

      $host = '127.0.0.1';
      $database = 'itws2110-f18-jonesw3-quiz2';
      $user = 'root';
      $password = '73Weserrang';
      $charset = 'utf8mb4';

      $dsn = "mysql:host=$host;port=3306;dbname=$database;charset=$charset";

      try {

        $connection = new PDO($dsn, $user, $password);

        if ($connection) {
          //echo "Connected";
          $user = $_POST['name'];
          $pass = $_POST['pass'];

          $stmt = $connection->prepare('SELECT * FROM users WHERE userID = :ID');
          $stmt->execute(['ID' => $user]);
          
          $record = $stmt->fetch();
          $stored_user = $record['userID'];
          $stored_pass = $record['pass'];

          //echo $entered_user;
          //echo $entered_pass;



          if ($user==$stored_user) {
            //echo "<br>Found matching user";
            if ($pass==$stored_pass) {
              //echo "<br> Passwords match!";
              header("Location: index.php");
            } else {
              echo '<script language="javascript">';
              echo 'alert("Error, try logging in again!")';
              echo '</script>';
              header("Location: login.php");
            }
          } else {
            header("Location: register.php");
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





