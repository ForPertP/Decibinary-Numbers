import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Result {

    /*
     * Complete the 'decibinaryNumbers' function below.
     *
     * The function is expected to return a LONG_INTEGER.
     * The function accepts LONG_INTEGER x as parameter.
     */

    private static final int MAX_DIGITS = 10;
    private static final int MAX_POWERS = 20;
    private static final int MAX_DECIMAL_VALUE = 286000;

    private static final long[][] dpTable = new long[MAX_DECIMAL_VALUE][MAX_POWERS];
    private static final long[] cumulativeCounts = new long[MAX_DECIMAL_VALUE];

    private static boolean precomputed = false;

    public static long decibinaryNumbers(long x) {}

}



public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int q = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, q).forEach(qItr -> {
            try {
                long x = Long.parseLong(bufferedReader.readLine().trim());

                long result = Result.decibinaryNumbers(x);

                bufferedWriter.write(String.valueOf(result));
                bufferedWriter.newLine();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
        bufferedWriter.close();
    }
}

