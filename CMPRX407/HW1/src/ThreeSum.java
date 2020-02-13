import java.util.Arrays;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

/**
 * File Name: ThreeSum.java 
 * ThreeSum  class
 * 
 * To Compile: IntUtil.java RandomInt.java Tuple.java ThreeSumBase.java ThreeSum.java 
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

class ThreeSum extends ThreeSumBase{
	ThreeSum() {
		//NOTHING CAN BE CHANGED HERE
		testBench();
	}

	@Override
	protected String inputFileBase() {
		//Where is the input file?
		//Change this to your location
		return "/Users/fdu/Dropbox/course/CMPRX407/HW1/3sumdata/";
	}

	@Override
	protected List<List<Integer>> threeSum(int[] nums, int n, int method) {
			//NOTHING CAN BE CHANGED HERE
			if (method == 1) {
				return N3TimeConstantSpace(nums,n) ;
			}
			if (method == 2) {
				return N2TimeNSpace(nums,n) ;
			}
			if (method == 3) {
				return N2TimeConstantSpace(nums,n) ;
			}
			return null ;
	}


	/*
	 * Time complexity O(N^3)
	 * Space complexity O(1)
	 */
	private List<List<Integer>> N3TimeConstantSpace(int[] nums, int n) {
		//WRITE CODE
		List<List<Integer>> ret = new ArrayList<>();
		Arrays.sort(nums);
		int previ = nums.length > 0 ? ~nums[0] : 0;
		for(int i = 0; i < nums.length-2; ++i) {
			if (previ != nums[i]) {
				previ = nums[i];
				int prevj = ~nums[i+1];
				for(int j = i+1; j < nums.length-1; ++j) {
					if (prevj != nums[j]) {
						prevj = nums[j];
						int prevk = ~nums[j+1];
						for(int k = j+1; k < nums.length; ++k) {
							if (prevk != nums[k]) {
								prevk = nums[k];
								long val = (long)nums[i] + (long)nums[j] + (long)nums[k];
								if (val > (long)n) {
									break;
								} else if (val == (long)n) {
									List<Integer> entry = new ArrayList<>();
									entry.add(nums[i]);
									entry.add(nums[j]);
									entry.add(nums[k]);
									ret.add(entry);
								}
							}
						}
					}
				}
			}
		}
		return ret;
	}


	/*
	 * Time complexity O(N^2)
	 * Space complexity O(N)
	 */
	private List<List<Integer>> N2TimeNSpace(int[] nums, int n) {
		//WRITE CODE
		List<List<Integer>> ret = new ArrayList<>();
		Arrays.sort(nums);
		int previ = nums.length > 0 ? ~nums[0] : 0;
		for(int i = 0; i < nums.length-2; ++i) {
			if (previ != nums[i]) {
				previ = nums[i];
				HashSet<Integer> hst = new HashSet<>();
				int prevk = Integer.MIN_VALUE;
				for(int k = i+1; k < nums.length; ++k) {
					if (prevk == nums[k]) {
						continue;
					}
					long j = (long)n - (long)nums[i] - (long)nums[k];
					if (j < (long)nums[i+1]) {
						break;
					}
					if (j <= nums[k] && hst.contains((int)j)) {
						List<Integer> entry = new ArrayList<>();
						entry.add(nums[i]);
						entry.add((int)j);
						entry.add(nums[k]);
						ret.add(entry);
						hst.add(nums[k]);
					}
					if (hst.contains(nums[k])) {
						prevk = nums[k];
					} else {
						hst.add(nums[k]);
					}
				}
			}
		}
		return ret;
	}

	/*
	 * Time complexity O(N^2)
	 * Space complexity O(1)
	 */
	private List<List<Integer>> N2TimeConstantSpace(int[] nums, int n) {
		//WRITE CODE
		List<List<Integer>> ret = new ArrayList<>();
		Arrays.sort(nums);
		int previ = nums.length > 0 ? ~nums[0] : 0;
		for(int i = 0; i < nums.length-2; ++i) {
			if (nums[i] != previ) {
				previ = nums[i];
				int j = i+1, k = nums.length-1;
				while(j < k) {
					long val = (long)nums[i] + (long)nums[j] + (long)nums[k];
					if (val == (long)n) {
						List<Integer> entry = new ArrayList<>();
						entry.add(nums[i]);
						entry.add(nums[j]);
						entry.add(nums[k]);
						ret.add(entry);
					}
					if (val <= (long)n) {
						do {
							++j;
						} while(j < k && nums[j] == nums[j-1]);
					}
					if (val >= (long)n) {
						do {
							--k;
						} while(j < k && nums[k] == nums[k+1]);
					}
				}
			}
		}
		return ret;
	}

	public static void main(String[] args) {
//		if (false) { //Change it true, if you want to dump all output to a file
//			System.out.println("Writing to 3sumoutput.txt") ;
//			try {
//				System.setOut(new PrintStream(new FileOutputStream("3sumoutput.txt")));
//			} catch (FileNotFoundException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
//		}
		System.out.println("ThreeSum.java STARTS");
		String version = System.getProperty("java.version");
		System.out.println("Java version used for this program is " + version);
		ThreeSum p = new ThreeSum() ;
		System.out.println("ThreeSum.java ENDS");
	}
}
