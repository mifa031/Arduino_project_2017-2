package byeongsu.soongsil.ac.kr.myapplication.adapter;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.List;

import byeongsu.soongsil.ac.kr.myapplication.R;
import byeongsu.soongsil.ac.kr.myapplication.model.Room;

/**
 * Created by byeon on 2017-11-20.
 */

public class RoomAdapter extends ArrayAdapter<Room> {

    Activity activity;
    int resource;

    public RoomAdapter(@NonNull Context context, int resource, @NonNull List<Room> objects) {
        super(context, resource, objects);

        this.activity = (Activity)context;
        this.resource = resource;
    }


    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {

        View itemView = convertView;

        if( itemView == null){
            itemView = this.activity.getLayoutInflater().inflate(this.resource, null);
        }

        Room item = getItem(position); //포지션받아오기

        if(item != null){  //아이템이 null이 아닐 경우 뷰에 데이터 설정
            TextView room_name = (TextView)itemView.findViewById(R.id.room_name);
            TextView room_status = (TextView)itemView.findViewById(R.id.room_status);

            room_name.setText(item.getRoom_name());
            room_name.setTextColor(Color.parseColor(activity.getString(R.string.black)));

            // Inform 2 Text
            if( item.getStatus().equals("lec")) {
                room_status.setText("강의중");
                room_status.setTextColor(Color.parseColor( activity.getString(R.string.red)));
            }
            else if( item.getStatus().equals("share")) {
                room_status.setText("자유이용");
            }
            else if( item.getStatus().equals("mono")) {
                room_status.setText("독점이용");
            }
            else // == empty
            {
                room_status.setText("사용가능");
                room_status.setTextColor(Color.parseColor( activity.getString(R.string.gray)));
            }
        }

        return itemView;
    }
}
