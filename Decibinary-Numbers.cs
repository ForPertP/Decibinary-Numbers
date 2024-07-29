using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;

class Result
{

    /*
     * Complete the 'decibinaryNumbers' function below.
     *
     * The function is expected to return a LONG_INTEGER.
     * The function accepts LONG_INTEGER x as parameter.
     */

    private const int MAX_DIGITS = 10;
    private const int MAX_POWERS = 20;
    private const int MAX_DECIMAL_VALUE = 286000;

    private static readonly long[,] dpTable = new long[MAX_DECIMAL_VALUE, MAX_POWERS];
    private static readonly long[] cumulativeCounts = new long[MAX_DECIMAL_VALUE];

    static Result()
    {
        PrecomputeTable();
    }
    
   static Lazy<bool> precomputed = new Lazy<bool>(() =>
    {
        PrecomputeTable();
        return true;
    });
    
    //private static bool precomputed = false;    

    private static void PrecomputeTable()
    {
        for (int i = 0; i < MAX_DECIMAL_VALUE; ++i)
        {
            dpTable[i, 0] = i < MAX_DIGITS ? 1 : 0;

            for (int j = 1; j < MAX_POWERS; ++j)
            {
                int powerValue = 1 << j;
                for (int digit = 0; digit < MAX_DIGITS; ++digit)
                {
                    int remainingValue = i - digit * powerValue;
                    if (remainingValue < 0) break;
                    dpTable[i, j] += dpTable[remainingValue, j - 1];
                }
            }
        }

        for (int i = 1; i < MAX_DECIMAL_VALUE; ++i)
        {
            cumulativeCounts[i] = dpTable[i - 1, MAX_POWERS - 1] + cumulativeCounts[i - 1];
        }
    }

    public static long decibinaryNumbers(long x)
    {
        // bool ensurePrecomputed = precomputed.Value;
        
        // if (!precomputed)
        // {
        //     precomputed = true;
        //     PrecomputeTable();
        // }
        
        if (x <= 0) return -1;

        long result = 0;
        int decimalValue = Array.BinarySearch(cumulativeCounts, x - 1);
        if (decimalValue < 0)
        {
            decimalValue = ~decimalValue - 1;
        }

        long offset = (x - 1) - cumulativeCounts[decimalValue];

        for (int j = MAX_POWERS - 1; j >= 1; --j)
        {
            int binaryPlaceValue = 1 << j;

            for (int digit = 0; digit < MAX_DIGITS; ++digit)
            {
                int remainingValue = decimalValue - digit * binaryPlaceValue;

                if (remainingValue >= 0 && offset < dpTable[remainingValue, j - 1])
                {
                    result = result * 10 + digit;
                    decimalValue = remainingValue;
                    break;
                }

                if (remainingValue >= 0)
                {
                    offset -= dpTable[remainingValue, j - 1];
                }
            }
        }

        result = result * 10 + decimalValue;
        return result;
    }
}


class Solution
{
    public static void Main(string[] args)
    {
        TextWriter textWriter = new StreamWriter(@System.Environment.GetEnvironmentVariable("OUTPUT_PATH"), true);

        int q = Convert.ToInt32(Console.ReadLine().Trim());

        for (int qItr = 0; qItr < q; qItr++)
        {
            long x = Convert.ToInt64(Console.ReadLine().Trim());

            long result = Result.decibinaryNumbers(x);

            textWriter.WriteLine(result);
        }

        textWriter.Flush();
        textWriter.Close();
    }
}
