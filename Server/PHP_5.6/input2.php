<?
$room_name = $_POST['room_name1'];
$room_name2 = $_POST['room_name2'];
$lec_name = $_POST['lec_name'];
$day = $_POST['day1'];
$start = $_POST['start1'];
$end = $_POST['end1'];
$day2 = $_POST['day2'];
$start2 = $_POST['start2'];
$end2 = $_POST['end2'];
$day_arr = array("sun"=>0,"mon"=>1,"tue"=>2,"wed"=>3,"thu"=>4,"fri"=>5,"sat"=>6);

$connect=mysqli_connect("localhost","root","autoset","ce2017");
mysqli_select_db($connect,"ce2017");

$query1="insert into room_info(status,room_name) values("."'empty',"."'".$room_name."'".")";
mysqli_query($connect,$query1);
$query2="select room_num from room_info where room_name="."'".$room_name."'"." "."order by room_num desc";
$result = mysqli_query($connect,$query2);
$row = mysqli_fetch_row($result);
$room_num = $row[0];
//
if($room_name2 != null and $room_name2 != $room_name){
$query3="insert into room_info(status,room_name) values("."'empty',"."'".$room_name2."'".")";
mysqli_query($connect,$query3);
$query4="select room_num from room_info where room_name="."'".$room_name2."'"." "."order by room_num desc";
$result = mysqli_query($connect,$query4);
$row = mysqli_fetch_row($result);
$room_num2 = $row[0];
}else{
$room_num2 = $room_num;
}

$query5="insert into lec(lec_name) values("."'".$lec_name."'".")";
mysqli_query($connect,$query5);
$query6="select lec_num from lec where lec_name="."'".$lec_name."'"." "."order by lec_num desc";
$result = mysqli_query($connect,$query6);
$row = mysqli_fetch_row($result);
$lec_num = $row[0];

$query7 = "insert into lec_info values(".$room_num.",".$lec_num.","."'".$lec_name."'".")";
mysqli_query($connect,$query7);
if($room_name2 != null and $room_name2 != $room_name){
$query8 = "insert into lec_info values(".$room_num2.",".$lec_num.","."'".$lec_name."'".")";
mysqli_query($connect,$query8);
}

$query9="insert into lec_time values(".$room_num.",".$lec_num.","."'".$day."'".","."'".$start."'".","."'".$end."'".",".$day_arr[$day].")";
mysqli_query($connect,$query9);
if($room_name2 != null){
$query10="insert into lec_time values(".$room_num2.",".$lec_num.","."'".$day2."'".","."'".$start2."'".","."'".$end2."'".",".$day_arr[$day2].")";
mysqli_query($connect,$query10);
}

?>