import java.util.Arrays;

/**
 * File Name: Stock1Base.java 
 * Java11
 * To Compile: IntUtil.java RandomInt.java Stock1Base.java
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * YOU CANNOT CHANGE ANYTHING IN THIS FILE. READ ONLY
 */

abstract class Stock1Base{
	private class results {
		//ONLY For me - the tester
		private int buyDay ;
		private int sellDay ;
		private int numDivide ;
		private int numConquer;
		results(int b, int s, int d, int c) {
			buyDay = b ;
			sellDay = s ;
			numDivide = d ;
			numConquer = c;
		}
	}
	protected IntUtil u = new IntUtil(); 
	private int[] a; //Data given. You cannot change it
	protected int buyDay = 0 ; //Find buyDay
	protected int sellDay = 0 ; //Find endDay ;
	protected int numDivide = 0 ; //Number of time divided
	protected int numConquer = 0 ; //work done during conquer
	
	//I don't know how to write it
  //Override by the concrete class
  abstract void NSquareTimeConstantSpace() ;
  abstract void NlognTimeLognSpace() ;
  abstract void NTimeLognSpace() ;
  abstract void NTimeConstantSpace();
  
  //You cannot access a
  protected int size() {
  	return a.length ;
  }
  
  //Get the price of the stock on day p
  //All array access must go through this routine this routine
  protected int price(int p) {
  	int l = a.length ;
  	u.myassert(p >= 0 && p < l);
  	return a[p] ;
  }
  
  //All profit computation must go through this routine
  protected int profit(int s, int b) {
  	int l = a.length ;
  	u.myassert(b >= 0 && b < l);
  	u.myassert(s >= 0 && s < l && b <= s);
  	int p = a[s] - a[b] ;
  	return p ;
  }
  
  protected void testBed() {
  	basic() ;
  	random() ;
	}	
  
  /*
	 * Use this routine to print
	 */
	private void P(int method) {
		String title[] = {"O(n^2)O(1)","O(nlogn)O(logn)","O(n)O(logn)", "O(n)O(1)"} ;
		int dq = numDivide + numConquer;
		if (a.length > 2 && dq == 0) {
			System.out.println("How you can solve this problem in 0 steps. Update numDivide and numConquer") ;
			u.myassert(false);
		}
		int bp = a[buyDay] ;
		int sp = a[sellDay] ;
		int g = profit(sellDay,buyDay);
		u.myassert((sp - bp) == g);
		System.out.println(title[method] + ": Sold on day " + sellDay + " for " + sp + ". Bought on day " + buyDay + " for " + bp + ". Profit = " + sp + "-" + bp + " = " + g) ; 
		int n = a.length ;
		double nlogn = n * (Math.log(n)/Math.log(2)) ;
		int inlogn = (int)nlogn ;
		int n2 = n * n ;
		if (method == 0) {
			System.out.print(title[0] + " = " + n2 + " ") ;
		}
		if (method == 1) {
			System.out.print(title[1] + " = " + inlogn + " ") ;
		}
		if (method == 2) {
			System.out.print(title[2] + " = " + n + " ") ;
		}
		if (method == 3) {
			System.out.print(title[3] + " = " + n + " ") ;
		}
		System.out.println("numDivide = " + numDivide + " numConquer = " + numConquer) ;
	}
	
  
  private void init(final int [] q) {
  	a = q ;
  	buyDay = 0 ; //Find buyDay
  	sellDay = 0 ; //Find endDay ;
  	numDivide = 0 ;
  	numConquer = 0 ;
  }
 
  private void assertAnswers(results d1, results d2) {
  	int p1 = profit(d1.sellDay,d1.buyDay) ;
		int p2 = profit(d2.sellDay,d2.buyDay) ;
		if (p1 != p2) {
			System.out.println("Correct answer = " + p1) ;
			System.out.println("Your    answer = " + p2) ;
			u.myassert(false); ;
		}
  }
  
  private void one(final int [] q) {
  	init(q) ;
  	System.out.println("-----------------------------------") ;
  	if (a.length < 16) {
  		u.pLn(a.length);
  		u.pLn(a) ;
  	}else {
  		System.out.println("--- Array length is " + a.length) ;
  	}
  	
  	NSquareTimeConstantSpace() ;
  	P(0) ;
  	results d0 = new results(buyDay,sellDay,numDivide,numConquer) ;
  	
  	init(q) ;
  	NlognTimeLognSpace() ;
  	P(1) ;
  	results d1 = new results(buyDay,sellDay,numDivide,numConquer) ;
  	assertAnswers(d0,d1) ;
  	
  	init(q) ;
  	NTimeLognSpace() ;
  	P(2) ;
  	results d2 = new results(buyDay,sellDay,numDivide,numConquer) ;
  	assertAnswers(d0,d2) ;
  	
  	init(q) ;
  	NTimeConstantSpace();
  	P(3) ;
  	results d3 = new results(buyDay,sellDay,numDivide,numConquer) ;
  	assertAnswers(d0,d3) ;
  }

  private void basic() {
  	{
  		final int [] a =  {5, 10, 4, 6, 12};
  		one(a) ;
  	}
  	{
  		final int [] a = {5};
  		one(a) ;
  	}
  	{
  		final int [] a = {6,5};
  		one(a) ;
  	}
  	{
  		final int [] a = {1,2,3};
  		one(a) ;
  	}
  	{
  		final int [] a = {3,2,1};
  		one(a) ;
  	}
  	{
  		final int [] a = { 5,10,4,6,12 };
  		one(a) ;
  	}
  	{
  		final int [] a = { 1,1,1,1,1,1};
  		one(a) ;
  	}
  	{
      final int a[] = { 1,2,3,4,5,6,7};
      one(a);
    }
  	{
      final int a[] = { 1,2,3,4,5,6};
      one(a);
    }
  	{
      final int a[] = { 7,6,5,4,3,2,1};
      one(a);
    }
  	{
      final int a[] = {6,5,4,3,2,1};
      one(a);
    }
  	{
  		//ascending
  		int N = 1000 ;
  		int [] a = u.generateNumberInIncreasingOrder(N,1);
  		one(a) ;
  	}
  	{
  		//descending
  		int N = 1000 ;
  		int [] a = u.generateNumberInDescendingOrder(N,1);
  		one(a) ;
  	}
  }
  
  private void random() {
  	final int max = 2000;
    final int n = 1000;
    for (int i = 0; i < max; ++i) {
      int [] a = u.generateRandomNumber(n, true, 50,100);
      one(a) ;
    }
  }
	
	public static void main(String[] args) {
		System.out.println("Stock1Base.java STARTS");
		String version = System.getProperty("java.version");
		System.out.println("Java version used for this program is " + version);
		System.out.println("You cannot instantiate Stock1Base class: Stock1Base p = new Stock1Base() ; ");
		//Stock1Base p = new Stock1Base() ;
		System.out.println("Stock1Base.java ENDS");
	}
}