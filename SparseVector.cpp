#include <math.h>
#include <vector>

#include "SparseVector.h"

using namespace std;

SparseVector::SparseVector(vector<int>* dimensions, vector<double>* values) : dimensions(dimensions), values(values) {}

double SparseVector::angle(const SparseVector &other) const {
    double degree_in_rad = acos(dot(other) / (magnitude() * other.magnitude()));
    return degree_in_rad * (180.0 / M_PI);
}

double SparseVector::magnitude() const {
    double accumulator = 0;
    for (int i = 0; i < dimensions.get()->size(); i++) {
        accumulator += powf(values.get()->at(i), 2);
    }
    return sqrtf(accumulator);
}

double SparseVector::dot(const SparseVector &other) const {
    double accumulator = 0;
    int this_index = 0;
    int other_index = 0;
    while (this_index < dimensions.get()->size() && other_index < other.dimensions.get()->size()) {
        if (dimensions.get()->at(this_index) == other.dimensions.get()->at(other_index)) {
            accumulator += values.get()->at(this_index) * other.values.get()->at(other_index);
            this_index++;
            other_index++;
        } else if (dimensions.get()->at(this_index) < other.dimensions.get()->at(other_index)) {
            this_index++;
        } else {
            other_index++;
        }
    }
    return accumulator;
}