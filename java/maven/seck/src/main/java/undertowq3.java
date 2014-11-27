import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.Executors;

import org.hbase.async.GetRequest;
import org.hbase.async.HBaseClient;
import org.hbase.async.KeyValue;

import com.stumbleupon.async.Callback;
import com.stumbleupon.async.Deferred;

import io.undertow.Undertow;
import io.undertow.server.HttpHandler;
import io.undertow.server.HttpServerExchange;
import io.undertow.util.Headers;

public class undertowq3 {

	
	static HBaseClient hbase = new HBaseClient("localhost", "/hbase");
	
    public static void main(final String[] args) {
    	
    	
    	
        Undertow server = Undertow.builder().setIoThreads(6).setWorkerThreads(6)
                .addHttpListener(80, "0.0.0.0")
                .setHandler(new HttpHandler() {
                    @Override
                    public void handleRequest(final HttpServerExchange exchange) throws Exception {
                    	
                    	String uid = exchange.getQueryString().split("=")[1];
                        exchange.dispatch();

                		GetRequest get = new GetRequest("table3" ,uid); 
                		Deferred<ArrayList<KeyValue>> result = hbase.get(get);
                		String output = "";
                		try {
                			output =  result.addCallback(new Callback<String,ArrayList<KeyValue>>() {
                			public String call(ArrayList<KeyValue> res)  {
                				String toReturn = new String(res.get(0).value());
                				toReturn = "Orpheaus,6270-7148-7208,9392-2385-3384,8745-6736-8809\n"+toReturn+";";
                                exchange.getResponseSender().send(toReturn);
                                exchange.dispatch();
								return toReturn;
                			}
                		}).joinUninterruptibly();
                		} 
                		catch (Exception e) { 
                			System.out.println("Exception caught");
                			}
                    }
                }).build();
        server.start();
    }
}
