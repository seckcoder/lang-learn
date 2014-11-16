/**
 * Created by seckcoder on 14-11-15.
 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.IOException;


public class DemoRegexp {
  private static void demoRegexp() {
    String str = new String("ab,*acdef--ade");
    String new_s = str.replaceAll("\\W+", " ");
    System.out.println(new_s);
  }
  private static void demoUTF8(String fpath) throws IOException {
    BufferedReader reader = new BufferedReader(
            new InputStreamReader(
                    new FileInputStream(fpath), "UTF8")
    );
    String line;
    while ((line = reader.readLine()) != null) {
      System.out.println(line);
    }
    reader.close();
  }
  public static void main(String[] args) throws IOException {
    demoUTF8(args[0]);
  }
}
