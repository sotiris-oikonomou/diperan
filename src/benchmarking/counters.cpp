//
// Created by sotiris on 27/8/2018.
//

#include "counters.h"

namespace Diperan {
    namespace Benchmarks {
        void prepare_counters(std::vector <int32_t> &event_codes) {
            int32_t retval;

            retval = PAPI_multiplex_init();
            if (retval != PAPI_OK) {
                std::cerr << "PAPI_multiplex_init error: " << PAPI_strerror(retval) << std::endl;
                return;
            }

            retval = PAPI_start_counters(event_codes.data(), event_codes.size());
            if (retval != PAPI_OK) {
                std::cerr << "PAPI_start_counters error: " << PAPI_strerror(retval) << std::endl;
                return;
            }
        }

        void read_counters(const std::vector <int32_t> &event_codes, std::vector <long long int> &counter_values) {
            counter_values.empty();
            counter_values.resize(event_codes.size());
            int32_t retval;

            retval = PAPI_stop_counters(&counter_values[0], event_codes.size());
            if (retval != PAPI_OK) {
                std::cerr << "PAPI_stop_counters error: " << PAPI_strerror(retval) << std::endl;
                return;
            }
        }

        void existing_events(std::vector <int32_t> &event_codes) {
            for (auto event_code : Diperan::g_state.used_papi_events) {
                if (check_event_exists(event_code)) {
                    event_codes.push_back(event_code);
                }
            }
        }

        bool check_event_exists(int32_t event_code) {
            int32_t exists = PAPI_query_event(event_code);
            if (exists == PAPI_OK) {
                return true;
            } else {
                return false;
            }
        }

        void create_benchmark_results_flatb(const std::vector <int32_t> &event_codes,
                                            const std::vector <long long int> &counter_values,
                                            int64_t cycles,
                                            int64_t time,
                                            std::string benchmark_type) {

            flatbuffers::FlatBufferBuilder builder(1024);

            std::vector <flatbuffers::Offset<EventResult>> event_results;

            if (event_codes.size() > counter_values.size()) {
                std::cerr << "Not all event codes have results" << std::endl;
                return;
            } else if (event_codes.size() > counter_values.size()) {
                std::cerr << "Some event codes are missing" << std::endl;
                return;
            }

            for (uint32_t i = 0; i < event_codes.size(); i++) {
                EventResultBuilder event_result(builder);
                event_result.add_event_code(event_codes.at(i));
                event_result.add_event_value(counter_values.at(i));
                auto event_result_finished = event_result.Finish();
                builder.Finish(event_result_finished);
                event_results.push_back(event_result_finished);
            }


            auto benchmark_type_flatb = builder.CreateString(benchmark_type);
            auto events_results_flatb_vec = builder.CreateVector(event_results);
            BenchmarkResultsBuilder benchmark_results(builder);
            benchmark_results.add_events_results(events_results_flatb_vec);
            benchmark_results.add_clock_cycles(cycles);
            benchmark_results.add_microseconds(time);
            benchmark_results.add_benchmark_type(benchmark_type_flatb);

            auto benchmark_results_finished = benchmark_results.Finish();
            builder.Finish(benchmark_results_finished);

            uint8_t *byte_buffer = builder.GetBufferPointer();
            int byte_buffer_size = builder.GetSize();

            outgoing_packet_t temp;
            temp.command = Diperan::benchmark_results_reply_pkt;
            temp.distribution_type = "SHOUT";
            temp.buffer.reserve(byte_buffer_size);
            temp.buffer.insert(temp.buffer.end(), byte_buffer, byte_buffer + byte_buffer_size);

            Diperan::g_outgoing_mutex.lock();
            Diperan::g_state.out_pkts.push(temp);

            if (Diperan::g_state.out_pkts.size() > Diperan::g_state.outgoing_queue_length) {
                Diperan::g_state.out_pkts.pop();
            }
            Diperan::g_outgoing_mutex.unlock();
        }
    }
}