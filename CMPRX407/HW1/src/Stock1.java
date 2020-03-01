/**
 * File Name: Stock1.java 
 * Stock1 concrete class
 * 
 * 
 * To Compile: IntUtil.java RandomInt.java Stock1.java Stock1Base.java
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

class Stock1 extends Stock1Base{
	//You can have any number of private data members here
	//You can have any number of private functions here
	Stock1() {
		//NOTHING CAN BE CHANGED HERE
		testBed() ;
	}
	
	@Override
	void NSquareTimeConstantSpace() {
		//NOTHING CAN BE CHANGED HERE
    nsquareTimeConstantSpace() ;
	}
	
	@Override
  void NlognTimeLognSpace() {
		//NOTHING CAN BE CHANGED HERE
    nlognTimelognSpace() ;
	}
	
	@Override
  void NTimeLognSpace() {
		//NOTHING CAN BE CHANGED HERE
    nTimelognSpace() ;
	}
	
	@Override
	void NTimeConstantSpace() {
		nTimeConstantSpace();
	}
	
	/*
	 * Time: O(n^2)
	 * Space: THETA(1)
	 * All your routine should match this answer
	 * Nothing can be changed in this routine
	 */
	private void nsquareTimeConstantSpace() {
		int gp = 0 ;
		int l = size() ;
		for (int buy = 0; buy < l-1; ++buy) {
			for (int sell = buy + 1; sell < l; ++sell) {
				++numConquer;
				int p = profit(sell,buy);
				if (p >= gp) { //So that I can make profit by keeping stock for less time
					gp = p ;
					buyDay = buy ;
					sellDay = sell ;
				}
			}
		}
	}
	
	/*
	 * Time: O(nlogn)
	 * Space: O(logn)
	 */
	private void nlognTimelognSpace() {
		//WRITE YOUR CODE
		int l = size();
		nlognTimelognSpace(0, l-1);
	}
	
	private void nlognTimelognSpace(int start, int end) {
		if (start == end) {
			return;
		}
		++numDivide;
		int mid = (end-start)/2+start;
		nlognTimelognSpace(start, mid);
		nlognTimelognSpace(mid+1, end);
		int buy = start, sell = end;
		for(int b = start, s = end; b <= s; ++b, --s) {
			++numConquer;
			if (price(b) < price(buy)) {
				buy = b;
			}
			if (price(s) > price(sell)) {
				sell = s;
			}
		}
		if (profit(sell, buy) > profit(sellDay, buyDay)) {
			sellDay = sell;
			buyDay = buy;
		}
	}
	
	private void nTimelognSpace() {
		//NOT required this time
		int l = size();
		int[] cross = nTimelognSpace(0, l-1);
	}
	
	private int[] nTimelognSpace(int start, int end) {
		int[] cross = {start, start}; // 0: minDay, 1: maxDay
		if (start == end) {
			return cross;
		}
		++numDivide;
		++numConquer;
		int mid = (end-start)/2+start;
		int[] left = nTimelognSpace(start, mid);
		int[] right = nTimelognSpace(mid+1, end);
		if (profit(right[1], left[0]) > profit(sellDay, buyDay)) {
			sellDay = right[1];
			buyDay = left[0];
		}
		cross[0] = price(left[0]) < price(right[0]) ? left[0] : right[0];
		cross[1] = price(left[1]) > price(right[1]) ? left[1] : right[1];
		return cross;
	}
	
	private void nTimeConstantSpace() {
		int buy = 0;
		int l = size();
		for(int day = 1; day < l; ++day) {
			++numConquer;
			if (price(day) < price(buy)) {
				buy = day;
			} else if (profit(day, buy) > profit(sellDay, buyDay)) {
				sellDay = day;
				buyDay = buy;
			}
		}
	}
	
	public static void main(String[] args) {
		//NOTHING CAN BE CHANGED HERE
		System.out.println("Stock1 problem STARTS");
		Stock1 m = new Stock1() ;
		System.out.println("All Stock1 tests passed. Now you can pass interviews");
		System.out.println("Stock1 problem ENDS");
	}
}