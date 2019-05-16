//
// Created by sotiris on 2/9/2018.
//

#include "crc32.h"

namespace Diperan {
    namespace Benchmarks {
        void crc32_init(std::vector <uint8_t> &buffer) {
            buffer.clear();
            buffer.resize(Diperan::g_state.benchmark_buffer_size);
            for (uint64_t i = 0; i < buffer.size(); i++) {
                srand(time(NULL));
                buffer[i] = rand() % 255;
            }
        }

        void crc32_run() {
            std::vector <uint8_t> buffer;
            std::vector <int32_t> event_codes;
            std::vector <long long int> counter_values;

            Diperan::Benchmarks::crc32_init(buffer);
            Diperan::Benchmarks::existing_events(event_codes);

            for (uint32_t i = 0; i < Diperan::g_state.benchmark_warmup; i++) {
                CRCPP::CRC::Calculate(buffer.data(), buffer.size(), CRCPP::CRC::CRC_32());
            }

            int64_t start_cycles, end_cycles, start_time, end_time;

            Diperan::Benchmarks::prepare_counters(event_codes);
            start_cycles = PAPI_get_real_cyc();
            start_time = PAPI_get_real_usec();
            CRCPP::CRC::Calculate(buffer.data(), buffer.size(), CRCPP::CRC::CRC_32());
            end_cycles = PAPI_get_real_cyc();
            end_time = PAPI_get_real_usec();
            Diperan::Benchmarks::read_counters(event_codes, counter_values);
            Diperan::Benchmarks::create_benchmark_results_flatb(event_codes,
                                                                counter_values,
                                                                (end_cycles - start_cycles),
                                                                (end_time - start_time),
                                                                Diperan::benchmark_crc32_command_pkt);
        }
    }
}