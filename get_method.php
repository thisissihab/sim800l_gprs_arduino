<?php
$servername = "localhost";

  // REPLACE with your Database name
$dbname = ""; //your database name inside the quotation
  // REPLACE with Database user
$username = ""; // your database username
  // REPLACE with Database user password
$password = ""; //your database user password
$val = $_GET['val'];

echo 'From Server-> Received: '.$val;

$conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO gprs(val) VALUES ('$val')";

if ($conn->query($sql) === TRUE) {
  return "New record created successfully";
}
else {
  return "Error: " . $sql . "<br>" . $conn->error;
}
$conn->close();


?>