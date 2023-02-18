#include "/workspaces/TP3/permutation.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include "/workspaces/TP3/arithm.hpp"
#include <set>

using namespace std;

// constructeurs de la classe Permutation
Permutation::Permutation(int m) : n(m), images(m)
{
    iota(images.begin(), images.end(), 0);
};
Permutation::Permutation(int m, mt19937 &g): n(m), images(m)
{
    for (int i = 0; i < n; i++)
    {
        images[i] = i;
    }
for (int i = n - 1; i > 0; --i) {
        std::uniform_int_distribution<int> dis(0, i);
        int j = dis(g);
        std::swap(images[i], images[j]);
    }
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

int Permutation::operator[](int i) const
{
    return images[i];
}

Permutation operator*(const Permutation &p1, const Permutation &p2)
{
    vector<int> v2(p1.size());
    for (int i = 0; i < p1.size(); i++)
    {
        v2[i] = p1[p2[i]];
    }
    return Permutation(v2);
};
// complexité O(max(n,p.size()))

ostream &operator<<(ostream &os, const Permutation &p)
{
    os << p.size() << endl;
    for (int i = 0; i < p.size(); i++)
    {
        os << p[i] << " ";
    }
    return os;
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
    set<int> S;
    for (int i = 0; i < n; i++)
    {
        S.insert(i);
    }
    while (S.size() > 0)
    {
        list<int> l2;
        int x = *S.begin();
        l2.push_back(x);
        S.erase(x);
        while (images[x] != l2.front())
        {
            x = images[x];
            l2.push_back(x);
            S.erase(x);
        }
        // L.push_back(Cycle(l2));
        if (l2.size() > 1)
        {
            L.push_back(Cycle(l2));
        }
    }
    return L;
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