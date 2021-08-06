long decibinaryNumbers(long x)
{
    long result = 0;
    auto l = upper_bound(c.begin(), c.end(), x - 1) - 1;
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

