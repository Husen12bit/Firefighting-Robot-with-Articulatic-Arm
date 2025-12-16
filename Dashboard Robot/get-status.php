<?php
include 'db_config.php';

header('Content-Type: application/json');

$sql = "SELECT * FROM status_robot WHERE id = 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
  // Ambil data dan kirim sebagai JSON
  $row = $result->fetch_assoc();
  echo json_encode($row);
} else {
  echo json_encode(["error" => "Data tidak ditemukan"]);
}

$conn->close();

?>
