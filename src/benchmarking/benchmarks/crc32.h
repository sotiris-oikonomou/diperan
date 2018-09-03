//
// Created by sotiris on 2/9/2018.
//

#ifndef DIPERAN_CRC32_H
#define DIPERAN_CRC32_H

#define CRCPP_USE_NAMESPACE
#define CRCPP_USE_CPP11

#include <vector>
#include <papi.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstdint>
#include <algorithm>

#include "mainVariables.h"
#include "benchmarking/algorithms/CRC.h"
#include "benchmarking/counters.h"

namespace Diperan {
    namespace Benchmarks {
        void crc32_init(std::vector<uint8_t>& buffer);
        void crc32_run();
    }
}

#endif //DIPERAN_CRC32_H
