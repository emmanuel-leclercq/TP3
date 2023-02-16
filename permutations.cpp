#include </workspaces/TP3/permutations.hpp>
#include <iostream>
#include <fstream>
#include <algorithm> // pour for_each et max_element
#include <random>    // pour le générateur std::mt19937
// donc compiler en -std=c++11

using namespace std;

int main()
{
    // Premiere partie
    vector<int> v{2, 4, 5, 3, 1, 0}; // syntaxe C++11 avec { }
    Permutation a(v);
    Permutation b(6); // identite
    for (int i = 0; i <= 6; ++i)
    {
        cout << "a^" << i << endl
             << b << endl;
        b = b * a;
    }
    list<int> fp = a.fixed_points();
    auto affiche = [](int x)
    { cout << x << " "; };
    for_each(fp.begin(), fp.end(), affiche);
    cout << "\n";
    // Deuxieme partie
    ifstream fichier_s("./file_s.dat");
    ifstream fichier_t("./file_t.dat");
    Permutation s(fichier_s);
    Permutation t(fichier_t);
    fichier_s.close();
    fichier_t.close();

    Permutation u = s * t.inverse();
    cout << "L'ordre de la permutation s*t^-1 est égal à "
         << u.order() << endl;
    list<Cycle> l = u.cycles();
    cout << "Cette permutation a " << l.size() << "cycles, dont le plus grand a pour longueur " << (*max_element(l.begin(), l.end())).order() << endl;
    // attention, cela utilise < sur des Cycle !
    //  Troisieme partie
    mt19937 g;
    unsigned n = 100;
    unsigned nb_echant = 10000;
    unsigned nb_derang = 0;
    for (unsigned i = 0; i < nb_echant; ++i)
    {
        nb_derang += Permutation(n, g).is_derangement();
    }
    cout << "La proportion de dérangements est environ "
         << nb_derang / double(nb_echant) << endl;
    
    return 0;
}