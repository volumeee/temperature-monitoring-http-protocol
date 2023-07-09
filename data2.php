<?php 

$servername = "localhost";
$username = "id20731543_sensor";
$password = "@Password25";
$database = "id20731543_sensor";

$conn = mysqli_connect($servername, $username, $password, $database);
$sql = "SELECT reading_time, value3 FROM SensorData";
$result = mysqli_query($conn, $sql);

// Menyimpan data ke dalam array
$data = array();
while ($row = mysqli_fetch_assoc($result)) {
    $data[] = array($row['reading_time'], $row['value3']);
}

// Menutup koneksi ke database
mysqli_close($conn);

// Mengembalikan data dalam format JSON
echo json_encode($data);
?>