package com.chidacan.hackphone;



import java.io.DataOutputStream;
import java.io.IOException;
import java.lang.reflect.Method;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.net.Uri;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;

import android.util.Log;
//import android.os.ServiceManager;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import com.android.internal.telephony.*;

import android.telephony.TelephonyManager; 

public class ActMain extends Activity {
	Intent intent;
	private static final String mip = "192.168.18.100";
	private static final String mport = "1996";
	private static final String TAG = "ServMain" ;
	private MsgReceiver msgReceiver;  
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.act_main);
		upgradeRootPermission(getPackageCodePath()); 
		Log.v(TAG, "ServiceDemo root ok");
		//动态注册广播接收器
		msgReceiver = new MsgReceiver();
		IntentFilter intentFilter = new IntentFilter();
		intentFilter.addAction("android.intent.action.MAIN");
		registerReceiver(msgReceiver, intentFilter);		
		
    	Intent it = new Intent(ServMain.ACTION);
    	it.setClass(this, com.chidacan.hackphone.ServMain.class);
    	it.putExtra("port", 1996);
    	it.putExtra("ip", mip);
    	startService(it); 
    	Log.v(TAG,"startService");
    	EditText ip = (EditText) findViewById(R.id.ip);
    	EditText port = (EditText) findViewById(R.id.port);
    	ip.setText(mip);
    	port.setText(mport);
    }
    
    public void bnset_onClick(View v){
    	EditText ip = (EditText) findViewById(R.id.ip);
    	EditText port = (EditText) findViewById(R.id.port);
    	Intent it = new Intent(ServMain.ACTION);
    	it.setClass(this, com.chidacan.hackphone.ServMain.class);
    	it.putExtra("port", Integer.valueOf(port.getText().toString()));
    	it.putExtra("ip", ip.getText().toString());
    	startService(it);      	
    }
    
    
    public void bn10086_click(View v){
    	/*
    	Phone phone = PhoneFactory.getDefaultPhone();
    	try {
			phone.dial("10086");
		} catch (CallStateException e) {
			Log.v(TAG,e.getMessage());
		}
    	*/
    	//dail("10086");
    	Log.v(TAG,"10086 ok!");
    	
    }

    public void bn01_click(View v){
    	/*
    	try{
    	Phone phone = PhoneFactory.getDefaultPhone();
    	Log.v(TAG,phone.getPhoneName());
    	phone.sendDtmf('1');
    	}catch(Exception e){
    		Log.v(TAG,e.getMessage());
    	}
    	Log.v(TAG,"dtmf done");
    	*/
    	//sendDTMF((char)1);
    }
    
    public void bnHungup_onClick(View v){
    	//endCall();
    }

	@Override
	protected void onDestroy() {
		//停止服务
    	Intent it = new Intent(ServMain.ACTION);
    	it.setClass(this, com.chidacan.hackphone.ServMain.class);
		stopService(it);
		//注销广播
		unregisterReceiver(msgReceiver);
		super.onDestroy();
	}    
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.act_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
    
    ServiceConnection conn = new ServiceConnection() {
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.v(TAG, "onServiceConnected");
		}
		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.v(TAG, "onServiceDisconnected");
		}
	};	
	
	
	/**
	 * 广播接收器
	 * @author len
	 *
	 */
	public class MsgReceiver extends BroadcastReceiver{

		@Override
		public void onReceive(Context context, Intent intent) {
			String progress = intent.getStringExtra("progress");
	    	try{
	        	//Phone phone = PhoneFactory.getDefaultPhone();
	        	//Log.v(TAG,phone.getPhoneName());
	        	for(char c : progress.toCharArray()){
	        		sendDTMF(c);
	        	}
	        	//phone.sendBurstDtmf(progress, 0, 0, null);
	    		//sendDTMF((char)progress);
	        	}catch(Exception e){
	        		Log.v(TAG,e.getMessage());
	        	}
	        	//Log.v(TAG,"dtmf done");			
		}
		
	}	
	
	/**
	 * 说明:发送dtmf事件
	 * Author:陈伟斌
	 * 2012-12-13
	 * @param keycode
	 */
	public void sendDTMF(char keycode) {
		try {
			
			Class cls_phoneFactory = Class
					.forName("com.android.internal.telephony.PhoneFactory");
			Method method_getDefaultPhone = cls_phoneFactory.getDeclaredMethod(
					"getDefaultPhone", null);
			method_getDefaultPhone.setAccessible(true);
			Object obj_phone = method_getDefaultPhone.invoke(null);
			Method method_sendDTMF = obj_phone.getClass().getDeclaredMethod(
					"sendDtmf", char.class);
			method_sendDTMF.invoke(obj_phone, keycode);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}	
	
	public void dail(String tel) {
		try {
			
			Class cls_phoneFactory = Class
					.forName("com.android.internal.telephony.PhoneFactory");
			Method method_getDefaultPhone = cls_phoneFactory.getDeclaredMethod(
					"getDefaultPhone", null);
			method_getDefaultPhone.setAccessible(true);
			Object obj_phone = method_getDefaultPhone.invoke(null);
			Method method_sendDTMF = obj_phone.getClass().getDeclaredMethod(
					"dial", String.class);
			method_sendDTMF.invoke(obj_phone, tel);
			
		} catch (Exception e) {
			e.printStackTrace();


		}
	}		
	
	private void endCall() {
		TelephonyManager telMag = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
		Class<TelephonyManager> c = TelephonyManager.class;
		Method mthEndCall = null;
		try {
			mthEndCall = c.getDeclaredMethod("getITelephony", (Class[]) null);
			mthEndCall.setAccessible(true);
			ITelephony iTel = (ITelephony) mthEndCall.invoke(telMag,
					(Object[]) null);
			iTel.endCall();
			Log.v(TAG, iTel.toString());
		} catch (Exception e) {
			e.printStackTrace();
		}
		Log.v(TAG, "endCall test");
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
