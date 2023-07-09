<?php 


$servername = "localhost";
$username = "id20731543_sensor";
$password = "@Password25";
$database = "id20731543_sensor";

$conn = mysqli_connect($servername, $username, $password, $database);

function query($query){
	global $conn;
	$hasil = mysqli_query($conn, $query);
	$rows = [];
	while( $row = mysqli_fetch_assoc($hasil)){
		$rows[] = $row;
	}
	return $rows;
}


function hapus($id){
	global $conn;
	mysqli_query($conn, "DELETE FROM SensorData WHERE id = $id");

return mysqli_affected_rows($conn);
}

?>