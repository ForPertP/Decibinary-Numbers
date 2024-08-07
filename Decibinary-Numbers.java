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

    private static void precomputeTable() {
        for (int decimalValue = 0; decimalValue < MAX_DECIMAL_VALUE; ++decimalValue) {
            dpTable[decimalValue][0] = decimalValue < MAX_DIGITS ? 1 : 0;

            for (int powerIndex = 1; powerIndex < MAX_POWERS; ++powerIndex) {
                int powerValue = 1 << powerIndex;
                for (int digit = 0; digit < MAX_DIGITS; ++digit) {
                    int remainingValue = decimalValue - digit * powerValue;

                    if (remainingValue < 0) break;

                    dpTable[decimalValue][powerIndex] += dpTable[remainingValue][powerIndex - 1];
                }
            }
        }

        for (int decimalValue = 1; decimalValue < MAX_DECIMAL_VALUE; ++decimalValue) {
            cumulativeCounts[decimalValue] = 
                dpTable[decimalValue - 1][MAX_POWERS - 1] + cumulativeCounts[decimalValue - 1];
        }
    }


    public static long decibinaryNumbers(long x) {
        if (!precomputed) {
            precomputed = true;
            precomputeTable();
        }

        if (x <= 0) return -1;

        long result = 0;
        int decimalValue = Arrays.binarySearch(cumulativeCounts, x - 1);
        if (decimalValue < 0) {
            decimalValue = -decimalValue - 2;
        }

        long offset = (x - 1) - cumulativeCounts[decimalValue];

        for (int powerIndex = MAX_POWERS - 1; powerIndex >= 1; --powerIndex) {
            int binaryPlaceValue = 1 << powerIndex;

            for (int digit = 0; digit < MAX_DIGITS; ++digit) {
                int remainingValue = decimalValue - digit * binaryPlaceValue;

                if (remainingValue >= 0 && offset < dpTable[remainingValue][powerIndex - 1]) {
                    result = result * 10 + digit;
                    decimalValue = remainingValue;
                    break;
                }

                if (remainingValue >= 0) {
                    offset -= dpTable[remainingValue][powerIndex - 1];
                }
            }
        }

        result = result * 10 + decimalValue;
        return result;
    }


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
