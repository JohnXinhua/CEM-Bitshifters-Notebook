import java.util.*;
import java.io.*;
 
public class Main {
	public static void main(String... args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String line = br.readLine();
		StringTokenizer st = new StringTokenizer(line);
		int N = Integer.parseInt(st.nextToken()),
			K = Integer.parseInt(st.nextToken());
		int res = 0;
		while(N-- != 0) {
			res += (Integer.parseInt(br.readLine()) % K == 0 ? 1 : 0);
		}
		System.out.println(res);
	}
}
 
