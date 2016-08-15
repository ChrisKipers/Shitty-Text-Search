#include <math.h>
#include <vector>

#include "SparseVector.h"

SparseVector::SparseVector(std::vector<int> dimensions, std::vector<double> values) : dimensions(dimensions), values(values) {}

double SparseVector::angle(const SparseVector &other) const {
    double degree_in_rad = acos(dot(other) / (magnitude() * other.magnitude()));
    return degree_in_rad * (180.0 / M_PI);
}

double SparseVector::magnitude() const {
    double accumulator = 0;
    for (int i = 0; i < dimensions.size(); i++) {
        accumulator += powf(values[i], 2);
    }
    return sqrtf(accumulator);
}

double SparseVector::dot(const SparseVector &other) const {
    double accumulator = 0;
    int this_index = 0;
    int other_index = 0;
    while (this_index < dimensions.size() && other_index < other.dimensions.size()) {
        if (dimensions[this_index] == other.dimensions[other_index]) {
            accumulator += values[this_index] * other.values[other_index];
            this_index++;
            other_index++;
        } else if (dimensions[this_index] < other.dimensions[other_index]) {
            this_index++;
        } else {
            other_index++;
        }
    }
    return accumulator;
}