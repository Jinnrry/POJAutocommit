import org.apache.commons.codec.binary.Base64;
import org.apache.http.Consts;
import org.apache.http.NameValuePair;
import org.apache.http.client.config.CookieSpecs;
import org.apache.http.client.config.RequestConfig;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.message.BasicNameValuePair;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by jiangwei on 2017/5/2.
 */
public class POJ {

    public String souce(int qid ) throws IOException {
        BufferedReader br=new BufferedReader(new InputStreamReader(new FileInputStream("poj/"+qid+".c"),"UTF-8"));
        String line = null;
        String souce="";
        while ((line = br.readLine()) != null) {
            souce=souce+line+"\r\n";
        }
        br.close();


        return new String(Base64.encodeBase64(souce.getBytes("UTF-8")));
    }




    public void submit(int qid) throws IOException {
        RequestConfig requestConfig = RequestConfig.custom().setCookieSpec(CookieSpecs.STANDARD_STRICT).build();
        CloseableHttpClient httpClient = HttpClients.custom().setDefaultRequestConfig(requestConfig).build();
        List<NameValuePair> valuePairs = new LinkedList<NameValuePair>();
        valuePairs.add(new BasicNameValuePair("user_id1","*******"));    //user id
        valuePairs.add(new BasicNameValuePair("password1", "*****"));          //password
        valuePairs.add(new BasicNameValuePair("b1", "login"));
        valuePairs.add(new BasicNameValuePair("url", "/status"));
        //完成登陆请求的构造
        UrlEncodedFormEntity entity = new UrlEncodedFormEntity(valuePairs, Consts.UTF_8);
        HttpPost post = new HttpPost("http://poj.org/login");
        post.setEntity(entity);
        CloseableHttpResponse imageResponse=httpClient.execute(post);//登录


        HttpGet get =new HttpGet("http://poj.org/");
        CloseableHttpResponse ht=httpClient.execute(get);//登录
//        String htmlinfo = EntityUtils.toString(ht.getEntity());
//        System.out.println(htmlinfo);


        List<NameValuePair> submitinfo = new LinkedList<NameValuePair>();
        submitinfo.add(new BasicNameValuePair("problem_id",""+qid));
        submitinfo.add(new BasicNameValuePair("language", "1"));
        submitinfo.add(new BasicNameValuePair("source", souce(qid)));  //源码
        submitinfo.add(new BasicNameValuePair("submit", "Submit"));
        submitinfo.add(new BasicNameValuePair("encoded", "1"));

        UrlEncodedFormEntity subinfo = new UrlEncodedFormEntity(submitinfo, Consts.UTF_8);



        HttpPost subpost = new HttpPost("http://poj.org/submit");
        subpost.setEntity(subinfo);
        CloseableHttpResponse subre=httpClient.execute(subpost);//登录


    }


    public static void main(String[] args) throws IOException {


        POJ p =new POJ();




        new Thread(){
            @Override
            public void run() {
                int i=1121;
                while (true) {
                    i++;
                    try {
                        p.submit(i);
                        String strs="submit success to No."+i+"";
                        String str = new String(strs.getBytes(), "gbk");
                        System.out.println(strs);

                    } catch (IOException e) {
                        System.out.println(e);
                        continue;
                    }

                    if(i>3985) break;


                    try {
                        sleep(5000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

            }
        }.start();



    }



}
