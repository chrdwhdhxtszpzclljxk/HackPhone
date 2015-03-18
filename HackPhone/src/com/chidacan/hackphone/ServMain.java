package com.chidacan.hackphone;

import java.io.BufferedReader;
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
		return super.onStartCommand(intent, flags, startId);
	}
	 
    class MyThread extends Thread {
        @Override
        public void run() {
        	boolean run = true; int readed;	String msg; StringBuilder sb = new StringBuilder(); 
            try {
            	do{
	            	Socket s = null;
            		try{
		            	s = new Socket("192.168.18.100",1996);
		            	OutputStream ou = s.getOutputStream(); 
		            	BufferedReader bff = new BufferedReader(new InputStreamReader( s.getInputStream()));
		            	do{
		            		if(!s.isConnected()) break;
		            		readed = bff.read();
		            		Log.v(TAG,"read");
		            		if(readed == -1) continue;
		            		sb.append("input keyevent ");
		            		sb.append(Integer.toString((char)readed));
		            		Log.v(TAG,sb.toString());
		            		
		            		Runtime.getRuntime().exec(sb.toString());
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
		threadSocket = new MyThread();
		threadSocket.start();
		
		super.onCreate();
	}
	
	@Override
    public void onDestroy() {
		Log.v(TAG, "ServiceDemo onDestroy");
		super.onDestroy();		
    }
}
