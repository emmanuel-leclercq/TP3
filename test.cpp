#include <iostream>
#include <vector>
#include <numeric>
#include </workspaces/TP3/permutations.hpp>

int main() {
  vector<int> v{2, 4, 5, 3, 1, 0};
  Permutation a(v);
  Permutation b(3);
  cout<<a*b<<endl;
  return 0;
}
