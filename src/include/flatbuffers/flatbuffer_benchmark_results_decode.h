//
// Created by sotiris on 23/8/2018.
//

#ifndef FLATBUFFER_BENCHMARK_RESULTS_DECODE_H
#define FLATBUFFER_BENCHMARK_RESULTS_DECODE_H

#include <memory>
#include <iostream>
#include <string>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/benchmark_results_generated.h"
#include "optional.h"

using namespace Diperan::Benchmark::Results;

namespace Diperan {
    inline std::experimental::optional<const BenchmarkResults *>
    flatbuffer_benchmark_results_decode(const std::vector <uint8_t> &buffer) {
        auto temp_verifier = flatbuffers::Verifier(reinterpret_cast<const uint8_t *>(buffer.data()), buffer.size());
        bool is_ok = VerifyBenchmarkResultsBuffer(temp_verifier);

        if (is_ok) {
            auto events_obj = GetBenchmarkResults(reinterpret_cast<const char *>(buffer.data()));
            return events_obj;
        } else {
            std::cerr << "BenchmarkResults flatbuffer verification Error" << std::endl;
            return {};
        }
    }

    inline void flatbuffer_benchmark_results_print(const BenchmarkResults *flatbuffer_obj, std::string uuid) {
        if (flatbuffer_obj == nullptr) {
            return;
        }
        auto events_results = flatbuffer_obj->events_results();
        auto cycles = flatbuffer_obj->clock_cycles();
        auto microseconds = flatbuffer_obj->microseconds();
        auto benchmark_type = flatbuffer_obj->benchmark_type();
        std::cout << "Node: " << uuid << std::endl;
        std::cout << " Benchmark: "
                  << benchmark_type->c_str()
                  << "\tCycles: "
                  << cycles
                  << "\t uSec: "
                  << microseconds
                  << std::endl;

        int retval = PAPI_library_init(PAPI_VER_CURRENT);
        if (retval != PAPI_VER_CURRENT) {
            std::cerr << "PAPI library init error!" << std::endl;
        }
        PAPI_event_info_t info;
        for (uint32_t i = 0; i < events_results->Length(); i++) {
            if (PAPI_get_event_info(events_results->Get(i)->event_code(), &info) == PAPI_OK) {
                std::cout << "  "
                          << info.symbol
                          << ": "
                          << events_results->Get(i)->event_value()
                          << std::endl;
            } else {
                std::cout << "  "
                          << events_results->Get(i)->event_code() << ": "
                          << events_results->Get(i)->event_value()
                          << std::endl;
            }
        }
    }
}
#endif //FLATBUFFER_BENCHMARK_RESULTS_DECODE_H
