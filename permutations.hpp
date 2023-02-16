#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <list>
#include <string>
#include <numeric>

using namespace std;

class Cycle
{
private:
    // attribut
    string s;

public:
    // constructeur
    Cycle() : s(""){};
    Cycle(int i) : s(to_string(i)){};
    Cycle(string s) : s(s){};

    // méthodes
    int order() const { return s.size(); };
    void push_back(int i) { s += to_string(i); };
    void push_back(Cycle c) { s += c.s; };
    void push_front(int i) { s = to_string(i) + s; };
    void push_front(Cycle c) { s = c.s + s; };
    bool operator<(const Cycle &c) const { return order() < c.order(); };
};

class Permutation
{
private:
    // attribut
    int n;
    vector<int> v;

    // mutateur
    const int &operator[](int &i) { return v[i]; };

public:
    // constructeur
    Permutation(int n) : v(n)
    {
        for (int i = 0; i < n; i++)
        {
            v[i] = i;
        }
    };
    Permutation(vector<int> v) : v(v)
    {
        n = v.size();
    };
    Permutation(int n, mt19937 &g) : v(n)
    {
        for (int i = 0; i < n; i++)
        {
            v[i] = i;
        }
        shuffle(v.begin(), v.end(), g);
    };
    Permutation(ifstream &f)
    {
        f >> n;
        v.resize(n);
        for (int i = 0; i < n; i++)
        {
            f >> v[i];
        }
    };
    Permutation() : v(0){};

    // méthodes
    int size() const { return n; };
    Permutation extend(int m) const
    {
        vector<int> v2(m);
        for (int i = 0; i < n; i++)
        {
            v2[i] = v[i];
        }
        for (int i = n; i < m; i++)
        {
            v2[i] = i;
        }
        return Permutation(v2);
    }
    Permutation inverse() const
    {
        vector<int> v2(n);
        for (int i = 0; i < n; i++)
        {
            v2[v[i]] = i;
        }
        return Permutation(v2);
    };
    list<int> fixed_points() const
    {
        list<int> l;
        for (int i = 0; i < n; i++)
        {
            if (v[i] == i)
            {
                l.push_back(i);
            }
        }
        return l;
    };
    bool is_derangement() const
    {
        if (fixed_points().size() != 0)
        {
            return false;
        }
        return true;
    };
    list<Cycle> cycles() const
    {
        list<Cycle> l;
        for(int i=0;i<n;i++){
            if(v[i]!=i){
                int b=v[i];
                Cycle c(i);
                while(b!=i){
                    c.push_back(b);
                    b=v[b];
                }
                l.push_back(c);
            }
        }
        return l;
    };
    int order() const
    {
        list<Cycle> l = cycles();
        vector<int> orders;
        for (auto& c : l)
        {
            orders.push_back(c.order());
        }
        int lcm = std::accumulate(orders.begin(), orders.end(), 1, std::lcm<int, int>);
        return lcm;
    };

    // operator
    int operator[](int &i) const { return v[i]; };
    friend ostream &operator<<(ostream &os, const Permutation &p)
    {
        for (int i = 0; i < p.size(); i++)
        {
            os << p[i] << " ";
        }
        return os;
    };
    friend Permutation operator*(const Permutation &p1, const Permutation &p2)
    {
        Permutation p(p1.size());
        for (int i = 0; i < p.size(); i++)
        {
            p.v[i] = p1.v[p2.v[i]];
        }
        return p;
    };
};