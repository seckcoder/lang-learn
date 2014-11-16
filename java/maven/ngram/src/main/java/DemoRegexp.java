/**
 * Created by seckcoder on 14-11-15.
 */

import java.util.regex.*;

public class DemoRegexp {
  public static void main(String[] args) {
    String str = new String("ab,*acdef--ade");
    String new_s = str.replaceAll("\\W+", " ");
    System.out.println(new_s);
  }
}
