//
// Created by sotiris on 23/8/2018.
//

#ifndef CLIENT_RUN_BENCHMARK_H
#define CLIENT_RUN_BENCHMARK_H

#include <vector>
#include <papi.h>
#include <iostream>
#include <thread>

#include "mainVariables.h"
#include "packet_type_definitions.h"
#include "benchmarking/benchmarks/matrix_multiplication.h"
#include "benchmarking/benchmarks/crc32.h"
#include "benchmarking/benchmarks/sha2.h"


namespace Diperan {
    void run_benchmark(std::string benchmark);
}

#endif //CLIENT_RUN_BENCHMARK_H
