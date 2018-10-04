import java.io.*;
import java.awt.geom.Area;
import java.awt.geom.Path2D;
import java.awt.geom.PathIterator;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		int T = 1;
		for (int i = 0; i < T; i++) solve(in, out);
		out.close();
	}
	public static void solve(InputReader in, PrintWriter out) {
	    int n = in.nextInt();//多边形个数
		Area totalArea = new Area();
		double total = 0.0;
		for(int i = 0;i < n; i++) {
	    	Path2D.Double pd = new Path2D.Double();
	    	int m = in.nextInt();
			double a = in.nextDouble(),b = in.nextDouble();
			pd.moveTo(a,b);
			for(int j = 1;j < m; j++) {//读入第i个多边形,这里是四边形
				a = in.nextDouble();
				b = in.nextDouble();
				pd.lineTo(a,b);
			}
			pd.closePath();
			Area tmpArea = new Area(pd);
			totalArea.add(tmpArea);//加入总图形
			total += calcArea(tmpArea);//获得第i个多边形的面积
		}
		out.println(total * 0.5 + " " + calcArea(totalArea) * 0.5);
	}
	private static double calcArea(Area area) {
		double ret = 0;
		PathIterator it = area.getPathIterator(null);//获得该图形的边界
		double[] buffer = new double[6], last = new double[2], first = null;
		while (!it.isDone()) {
			switch (it.currentSegment(buffer)) {
				case PathIterator.SEG_MOVETO:
				case PathIterator.SEG_LINETO:
					if (first == null) {
						first = new double[2];
						first[0] = buffer[0]; first[1] = buffer[1];
					} else {
						ret += last[0] * buffer[1] - last[1] * buffer[0];
					}
					last[0] = buffer[0]; last[1] = buffer[1];
					break;
				case PathIterator.SEG_CLOSE:
					ret += last[0] * first[1] - last[1] * first[0];
					first = null;
					break;
			}
			it.next();
		}
		if(ret < 0) ret = -ret;
		return ret;
	}

	static class InputReader {
		public BufferedReader reader;
		public StringTokenizer tokenizer;

		public InputReader(InputStream stream) {
			reader = new BufferedReader(new InputStreamReader(stream), 32768);
			tokenizer = null;
		}

		public String next() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					tokenizer = new StringTokenizer(reader.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return tokenizer.nextToken();
		}

		public int nextInt() {
			return Integer.parseInt(next());
		}

		public double nextDouble() {
			return Double.parseDouble(next());
		}

	}
}