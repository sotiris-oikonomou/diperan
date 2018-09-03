//
// Created by sotiris on 2/9/2018.
//

#include "sha2.h"

namespace Diperan {
    namespace Benchmarks {
        void sha2_init(std::vector <uint8_t> &buffer) {
            buffer.clear();
            buffer.resize(Diperan::g_state.benchmark_buffer_size);
            for (uint64_t i = 0; i < buffer.size(); i++) {
                srand(time(NULL));
                buffer[i] = rand() % 255;
            }
        }

        void sha2_run() {
            std::vector <uint8_t> buffer;
            std::vector <uint8_t> hash_buffer(picosha2::k_digest_size);
            std::vector <int32_t> event_codes;
            std::vector <int64_t> counter_values;

            Diperan::Benchmarks::sha2_init(buffer);
            Diperan::Benchmarks::existing_events(event_codes);

            for (uint32_t i = 0; i < Diperan::g_state.benchmark_warmup; i++) {
                picosha2::hash256(buffer.begin(), buffer.end(), hash_buffer.begin(), hash_buffer.end());
            }

            int64_t start_cycles, end_cycles, start_time, end_time;

            Diperan::Benchmarks::prepare_counters(event_codes);
            start_cycles = PAPI_get_real_cyc();
            start_time = PAPI_get_real_usec();
            picosha2::hash256(buffer.begin(), buffer.end(), hash_buffer.begin(), hash_buffer.end());
            end_cycles = PAPI_get_real_cyc();
            end_time = PAPI_get_real_usec();
            Diperan::Benchmarks::read_counters(event_codes, counter_values);
            Diperan::Benchmarks::create_benchmark_results_flatb(event_codes,
                                                                counter_values,
                                                                (end_cycles - start_cycles),
                                                                (end_time - start_time),
                                                                Diperan::benchmark_sha2_command_pkt);
        }
    }
    }