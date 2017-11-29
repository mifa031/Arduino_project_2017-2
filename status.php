<?
$day = array("sun","mon","tue","wed","thu","fri","sat");
if(!isset($_GET["status"])){
	$room_num = $_GET["room_num"];
	$connect=mysqli_connect("localhost","root","autoset","ce2017");
        mysqli_select_db($connect,"ce2017");
	$query="select * from lec_time where room_num=".$room_num;
	$sql_result=mysqli_query($connect,$query);
	$time_now = date("H:i:s");
	$day_now = $day[date('w')];
	while($re=mysqli_fetch_array($sql_result)){
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
					mysqli_query($connect,$query);
				}
			}
		}
	}
}else{
	$room_num = $_GET["room_num"];
	$status = $_GET["status"];
	$connect=mysqli_connect("localhost","root","autoset","ce2017");
	mysqli_select_db($connect,"ce2017");
	//$day_now = $day[date('w')];
	$pre_query = "select * from lec_time where room_num=".$room_num." and day_num=".date('w');
	$sql_result=mysqli_query($connect,$pre_query);
	$re=mysqli_fetch_array($sql_result);
	if(strcmp($re[0],null) == 0){
		$not_this_day = 1;
	}else{
		$not_this_day = 0;
	}

	$query="select * from lec_time where room_num=".$room_num;
	$sql_result=mysqli_query($connect,$query);
	$time_now = date("H:i:s");
	while($re=mysqli_fetch_array($sql_result)){
		$day_db = $re[5];
		$time_start = $re[3];
		$time_end = $re[4];
		if(($not_this_day == 1) || (strtotime($time_start) > strtotime($time_now)) || (strtotime($time_end) < strtotime($time_now))){
				 if($status == 'mono' || $status == 'share' || $status == 'empty'){
					 $query = "update room_info set status="."'".$status."'"." where room_num=".$room_num;
					 mysqli_query($connect,$query);
			      }
        }
	}
}
?>