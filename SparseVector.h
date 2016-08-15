//
// Created by chris on 8/14/16.
//

#ifndef HELLO_WORLD_SPARSEVECTOR_H
#define HELLO_WORLD_SPARSEVECTOR_H


#include <vector>

class SparseVector {
public:
    SparseVector(std::vector<int> dimensions, std::vector<double> values);
    double angle(const SparseVector& other) const;
    double magnitude() const;
    double dot(const SparseVector& other) const;

protected:
    std::vector<int> dimensions;
    std::vector<double> values;
};

#endif //HELLO_WORLD_SPARSEVECTOR_H
