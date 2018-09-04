//
// Created by sotiris on 18/8/2018.
//

#include "master.h"

namespace Diperan {
    void master_run() {
        linenoise::SetMultiLine(true);
        linenoise::SetHistoryMaxLen(4);
        std::string prompt = "Command# ";
        while (!zsys_interrupted) {
            std::string line;
            linenoise::Readline(prompt.c_str(), line);

            if (line.compare("exit") == 0) {
                zyre_stop(Diperan::g_state.node);
                zyre_destroy(&Diperan::g_state.node);
                zpoller_destroy(&Diperan::g_state.poller);
                PAPI_shutdown();
                exit(EXIT_SUCCESS);
            } else if (line.compare("list peers") == 0) {
                if(Diperan::g_state.other_nodes.size() > 0) {
                    std::cout << "Recognised peer UUIDs" << std::endl;
                    for (auto &&node_temp : Diperan::g_state.other_nodes) {
                        if (node_temp.second.name.size() != 0) {
                            std::cout << "  UUID: " << node_temp.second.UUID << std::endl;
                        }
                        Diperan::thread_wait_random_time(5, 1);
                    }
                }
                else {
                    std::cout << "No Recognised peers" << std::endl;
                }
            } else if (line.compare("peer info") == 0) {
                linenoise::Readline("UUID# ", line);
                auto temp_node = Diperan::g_state.other_nodes.find(line);
                if (temp_node != Diperan::g_state.other_nodes.end()) {
                    auto flatbuffer_sys_info_decoded = Diperan::flatbuffer_sys_info_decode(
                            temp_node->second.sys_info_buffer);
                    flatbuffer_sys_info_print(flatbuffer_sys_info_decoded.value_or(nullptr));
                    std::cout << "  Supported events" << std::endl;
                    int retval = PAPI_library_init(PAPI_VER_CURRENT);
                    if (retval != PAPI_VER_CURRENT) {
                        std::cerr << "PAPI library init error!" << std::endl;
                    }
                    PAPI_event_info_t info;
                    for (auto event_code: temp_node->second.papi_supported_events) {
                        if (PAPI_get_event_info(event_code, &info) == PAPI_OK) {
                            std::cout << "    Symbol: " << info.symbol << ", Description: " << info.long_descr
                                      << std::endl;
                        } else {
                            std::cout << event_code << std::endl;
                        }
                    }
                }
            } else if (line.compare("peer config") == 0) {
                linenoise::Readline("Bench Warmup# ", line);
                uint32_t warmup_turns = std::stoi(line);
                linenoise::Readline("Bench Buffer# ", line);
                uint32_t buffer_size = std::stoi(line);
                Diperan::create_peer_config_command(std::vector <int32_t>(), warmup_turns, buffer_size, 0, 0);
            } else if (line.compare("bench mmul float") == 0) {
                Diperan::create_shout_packet(Diperan::benchmark_mmul_command_pkt);
            } else if (line.compare("bench mmul double") == 0) {
                Diperan::create_shout_packet(Diperan::benchmark_mmul_double_command_pkt);
            } else if (line.compare("bench crc32") == 0) {
                Diperan::create_shout_packet(Diperan::benchmark_crc32_command_pkt);
            } else if (line.compare("bench sha2") == 0) {
                Diperan::create_shout_packet(Diperan::benchmark_sha2_command_pkt);
            }
            linenoise::AddHistory(line.c_str());
        }
    }

}