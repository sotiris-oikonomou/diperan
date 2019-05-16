//
// Created by sotiris on 26/8/2018.
//

#ifndef DIPERAN_MATRIX_MULTIPLICATION_H
#define DIPERAN_MATRIX_MULTIPLICATION_H
#include <vector>
#include <papi.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstdint>
#include <algorithm>

#include "mainVariables.h"
#include "benchmarking/algorithms/simple_matrix_mul.h"
#include "benchmarking/counters.h"

namespace Diperan {
    namespace Benchmarks {
        void matrix_multiplication_init(const uint64_t INDEX,
                                               std::vector<float>& matrixa,
                                               std::vector<float>& matrixb,
                                               std::vector<float>& mresult);

        void matrix_multiplication_init(const uint64_t INDEX,
                                               std::vector<double>& matrixa,
                                               std::vector<double>& matrixb,
                                               std::vector<double>& mresult);

        void matrix_multiplication_run(const bool double_precision);
    }
}
#endif //DIPERAN_MATRIX_MULTIPLICATION_H
