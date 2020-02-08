package com.vell.vchat;

import android.app.Application;
import android.os.Environment;

import com.tencent.mars.xlog.Log;
import com.tencent.mars.xlog.Xlog;

public class BaseApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        // 初始化日志
        System.loadLibrary("c++_shared");
        System.loadLibrary("marsxlog");

        final String SDCARD = Environment.getExternalStorageDirectory().getAbsolutePath();
        final String logPath = SDCARD + "/vchat/log";

        // this is necessary, or may crash for SIGBUS
        final String cachePath = this.getFilesDir() + "/xlog";

        //init xlog
        if (BuildConfig.DEBUG) {
            Xlog.appenderOpen(Xlog.LEVEL_DEBUG, Xlog.AppednerModeAsync, cachePath, logPath, "vchat", 0, "");
            Xlog.setConsoleLogOpen(true);

        } else {
            Xlog.appenderOpen(Xlog.LEVEL_INFO, Xlog.AppednerModeAsync, cachePath, logPath, "vchat", 3, "");
            Xlog.setConsoleLogOpen(false);
        }

        Log.setLogImp(new Xlog());

    }

    @Override
    public void onTerminate() {
        super.onTerminate();
        Log.appenderClose();
    }
}
