<?php
date_default_timezone_set(‘Asia/Bangkok’);
$servername =”127.0.0.1”;
$username = “root”;
$password = ““;
$dbname = “air_meter_pm2.5”;
$now = new DateTime();
$pm25 = $_REQUEST[‘pm25’];
$pm10 = $_REQUEST[‘pm10’];
$conn = mysql_connect(“localhost”,”root”,””);
if (!$conn)
{
die(‘Could not connect: ‘ . mysql_error());
}
$con_result = mysql_select_db($dbname, $conn);
if(!$con_result)
{
die(‘Could not connect to specific database: ‘ . mysql_error());
}
$datenow = $now->format(“Y-m-d H:i:s”);
$hvalue = $value;
if(!empty($pm25) && !empty($pm10)){
$sql =”insert into pm25(id,pm25,pm10,date) values ( null,$pm25,$pm10,’$datenow’)”;
//echo $sql;
$result = mysql_query($sql);
if (!$result) {
die(‘Invalid query: ‘ . mysql_error());
}
echo “<h1 align=center>THE DATA HAS BEEN SENT!!</h1>”;
mysql_close($conn);
} else{
//
}
?>