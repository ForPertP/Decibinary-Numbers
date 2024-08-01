#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'decibinaryNumbers' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER x as parameter.
 */

constexpr int MAX_DIGITS = 10;
constexpr int MAX_POWERS = 20;
constexpr int MAX_DECIMAL_VALUE = 286000;

vector<vector<long>> dpTable(MAX_DECIMAL_VALUE, vector<long>(MAX_POWERS));
vector<long> cumulativeCounts(MAX_DECIMAL_VALUE);
std::once_flag precompute_flag;

void precomputeTable()
{
    for (int i = 0; i < MAX_DECIMAL_VALUE; ++i)
    {
        dpTable[i][0] = i < MAX_DIGITS ? 1 : 0;

        for (int j = 1; j < MAX_POWERS; ++j)
        {
            int powerValue = 1 << j;
     
            for (int digit = 0; digit < MAX_DIGITS; ++digit)
            {
                int remainingValue = i - digit * powerValue;
                if (remainingValue < 0) break;
                dpTable[i][j] += dpTable[remainingValue][j - 1];
            }
        }
    }

    for (int i = 1; i < MAX_DECIMAL_VALUE; ++i)
    {
        cumulativeCounts[i] = dpTable[i - 1][MAX_POWERS - 1] + cumulativeCounts[i - 1];
    }
}


long decibinaryNumbers(long x)
{
    std::call_once(precompute_flag, precomputeTable);
    //static bool precomputed = (precomputeTable(), true); 

    if (x <= 0) return -1;

    long result = 0;
    auto upperBound = upper_bound(cumulativeCounts.begin(), cumulativeCounts.end(), x - 1);

    if (upperBound == cumulativeCounts.begin())
    {
        return -1;
    }

    int decimalValue = (upperBound - cumulativeCounts.begin()) - 1;
    long offset = (x - 1) - cumulativeCounts[decimalValue];

    for (int j = MAX_POWERS - 1; j >= 1; --j)
    {
        int binaryPlaceValue = 1 << j;

        for (int digit = 0; digit < MAX_DIGITS; ++digit)
        {
            int remainingValue = decimalValue - digit * binaryPlaceValue;

            if (remainingValue >= 0 && offset < dpTable[remainingValue][j - 1])
            {
                result = result * 10 + digit;
                decimalValue = remainingValue;
                break;
            }

            if (remainingValue >= 0)
            {
                offset -= dpTable[remainingValue][j - 1];
            }
        }
    }

    result = result * 10 + decimalValue;
    return result;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string x_temp;
        getline(cin, x_temp);

        long x = stol(ltrim(rtrim(x_temp)));

        long result = decibinaryNumbers(x);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
