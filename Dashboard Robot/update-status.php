<?php
include 'db_config.php';

// Ambil data dari request POST NodeMCU
$mode = $_POST['modeOperasi'];
$arah = $_POST['arahApi'];
$pompa = $_POST['pompaStatus'];
$base = $_POST['baseAngle'];
$shoulder = $_POST['shoulderAngle'];
$elbow = $_POST['elbowAngle'];
$wrist = $_POST['wristAngle'];
$kiri = $_POST['sensorKiri'];
$kanan = $_POST['sensorKanan'];
$tengah = $_POST['sensorTengahAnalog'];

// Update satu baris (id=1) di database
$sql = "UPDATE status_robot SET
            modeOperasi = ?, arahApi = ?, pompaStatus = ?,
            baseAngle = ?, shoulderAngle = ?, elbowAngle = ?, wristAngle = ?,
            sensorKiri = ?, sensorKanan = ?, sensorTengahAnalog = ?
        WHERE id = 1";

$stmt = $conn->prepare($sql);
$stmt->bind_param("sssiiiiiii",
    $mode, $arah, $pompa,
    $base, $shoulder, $elbow, $wrist,
    $kiri, $kanan, $tengah
);

if ($stmt->execute()) {
  echo "Data berhasil diperbarui";
} else {
  echo "Error: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>