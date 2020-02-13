import java.util.Random;

/**
 * File Name: LookAndSayBase.java 
 * Java11
 * To Compile: IntUtil.java RandomInt.java LookAndSayBase.java
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * YOU CANNOT CHANGE ANYTHING IN THIS FILE. READ ONLY
 */

abstract class LookAndSayBase{
	protected IntUtil u = new IntUtil();
	
	//I don't know how to write it
  //Override by the concrete class
  abstract String lookAndSay(int n) ;
  abstract String lookAndSay(String s) ;
  
  protected void testBench() {
  	tests() ;
		testn() ;
	}	
  
  private void tests() {
  	{
  		String n = "123" ;
  		String e = "111213" ;
  		String s = lookAndSay(n) ;
  		u.myassert(s.equals(e));
  	}
  	{
  		String n = "9999999999" ;
  		String e = "109" ;
  		String s = lookAndSay(n) ;
  		u.myassert(s.equals(e));
  	}
  	{
  		String n = "9876543210" ;
  		String e = "19181716151413121110" ;
  		String s = lookAndSay(n) ;
  		u.myassert(s.equals(e));
  	}
  	
  }

  private void testn() {
  	{
  		int n = 1 ;
  		String e = "1" ;
  		String s = lookAndSay(n) ;
  		u.myassert(s.equals(e));
  	}
  	{
  		int n = 2 ;
  		String e = "11" ;
  		String s = lookAndSay(n) ;
  		u.myassert(s.equals(e));
  	}
  	{
  		int n = 3 ;
  		String e = "21" ;
  		String s = lookAndSay(n) ;
  		u.myassert(s.equals(e));
  	}
  	{
  		int n = 4 ;
  		String e = "1211" ;
  		String s = lookAndSay(n) ;
  		u.myassert(s.equals(e));
  	}
  	{
  		int n = 5 ;
  		String e = "111221" ;
  		String s = lookAndSay(n) ;
  		u.myassert(s.equals(e));
  	}
  	for (int n = 1; n < 32; ++n) {
  		String s = lookAndSay(n) ;
  		System.out.println("n = " + n + " Length = " + s.length()) ;
  		System.out.println("n = " + n + " " + s) ;
  		System.out.println() ;
  	}
  }
	
	public static void main(String[] args) {
		System.out.println("LookAndSayBase.java STARTS");
		String version = System.getProperty("java.version");
		System.out.println("Java version used for this program is " + version);
		System.out.println("You cannot instantiate LookAndSayBase class: LookAndSayBase p = new LookAndSayBase() ; ");
		//LookAndSayBase p = new LookAndSayBase() ;
		System.out.println("LookAndSayBase.java ENDS");
	}
}