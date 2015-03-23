package com.chidacan.hackphone;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;

import com.android.internal.telephony.Phone;
import com.android.internal.telephony.PhoneFactory;

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
        	boolean run = true; int readed;
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
		            			//readed = bff.readLine();
		            			readed = bff.read();
		            		}
		            		catch(Exception e){
		            			break;
		            		}
		            		Log.v(TAG,"read");
		            		if(readed == -1) break;
		            		// ·¢ËÍ°´¼üdtmf
		            		//try{
		                	//Phone phone = PhoneFactory.getDefaultPhone();
		                	//phone.sendDtmf((char) readed);
		            		//}catch(Exception e){
		            		//	e.printStackTrace();
		            		//}
		            		Intent intent = new Intent("android.intent.action.MAIN");
		            		intent.putExtra("progress", readed);
		            		sendBroadcast(intent); 
		            		
		            	}while(true);
            		}catch(Exception e){
            			sleep(1000);
            			//e.printStackTrace();
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
