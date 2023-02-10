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
    vector<int> extend(int m) const { 
        vector<int> v2(m-n);
        for (int i=0;i<m-n){
            v2[i]=i+n;
        }
        return v2; };

}