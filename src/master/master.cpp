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
            auto quit = linenoise::Readline(prompt.c_str(), line);

            if (quit) {
                break;
            }

            std::cout <<  "echo: '" << line << "'" << std::endl;

            // Add text to history
            linenoise::AddHistory(line.c_str());
            /*
            if(input == 'X') {
                zyre_stop(Diperan::g_state.node);
                zyre_destroy(&Diperan::g_state.node);
                zpoller_destroy(&Diperan::g_state.poller);
                PAPI_shutdown();
                exit(EXIT_SUCCESS);
            }
            else if(input == 'L') {
                std::cout<<"Recognised peer UUIDs"<<std::endl;
                for (auto &&node_temp : Diperan::g_state.other_nodes) {
                    if(node_temp.second.name.size() != 0) {
                        std::cout << "  UUID: " << node_temp.second.UUID << std::endl;
                    }
                    Diperan::thread_wait_random_time(5, 1);
                }
            }
            else if(input == 'I') {
                std::cout<<"UUID: ";
                std::string temp_uuid;
                std::cin>>temp_uuid;
                auto temp_node = Diperan::g_state.other_nodes.find(temp_uuid);
                if(temp_node != Diperan::g_state.other_nodes.end()) {
                    auto flatbuffer_sys_info_decoded = Diperan::flatbuffer_sys_info_decode(temp_node->second.sys_info_buffer);
                    flatbuffer_sys_info_print(flatbuffer_sys_info_decoded.value_or(nullptr));
                    std::cout<<"  Supported events"<<std::endl;
                    int retval = PAPI_library_init(PAPI_VER_CURRENT);
                    if (retval != PAPI_VER_CURRENT) {
                        std::cerr<<"PAPI library init error!"<<std::endl;
                    }
                    PAPI_event_info_t info;
                    for(auto event_code: temp_node->second.papi_supported_events) {
                        if (PAPI_get_event_info(event_code, &info) == PAPI_OK) {
                            std::cout<<"    Symbol: "<<info.symbol<<", Description: "<<info.long_descr<<std::endl;
                        }
                        else {
                            std::cout << event_code << std::endl;
                        }
                    }
                }
            }
            else if(input == 'W') {
                std::cout<<"Warmup# ";
                std::cin>>input;
            }
            else if(input == 'm') {
                Diperan::create_shout_packet(Diperan::benchmark_mmul_command_pkt);
            }
            else if(input == 'M') {
                Diperan::create_shout_packet(Diperan::benchmark_mmul_double_command_pkt);
            }
            else if(input == 'C') {
                Diperan::create_shout_packet(Diperan::benchmark_crc32_command_pkt);
            }
            else if(input == 'S') {
                Diperan::create_shout_packet(Diperan::benchmark_sha2_command_pkt);
            }*/
        }
    }

}