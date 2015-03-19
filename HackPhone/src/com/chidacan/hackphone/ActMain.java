package com.chidacan.hackphone;



import java.io.IOException;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
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
//import com.android.internal.telephony.*;

import android.telephony.TelephonyManager; 

public class ActMain extends Activity {
	Intent intent;
	private static final String TAG = "ServMain" ;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.act_main);
    	Intent it = new Intent(ServMain.ACTION);
    	it.setClass(this, com.chidacan.hackphone.ServMain.class);
    	it.putExtra("port", 1996);
    	it.putExtra("ip", "192.168.18.101");
    	startService(it);  

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
    }

    public void bn01_click(View v){
    	Intent it = new Intent(ServMain.ACTION);
    	it.setClass(this, com.chidacan.hackphone.ServMain.class);    	
    	bindService(it, conn, BIND_AUTO_CREATE); 		
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
}
