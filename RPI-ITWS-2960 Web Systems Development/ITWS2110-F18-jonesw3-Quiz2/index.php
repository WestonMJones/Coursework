<!DOCTYPE html>
<html lang="en">
  <head>
    <title>Index Page</title> 
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="author" content="Weston Jones"> 

  	
  </head>

  <body>

    Existing Members:
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
          

          $stmt = $connection->prepare('SELECT * FROM users');
          $stmt->execute(['ID' => $user]);
          
          
        }

      } catch (\PDOException $e) {
          echo 'ERROR: ' . $e->getMessage();
      }


    ?>









    <form action="add_action.php" method="post">
      Project Name: <input type="text" name="uname"><br>
      Description: <input type="text" name="fname"><br>
      Members (enter IDs separated by spaces): <input type="text" name="mname"><br>




      <input type="submit">
    </form>



  </body>

  
  
</html>