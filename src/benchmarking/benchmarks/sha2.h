//
// Created by sotiris on 2/9/2018.
//

#ifndef DIPERAN_SHA2_H
#define DIPERAN_SHA2_H

#include <vector>
#include <papi.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstdint>
#include <algorithm>

#include "mainVariables.h"
#include "benchmarking/algorithms/picosha2.h"
#include "benchmarking/counters.h"

namespace Diperan {
    namespace Benchmarks {
        void sha2_init(std::vector <uint8_t> &buffer);
        void sha2_run();
    }
}
#endif //DIPERAN_SHA2_H
