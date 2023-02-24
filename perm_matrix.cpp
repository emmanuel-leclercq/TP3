#include "/workspaces/TP3/permutation.hpp"
#include "/workspaces/TP3/eigen/Eigen/Dense"

using namespace std;

typedef Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> MatrixInt;

MatrixInt perm_to_mat(const Permutation & p) {
    int n = p.size();
    MatrixInt m;
    m= MatrixInt::Zero(n, n);
    for (int i = 0; i < n; i++) {
        m(i, p[i]) = 1;
    }
    return m;
}

int main() {
    Permutation p(5);
    cout << p << endl;
    MatrixInt m = perm_to_mat(p);
    cout << m << endl;
    return 0;
}   