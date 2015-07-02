
import java.io.IOException;
class A {
  public A() throws IOException {
    System.out.print("AirPlane");
    throw new IOException();
  }
};

class B extends A {
  public B() throws IOException {
    try {
      super();
    } catch (IOException e) {
      System.out.print("IOException is thrown in AirJet");
    }
  }
}


public class Tester {
  public static void main(String args[]) {
    try {
      new B();
    } catch (IOException e) {
      System.out.print("IOException is thrown in Tester");
    }
  }
}
