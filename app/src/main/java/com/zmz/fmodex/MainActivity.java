package com.zmz.fmodex;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import org.fmod.FMOD;

/**
 * @author Zhang Mingzhe
 */
public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("zmz_lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        FMOD.init(this);
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
//                String path = "android.resource://" + getPackageName() + "/" + R.raw.tonghuazhen;
//                String path = "/storage/emulated/0/zmz/tonghuazhen.mp3";
                String path = "file:///android_asset/tonghuazhen.mp3";
                Log.i("ZMZ", "onClick: " + path);
                VoliUtil.fix(path, 1);
            }
        });

        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                VoliUtil.stop();
            }
        });
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
