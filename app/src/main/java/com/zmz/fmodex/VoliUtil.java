package com.zmz.fmodex;

/**
 * Created by Zhang Mingzhe on 2018/3/9.
 * mail:1084904209@qq.com
 * Describe
 */

public class VoliUtil {
    static {
        System.loadLibrary("fmod");
        System.loadLibrary("fmodL");
        System.loadLibrary("zmz_lib");
    }

    public native static void fix(String path, int mode);
    public native static void stop();
}
