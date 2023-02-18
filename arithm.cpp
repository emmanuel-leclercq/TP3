#include <list>
#include <numeric>

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

int lcm_list(std::list<int> l)
{
    if (l.empty())
    {
        return 1;
    }
    int result = l.front();
    l.pop_front();
    for (int x : l)
    {
        result = lcm(result, x);
    }
    return result;
}
