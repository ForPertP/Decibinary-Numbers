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

// Source:
// https://www.hackerrank.com/challenges/decibinary-numbers/forum craig53

constexpr int digits = 10;
constexpr int powers = 20;
constexpr int max_value = 290000;
vector<vector<long>> v(max_value, vector<long>(powers));
vector<long> c(max_value);

void pre_make_table()
{
    for (int i = 0; i < max_value; ++i)
    {
        v[i][0] = i < digits;

        for (int j = 1; j < powers; ++j)
        {
            for (int k = 0; k < digits; ++k)
            {
                int value = i - k * (1 << j);
        
                if (value < 0)
                    break;
                    
                v[i][j] += v[value][j - 1];
            }
        }
    }

    for (int i = 1; i < max_value; i++)
    {
        c[i] = v[i - 1][powers - 1] + c[i - 1];
    }
}

long decibinaryNumbers(long x)
{
    long result = 0;
    auto l = std::upper_bound(c.begin(), c.end(), x - 1) - 1;
    int value = l - c.begin();
    long offset = (x - 1) - *l;

    for (int i = powers - 1; i >= 1; i--)
    {
        int power = 1 << i;

        for (int digit = 0; digit < digits; digit++)
        {
            int v1 = value - digit * power;

            if (offset < v[v1][i - 1])
            {
                result += digit;
                value -= power * digit;
                break;
            }

            offset -= v[v1][i - 1];
        }

        result *= 10;
    }

    result += value;
    return result;
}

int main()
{
    pre_make_table();
    
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
