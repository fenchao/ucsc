/**
 * File Name: LookAndSay.java 
 * LookAndSay concrete class
 * 
 * 
 * To Compile: IntUtil.java RandomInt.java LookAndSay.java LookAndSayBase.java
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

class LookAndSay extends LookAndSayBase{
	LookAndSay() {
		//NOTHING CAN BE CHANGED HERE
		testBench();
	}
	
	@Override
	protected String lookAndSay(String s) {
		//NOTHING CAN BE CHANGED HERE
		return alg(s) ;
	}

	@Override
	protected String lookAndSay(int n) {
		//NOTHING CAN BE CHANGED HERE
		return alg(n) ;
	}
	
	private String alg(String s) {
	  //WRITE CODE
		//You can have any number of private functions and variables
		StringBuffer sb = new StringBuffer();
        int count = 0;
        for(int i = 0; i < s.length(); ++i) {
            ++count;
            if (i+1 == s.length() || s.charAt(i) != s.charAt(i+1)) {
                sb.append(count);
                sb.append(s.charAt(i));
                count = 0;
            }
        }
        return sb.toString();
	}

	private String alg(int n) {
		//WRITE CODE
		//You can have any number of private functions and variables
		String ret = "1";
		for(int i = 1; i < n; ++i) {
			ret = alg(ret);
		}
		return ret;
	}

	public static void main(String[] args) {
		//NOTHING CAN BE CHANGED HERE
		System.out.println("LookAndSay problem STARTS");
		LookAndSay m = new LookAndSay() ;
		System.out.println("All LookAndSay tests passed. You are genius");
		System.out.println("LookAndSay problem ENDS");
	}
}