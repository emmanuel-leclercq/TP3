#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

class Permutation
{
private:
    vector<int> v;
    int n;

public:
    int size() const { return n; };
    vector<int> extend(int n) const { return v; };
    
}