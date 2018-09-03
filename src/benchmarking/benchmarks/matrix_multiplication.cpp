//
// Created by sotiris on 26/8/2018.
//

#include "matrix_multiplication.h"

namespace Diperan {
    namespace Benchmarks {
        void matrix_multiplication_init(const uint64_t INDEX,
                                        std::vector<float> &matrixa,
                                        std::vector<float> &matrixb,
                                        std::vector<float> &mresult) {

            matrixa.clear();
            matrixa.resize(INDEX * INDEX);
            matrixb.clear();
            matrixb.resize(INDEX * INDEX);
            mresult.clear();
            mresult.resize(INDEX * INDEX);

            std::fill(mresult.begin(), mresult.end(), 0.0);
            for (uint64_t i = 0; i < INDEX * INDEX; i++) {
                srand(time(NULL));
                matrixa[i] = static_cast<float>(rand() * 1.1);
                matrixb[i] = static_cast<float>(rand() * 1.1);
            }
        }

        void matrix_multiplication_init(const uint64_t INDEX,
                                        std::vector<double> &matrixa,
                                        std::vector<double> &matrixb,
                                        std::vector<double> &mresult) {

            matrixa.clear();
            matrixa.resize(INDEX * INDEX);
            matrixb.clear();
            matrixb.resize(INDEX * INDEX);
            mresult.clear();
            mresult.resize(INDEX * INDEX);

            std::fill(mresult.begin(), mresult.end(), 0.0);
            for (uint64_t i = 0; i < INDEX * INDEX; i++) {
                srand(time(NULL));
                matrixa[i] = static_cast<double>(rand() * 1.1);
                matrixb[i] = static_cast<double>(rand() * 1.1);
            }
        }

        void matrix_multiplication_run(const bool double_precision) {
            uint64_t INDEX = 1000;


            if (double_precision) {
                std::vector<double> matrixa;
                std::vector<double> matrixb;
                std::vector<double> mresult;
                std::vector <int32_t> event_codes;
                std::vector <int64_t> counter_values;

                Diperan::Benchmarks::matrix_multiplication_init(INDEX, matrixa, matrixb, mresult);
                Diperan::Benchmarks::existing_events(event_codes);

                for (uint32_t i = 0; i < Diperan::g_state.benchmark_warmup; i++) {
                    simple_matrix_mul(INDEX, matrixa, matrixb, mresult);
                }

                int64_t start_cycles, end_cycles, start_time, end_time;

                Diperan::Benchmarks::prepare_counters(event_codes);
                start_cycles = PAPI_get_real_cyc();
                start_time = PAPI_get_real_usec();
                simple_matrix_mul(INDEX, matrixa, matrixb, mresult);
                end_cycles = PAPI_get_real_cyc();
                end_time = PAPI_get_real_usec();
                Diperan::Benchmarks::read_counters(event_codes, counter_values);
                Diperan::Benchmarks::create_benchmark_results_flatb(event_codes, counter_values, (end_cycles - start_cycles),
                                               (end_time - start_time), Diperan::benchmark_mmul_double_command_pkt);

            } else {
                std::vector<float> matrixa;
                std::vector<float> matrixb;
                std::vector<float> mresult;
                std::vector <int32_t> event_codes;
                std::vector <int64_t> counter_values;

                Diperan::Benchmarks::matrix_multiplication_init(INDEX, matrixa, matrixb, mresult);
                Diperan::Benchmarks::existing_events(event_codes);

                for (uint32_t i = 0; i < Diperan::g_state.benchmark_warmup; i++) {
                    simple_matrix_mul(INDEX, matrixa, matrixb, mresult);
                }

                int64_t start_cycles, end_cycles, start_time, end_time;

                Diperan::Benchmarks::prepare_counters(event_codes);
                start_cycles = PAPI_get_real_cyc();
                start_time = PAPI_get_real_usec();
                simple_matrix_mul(INDEX, matrixa, matrixb, mresult);
                end_cycles = PAPI_get_real_cyc();
                end_time = PAPI_get_real_usec();
                Diperan::Benchmarks::read_counters(event_codes, counter_values);
                Diperan::Benchmarks::create_benchmark_results_flatb(event_codes, counter_values, (end_cycles - start_cycles),
                                               (end_time - start_time), Diperan::benchmark_mmul_command_pkt);

            }
        }
    }
}