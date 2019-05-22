//
// Created by sotiris on 23/8/2018.
//

#include "benchmarking/run_benchmark.h"

namespace Diperan {
    void run_benchmark(std::string benchmark) {
        if(benchmark.compare(Diperan::benchmark_mmul_command_pkt) == 0) {
            Diperan::Benchmarks::matrix_multiplication_run(false);
        }
        else if(benchmark.compare(Diperan::benchmark_mmul_double_command_pkt) == 0) {
            Diperan::Benchmarks::matrix_multiplication_run(true);
        }
        else if(benchmark.compare(Diperan::benchmark_crc32_command_pkt) == 0) {
            Diperan::Benchmarks::crc32_run();
        }
        else if(benchmark.compare(Diperan::benchmark_sha2_command_pkt) == 0) {
            Diperan::Benchmarks::sha2_run();
        }
    }
}