#ifndef HELLO_WORLD_SPARSEVECTOR_H
#define HELLO_WORLD_SPARSEVECTOR_H

#include <vector>
#include <memory>

using namespace std;

class SparseVector {
public:
    SparseVector(vector<int>* dimensions, vector<double>* values);
    double angle(const SparseVector& other) const;
    double magnitude() const;
    double dot(const SparseVector& other) const;

protected:
    unique_ptr<vector<int>> dimensions;
    unique_ptr<vector<double>> values;
};

#endif //HELLO_WORLD_SPARSEVECTOR_H
