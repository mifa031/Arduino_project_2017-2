<?
$day = array("sun","mon","tue","wed","thu","fri","sat");
$room_num = $_GET['room_num'];
if(isset($_GET['set'])){
	if($_GET['set'] == 0){
		echo date("Y").'.'.date("n").'.'.date("j").'.'.date("G").'.'.date("i").'.'.date("s");
	}
	else if($_GET['set'] == 1){
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
						echo (strtotime($time_end) - strtotime($time_now))/60;
					}
				}
			}
		}
	}
	else if($_GET['set'] == 2){
		$room_num = $_GET["room_num"];
		$connect=mysqli_connect("localhost","root","autoset","ce2017");
                mysqli_select_db($connect,"ce2017");
		$time_now = date("H:i:s");
		$day_now = $day[date('w')];
		$query = "select * from lec_time where day ="."'".$day_now."'"." order by start asc";
		$sql_result=mysqli_query($connect,$query);
		while($re=mysqli_fetch_array($sql_result)){
			$time_start = $re[3];
			if((strtotime($time_start) > strtotime($time_now))){
				echo (strtotime($time_start) - strtotime($time_now))/60;
			}
		}
	}
}
?>