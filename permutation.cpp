#include "/workspaces/TP3/permutation.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include "/workspaces/TP3/arithm.hpp"
#include <unordered_set>

using namespace std;

// constructeurs de la classe Permutation
Permutation::Permutation(int m) : n(m), images(m)
{
    iota(images.begin(), images.end(), 0);
};
Permutation::Permutation(int m, mt19937 &g)
{
    n = m;
    for (int i = 0; i < n; i++)
    {
        images[i] = i;
    }
    shuffle(images.begin(), images.end(), g);
};
Permutation::Permutation(ifstream &f)
{
    f >> n;
    images.resize(n);
    for (int i = 0; i < n; i++)
    {
        f >> images[i];
    }
};

// Méthodes
Permutation Permutation::extend(int m) const
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

Permutation Permutation::operator*(const Permutation &p)
{
    Permutation prod;
    if (n > p.size())
    {
        prod = p.extend(n);
    }
    if (n < p.size())
    {
        prod = extend(p.size());
    }
    for (int i = 0; i < prod.size(); i++)
    {
        prod.images[i] = images[p[i]];
    }
    return prod;
}; // complexité O(max(n,p.size()))

ostream &operator<<(ostream &os, const Permutation &p)
{
    os << p.size() << endl;
    for (int i = 0; i < p.size(); i++)
    {
        os << p[i] << " ";
    }
};

list<int> Permutation::fixed_points() const
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

Permutation Permutation::inverse() const
{
    vector<int> v2(n);
    for (int i = 0; i < n; i++)
    {
        v2[images[i]] = i;
    }
    return Permutation(v2);
}; // complexité O(n)

bool Permutation::is_derangement() const
{
    if (fixed_points().size() != 0)
    {
        return false;
    }
    return true;
};

list<Cycle> Permutation::cycles() const
{
    list<Cycle> L;
    unordered_set<int> S;
    for (int i = 0; i < n; i++)
    {
        S.insert(i);
    }
    while (S.size() != 0)
    {
        list<int> l2;
        int i = *S.begin();
        l2.push_back(i);
        S.erase(i);
        while (images[i] != l2.front())
        {
            i = images[i];
            l2.push_back(i);
            S.erase(i);
        }
        L.push_back(Cycle(l2));
    }
};

int Permutation::order() const
{
    list<Cycle> l = cycles();
    list<int> orders;
    for (auto &c : l)
    {
        orders.push_back(c.order());
    }
    return lcm_list(orders);
};

