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
    list<int> elem;

public:
    // constructeur
    Cycle(list<int> l) : elem(l){};

    // méthodes
    int order() const { return elem.size(); };

    // operators
    friend bool operator<(const Cycle &c1, const Cycle &c2)
    {
        return (c1.order() < c2.order());
    };
    friend ostream &operator<<(ostream &os, const Cycle &c)
    {
        auto affiche = [](int x)
        { cout << x << " "; };
        for_each(c.elem.begin(), c.elem.end(), affiche);
        return os;
    };
};

#ifndef permutation
#define permutation
class Permutation
{
private:
    // attributs
    int n;
    vector<int> images;

    // mutateur
    int &operator[](int &i) { return images[i]; };

public:
    // constructeurs
    Permutation(int m);
    Permutation(const vector<int> &v) : n(v.size()), images(v){};
    Permutation(int m, mt19937 &g);
    Permutation(ifstream &f);
    Permutation() : images(0){};

    // méthodes
    int size() const { return n; };
    Permutation extend(int m) const;
    Permutation inverse() const;
    list<int> fixed_points() const;
    bool is_derangement() const;
    list<Cycle> cycles() const;
    int order() const;

    // operators
    int operator[](int i) const;
    friend ostream &operator<<(ostream &, const Permutation &);
    friend Permutation operator*(const Permutation &, const Permutation &);

    // templates
    template <typename T>
    vector<T> permute(std::vector<T> &v) const
    {

        if (n <= v.size())
        {
            for (int i = 0; i < n; ++i)
            {
                swap(v[i], v[images[i]]);
            }
        }
        return v;
    };
};
#endif