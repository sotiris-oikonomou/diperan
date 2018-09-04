//
// Created by sotiris on 27/8/2018.
//

#ifndef COUNTERS_H
#define COUNTERS_H

#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <papi.h>

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/benchmark_results_generated.h"
#include "mainVariables.h"
#include "packet_type_definitions.h"

using namespace Diperan::Benchmark::Results;

namespace Diperan {
    namespace Benchmarks {
        void prepare_counters(std::vector<int32_t>& event_codes);
        void read_counters(const std::vector<int32_t>& event_codes, std::vector<long long int>& counter_values);
        void existing_events(std::vector<int32_t>& event_codes);
        bool check_event_exists(int32_t event_code);
        void create_benchmark_results_flatb(const std::vector <int32_t> &event_codes,
                                            const std::vector <long long int> &counter_values,
                                            int64_t cycles,
                                            int64_t time,
                                            std::string benchmark_type);
    }
}

#endif //COUNTERS_H
