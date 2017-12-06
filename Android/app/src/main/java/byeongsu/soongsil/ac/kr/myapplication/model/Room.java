package byeongsu.soongsil.ac.kr.myapplication.model;

/**
 * Created by byeon on 2017-11-20.
 */

public class Room {
    private String room_num;
    private String room_name;
    private String status;
    public Room(String room_num, String room_name, String status) {
        this.room_num = room_num;
        this.room_name = room_name;
        this.status = status;

    }

    public String getRoom_num() {
        return room_num;
    }

    public void setRoom_num(String room_num) {
        this.room_num = room_num;
    }

    public String getRoom_name() {
        return room_name;
    }

    public void setRoom_name(String room_name) {
        this.room_name = room_name;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }


}
