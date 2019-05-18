//
// Created by sotiris on 9/8/2018.
//

#include "processing/incoming/in_processor.h"

namespace Diperan {

    void incoming_packet_processing_loop() {

        while (!zsys_interrupted) {
            if (Diperan::g_state.in_pkts.size() > 0) {
                Diperan::incoming_packet_t temp_pkt;

                Diperan::g_incoming_mutex.lock();
                temp_pkt = Diperan::g_state.in_pkts.front();
                Diperan::g_state.in_pkts.pop();
                Diperan::g_incoming_mutex.unlock();

                if (Diperan::g_state.is_master_node) {//Master
                    if (temp_pkt.command.compare(Diperan::sys_info_pkt) == 0) {
                        Diperan::save_peer_node(temp_pkt);
                    } else if (temp_pkt.command.compare(Diperan::papi_supported_events_reply_pkt) == 0) {
                        std::vector <int32_t> temp;
                        auto events_flatb = Diperan::flatbuffer_events_info_decode(temp_pkt.buffer).value_or(nullptr);

                        if (events_flatb == nullptr) {
                            std::cerr << "Events info flatbuffer processing error" << std::endl;
                            continue;
                        }

                        for (uint32_t i = 0; i < events_flatb->event_codes()->Length(); i++) {
                            temp.push_back(events_flatb->event_codes()->Get(i));
                        }
                        Diperan::save_node_papi_supported_events(temp_pkt.UUID, temp);
                    } else if (temp_pkt.command.compare(Diperan::benchmark_results_reply_pkt) == 0) {
                        auto benchmark_results_flatb = Diperan::flatbuffer_benchmark_results_decode(
                                temp_pkt.buffer).value_or(nullptr);
                        if (benchmark_results_flatb == nullptr) {
                            std::cerr << "Benchmark results flatbuffer processing error" << std::endl;
                            continue;
                        }
                        Diperan::flatbuffer_benchmark_results_print(benchmark_results_flatb, temp_pkt.UUID);
                    }
                } else {//Node
                    if (temp_pkt.command.compare(Diperan::sys_info_command_pkt) == 0) {
                        //We are an ordinary node so we reply to a command incoming packet
                        Diperan::prepare_sys_info_packet();
                    } else if (temp_pkt.command.compare(Diperan::papi_supported_events_command_pkt) == 0) {
                        Diperan::prepare_supported_papi_events_pkt();
                    } else if (temp_pkt.command.compare(Diperan::benchmark_mmul_command_pkt) == 0) {
                        Diperan::run_benchmark(temp_pkt.command);
                    } else if (temp_pkt.command.compare(Diperan::benchmark_mmul_double_command_pkt) == 0) {
                        Diperan::run_benchmark(temp_pkt.command);
                    } else if (temp_pkt.command.compare(Diperan::benchmark_crc32_command_pkt) == 0) {
                        Diperan::run_benchmark(temp_pkt.command);
                    } else if (temp_pkt.command.compare(Diperan::benchmark_sha2_command_pkt) == 0) {
                        Diperan::run_benchmark(temp_pkt.command);
                    } else if (temp_pkt.command.compare(Diperan::peer_configuration_command_pkt) == 0) {
                        Diperan::flatbuffer_node_configuration_decode(temp_pkt.buffer);
                    }
                }
            }

            Diperan::thread_wait_random_time(Diperan::g_state.processing_incomings_loop_wait_time, 1);
        }
    }
}