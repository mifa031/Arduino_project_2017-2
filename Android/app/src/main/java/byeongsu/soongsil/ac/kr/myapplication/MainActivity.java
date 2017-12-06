package byeongsu.soongsil.ac.kr.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ListView;

import com.loopj.android.http.AsyncHttpClient;

import java.io.LineNumberInputStream;
import java.util.ArrayList;
import java.util.List;

import byeongsu.soongsil.ac.kr.myapplication.adapter.RoomAdapter;
import byeongsu.soongsil.ac.kr.myapplication.model.Room;
import byeongsu.soongsil.ac.kr.myapplication.response.RoomResponse;

public class MainActivity extends AppCompatActivity {

    List<Room> list;
    RoomAdapter adapter;
    ListView listView;

    AsyncHttpClient client;
    RoomResponse response;
    String URL_JSON = "http://121.128.151.144/android_json.php?set=0"; // only room_status

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        list = new ArrayList<Room>();
        adapter = new RoomAdapter(this, R.layout.list_item, list);
        listView = (ListView)findViewById(R.id.listView);
        listView.setAdapter(adapter);

        client = new AsyncHttpClient();
        response = new RoomResponse(this, adapter);

    }

    @Override
    protected void onPostResume() {
        super.onPostResume();
        client.get(URL_JSON, response);
    }
}
