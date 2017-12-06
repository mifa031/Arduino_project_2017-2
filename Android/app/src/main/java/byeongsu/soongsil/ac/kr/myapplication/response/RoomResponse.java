package byeongsu.soongsil.ac.kr.myapplication.response;

import android.app.Activity;
import android.app.ProgressDialog;
import android.widget.Toast;

import com.loopj.android.http.AsyncHttpResponseHandler;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import byeongsu.soongsil.ac.kr.myapplication.adapter.RoomAdapter;
import byeongsu.soongsil.ac.kr.myapplication.model.Room;

/**
 * Created by byeon on 2017-11-20.
 */

public class RoomResponse extends AsyncHttpResponseHandler {

        Activity activity;
        RoomAdapter adapter;
        ProgressDialog dialog;


    public RoomResponse(Activity activity, RoomAdapter adapter) {
        this.activity = activity;
        this.adapter = adapter;
    }

    @Override
    public void onStart() {

        dialog = new ProgressDialog(activity);
        dialog.setMessage("잠시만 기다리세요");
        dialog.setCancelable(false);
        dialog.show();
    }

    @Override
    public void onSuccess(String content) {

        try{
            // only parse room_status
            JSONArray jsonArray = new JSONArray(content);


            for(int i = 0 ; i < jsonArray.length() ; i++ ){
                JSONObject temp =  jsonArray.getJSONObject(i);

                String room_num = temp.getString("room_num");
                String room_name = temp.getString("room_name");
                String room_status = temp.getString("status");

                adapter.add(new Room(room_num, room_name, room_status));

            }

        }catch(JSONException e){
            //TODO auto-generated catch block
            e.printStackTrace();
        }
    }

    @Override
    public void onFailure(int statusCode, Throwable error, String content) {

        Toast.makeText(activity, "통신에 실패했습니다", Toast.LENGTH_SHORT);
    }

    @Override
    public void onFinish() {

        dialog.dismiss();
        dialog = null;
    }
}
