#include <list>
#include <numeric>


int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}

int gcd_list(std::list<int> l){
    return std::accumulate(l.begin(), l.end(), 1, gcd);
}

int lcm_list(std::list<int> l){
    return std::accumulate(l.begin(), l.end(), 1, lcm);
}

int main(){return 0;}