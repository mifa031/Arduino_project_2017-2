<?
$day = array("sun","mon","tue","wed","thu","fri","sat");
if(!isset($_GET["status"])){
	$room_num = $_GET["room_num"];
	$connect=mysql_connect("localhost","ce2017","20172ssu");
	$result=mysql_select_db("ce2017",$connect);
	$query="select * from lec_time where room_num=".$room_num;
	$sql_result=mysql_query($query, $connect);
	$time_now = date("H:i:s");
	$day_now = $day[date('w')];
	while($re=mysql_fetch_array($sql_result)){
		$day_db = $re[2];
		$time_start = $re[3];
		$time_end = $re[4];
		if($day_now == $day_db){
			$time_now = date("H:i:s",time()+30);
			if(strtotime($time_start) <= strtotime($time_now)){
				$time_now = date("H:i:s");
				if(strtotime($time_end) >= strtotime($time_now)){
					echo 'lec';
					$query = "update room_info set status = 'lec' where room_num=".$room_num;
					mysql_query($query, $connect);
				}
			}
		}
	}
}else{
	$room_num = $_GET["room_num"];
	$status = $_GET["status"];
	$connect=mysql_connect("localhost","ce2017","20172ssu");
	$result=mysql_select_db("ce2017",$connect);
	$query="select * from lec_time where room_num=".$room_num;
	$sql_result=mysql_query($query, $connect);
	$time_now = date("H:i:s");
	$day_now = $day[date('w')];
	while($re=mysql_fetch_array($sql_result)){
		$day_db = $re[2];
		$time_start = $re[3];
		$time_end = $re[4];
		if(($day_now != $day_db) || (strtotime($time_start) > strtotime($time_now)) || (strtotime($time_end) < strtotime($time_now))){
			if($status == 'mono' || $status == 'share' || $status == 'empty'){
				$query = "update room_info set status="."'".$status."'"." where room_num=".$room_num;
				mysql_query($query, $connect);
			}
		}
	}
}
?>