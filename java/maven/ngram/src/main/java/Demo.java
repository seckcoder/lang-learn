/**
 * Created by seckcoder on 14-11-22.
 */
public class Demo {

  static void test1() {
    String[] subs = new String("abc def").split(" ");
    StringBuilder[] builders = new StringBuilder[subs.length];
    for (int i = 0; i < subs.length; i++) {
      builders[i] = new StringBuilder(subs[i]);
    }
    builders[0].append(builders[1].toString());
    System.out.println(builders[0].toString());
    builders[1].append("ghi");
    System.out.println(builders[0].toString());
  }
  public static void main(String[] args) {
    String str = "abc def ghi";
    String[] subs = str.split(" ");
    StringBuilder[] builders = new StringBuilder[subs.length];
    for (int i = 0; i < subs.length; i++) {
      builders[i] = new StringBuilder(subs[i]);
    }
    int arr_len = subs.length;
    int step = 1;
    while (arr_len > 0) {
      for (int i = 0; i < arr_len; i++) {
        System.out.println(String.format("%s\t%d", builders[i].toString(), 1));
      }
      for (int i = 0; i < arr_len - 1; i++) {
        builders[i].append(" ");
        builders[i].append(subs[i + step].toString());
      }
      step += 1;
      arr_len -= 1;
    }
  }
}
