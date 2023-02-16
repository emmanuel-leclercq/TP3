#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <list>
#include <string>
#include <numeric>

using namespace std;

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}

int calculate_lcm(const std::vector<int> &v)
{
    return std::accumulate(v.begin(), v.end(), 1, lcm);
}

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
    vector<int> images;

    // mutateur
    const int &operator[](int &i) { return images[i]; };

public:
    // constructeur
    Permutation(int m) : images(m)
    {
        n = m;
        for (int i = 0; i < n; i++)
        {
            images[i] = i;
        }
    };
    Permutation(const vector<int> &v) : images(v)
    {
        n = v.size();
    };
    Permutation(int m, mt19937 &g) : images(m)
    {
        n = m;
        for (int i = 0; i < n; i++)
        {
            images[i] = i;
        }
        shuffle(images.begin(), images.end(), g);
    };
    Permutation(ifstream &f)
    {
        f >> n;
        images.resize(n);
        for (int i = 0; i < n; i++)
        {
            f >> images[i];
        }
    };
    Permutation() : images(0){};

    // méthodes
    int size() const { return n; };
    Permutation extend(int m) const
    {
        if (m > n)
        {
            vector<int> v2(m);
            for (int i = 0; i < n; i++)
            {
                v2[i] = images[i];
            }
            for (int i = n; i < m; i++)
            {
                v2[i] = i;
            }
            return Permutation(v2);
        }
    }
    Permutation inverse() const
    {
        vector<int> v2(n);
        for (int i = 0; i < n; i++)
        {
            v2[images[i]] = i;
        }
        return Permutation(v2);
    };//complexité O(n)

    list<int> fixed_points() const
    {
        list<int> l;
        for (int i = 0; i < n; i++)
        {
            if (images[i] == i)
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
        for (int i = 0; i < n; i++)
        {
            if (images[i] != i)
            {
                int b = images[i];
                Cycle c(i);
                while (b != i)
                {
                    c.push_back(b);
                    b = images[b];
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
        for (auto &c : l)
        {
            orders.push_back(c.order());
        }
        return calculate_lcm(orders);
    };

    // operator
    int operator[](int &i) const { return images[i]; };
    friend ostream &operator<<(ostream &os, const Permutation &p)
    {   
        os<<p.size()<<endl;
        for (int i = 0; i < p.size(); i++)
        {
            os << p[i] << " ";
        }
        return os;
    };
    friend Permutation operator*(const Permutation &p1, const Permutation &p2)
    {
        if (p1.size() > p2.size())
        {
            p2.extend(p1.size());
        }
        if (p1.size() < p2.size())
        {
            p1.extend(p2.size());
        }
        Permutation p(p1.size());
        for (int i = 0; i < p.size(); i++)
        {
            p.images[i] = p1.images[p2.images[i]];
        }
        return p;
    }; //complexité=O(n)
};