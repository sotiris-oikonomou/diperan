//
// Created by sotiris on 25/8/2018.
//
#ifndef SIMPLE_MATRIX_MULTIPLICATION_H
#define SIMPLE_MATRIX_MULTIPLICATION_H

#include <vector>
#include <papi.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstdint>

namespace Diperan {
    namespace Benchmarks {
        inline void simple_matrix_mul(const uint64_t INDEX, const std::vector<float> &matrixa,
                                      const std::vector<float> &matrixb,
                                      std::vector<float> &mresult) {

            for (uint64_t row = 0; row < INDEX; row++) {
                for (uint64_t col = 0; col < INDEX; col++) {
                    for (uint64_t k = 0; k < INDEX; k++) {
                        mresult[(INDEX * row) + col] += matrixa[(INDEX * row) + k] * matrixb[(INDEX * k) + col];
                    }
                }
            }
        }

        inline void simple_matrix_mul(const uint64_t INDEX, const std::vector <double> &matrixa,
                                      const std::vector <double> &matrixb,
                                      std::vector <double> &mresult) {

            for (uint64_t row = 0; row < INDEX; row++) {
                for (uint64_t col = 0; col < INDEX; col++) {
                    for (uint64_t k = 0; k < INDEX; k++) {
                        mresult[(INDEX * row) + col] += matrixa[(INDEX * row) + k] * matrixb[(INDEX * k) + col];
                    }
                }
            }
        }
    }
}

#endif