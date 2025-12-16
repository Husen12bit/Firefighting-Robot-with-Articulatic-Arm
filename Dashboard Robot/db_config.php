<?php
$servername = "localhost";
$username = "root"; // Ganti jika beda
$password = ""; // Ganti jika beda
$dbname = "db_robot";

// Buat koneksi
$conn = new mysqli($servername, $username, $password, $dbname);

// Cek koneksi
if ($conn->connect_error) {
  die("Koneksi gagal: " . $conn->connect_error);
}
?>