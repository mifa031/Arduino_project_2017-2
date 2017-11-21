<?
header('Content-Type: application/json');
$connect=mysql_connect("localhost","ce2017","20172ssu");
$result=mysql_select_db("ce2017",$connect);
$query="select room_info.room_num, room_info.room_name, room_info.status, lec_info.lec_num, lec_info.lec_name, lec_time.day, lec_time.start, lec_time.end from room_info join lec_info using(room_num) join lec_time using(room_num,lec_num) order by room_num, day_num, start";
$sql_result=mysql_query($query, $connect);

while($re=mysql_fetch_array($sql_result)){
	$array[] = array('room_num'=>$re[0], 'room_name'=>$re[1], 'status'=>$re[2], 'lec_num'=>$re[3], 'lec_name'=>$re[4], 'day'=>$re[5], 'start'=>$re[6], 'end'=>$re[7]);
}
echo json_encode($array, JSON_UNESCAPED_UNICODE);
?>