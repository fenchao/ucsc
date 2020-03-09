/**
 * File Name: HauffmanTest.java 
 * Test Hauffman encode and decode algorithms
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

public class HauffmanTest{
	//CHANGE ONLY THIS LINE
	//Directory where you want to output dotfiles
	private static final String BASE = "./output/";
	//NOTHING CAN BE CHANGED BELOW
  private static final IntUtil u = new IntUtil();
  
  public static void test1(String s, boolean show, String dotfilename) {
    Hauffman h = new Hauffman(s,show,dotfilename);
    String d = h.encode();
    String f = h.decode();
    u.myassert(s.equals(f)) ;
    double sl = s.length() * 7 ;
    double dl = d.length();
    System.out.println("Original string cost = " + sl) ;
    System.out.println("Decoded  string cost = " + dl) ;
    double r = ((dl - sl)/sl) * 100 ;
    System.out.println("% reduction = " + (-r)) ;
  }
  
  public static void testbed() {
    boolean show = true ;
    test1("a",show,BASE + "1.dot");
    test1("aba",show,BASE+"2.dot");
    test1("aaabbggggghhhhaaaggggaaaaa_+@#",show,BASE +"3.dot");
    test1("A quick brown fox jumps over the lazy dog",show,BASE +"4.dot");
    test1("Pack my box with five dozen liquor jugs",show, BASE + "5.dot");
    test1("Long years ago we made a tryst with destiny, and now the time comes when we shall redeem our pledge, not wholly or in full measure, but very substantially.At the stroke of the midnight hour, when the world sleeps, India will awake to life and freedom. A moment comes, which comes but rarely in history, when we step out from the old to the new, when an age ends, and when the soul of a nation, long suppressed, finds utterance.",show,BASE +"6.dot");
    test1("Baa, baa, black sheep, have you any wool?",show,BASE + "7.dot") ;

    if (show) {
      System.out.println("===============  Done with Test1 ==================") ;
    } 
  }

  public static void main(String[] args) {
  	String version = System.getProperty("java.version");
		System.out.println("Java version used for this program is " + version);
    System.out.println("HauffmanTest.java");
    testbed() ;
    System.out.println(" All Hauffman Test passed. You are great. You should get an award");
  }
}
