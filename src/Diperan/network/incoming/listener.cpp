//
// Created by sotiris on 20/7/2018.
//
#include "listener.h"

namespace Diperan {

    void packet_listening_loop() {
        while (!zsys_interrupted) {
            void *which = zpoller_wait(Diperan::g_state.poller, -1);
            if (which == zyre_socket(Diperan::g_state.node)) {

                zmsg_t *msg = zyre_recv(reinterpret_cast<zyre_t *>(which));

                if (!msg) {
                    Diperan::thread_wait_random_time(g_state.listening_loop_wait_time, 1);
                    continue;
                }

                char *zre_msg_type;
                char *zre_node_name;
                char *zre_node_UUID;
                char *zre_group;
                char *diperan_packet_type;

                zre_msg_type = zmsg_popstr(msg);
                zre_node_UUID = zmsg_popstr(msg);
                zre_node_name = zmsg_popstr(msg);
                if (strcmp(zre_msg_type, "SHOUT") == 0) {
                    zre_group = zmsg_popstr(msg);
                }
                diperan_packet_type = zmsg_popstr(msg);

                if (strcmp(zre_msg_type, "SHOUT") == 0 || strcmp(zre_msg_type, "WHISPER") == 0) {
                    if (Diperan::g_state.is_master_node) {
                        //Processing input packets on master mode
                        if (strcmp(diperan_packet_type, Diperan::sys_info_pkt.c_str()) == 0 ||
                            strcmp(diperan_packet_type, Diperan::papi_supported_events_reply_pkt.c_str()) == 0 ||
                            strcmp(diperan_packet_type, Diperan::benchmark_results_reply_pkt.c_str()) == 0) {

                            Diperan::incoming_packet_t temp_pkt;
                            temp_pkt.command = std::string(diperan_packet_type);
                            temp_pkt.UUID = std::string(zre_node_UUID);
                            temp_pkt.name = std::string(zre_node_name);
                            zframe_t *zframe_tmp = zmsg_pop(msg);
                            if (zframe_tmp) {
                                int temp_buffer_size = zframe_size(zframe_tmp);
                                temp_pkt.buffer.insert(temp_pkt.buffer.end(),
                                                       reinterpret_cast<uint8_t *>(zframe_data(zframe_tmp)),
                                                       reinterpret_cast<uint8_t *>(zframe_data(zframe_tmp)) +
                                                       temp_buffer_size);
                            }
                            zframe_destroy(&zframe_tmp);

                            Diperan::g_incoming_mutex.lock();
                            Diperan::g_state.in_pkts.push(temp_pkt);
                            if (Diperan::g_state.in_pkts.size() > Diperan::g_state.incoming_queue_length) {
                                Diperan::g_state.in_pkts.pop();
                            }
                            Diperan::g_incoming_mutex.unlock();
                        }
                    } else {
                        //Processing input packets on normal node mode
                        if (strcmp(diperan_packet_type, Diperan::sys_info_command_pkt.c_str()) == 0 ||
                            strcmp(diperan_packet_type, Diperan::papi_supported_events_command_pkt.c_str()) == 0 ||
                            strcmp(diperan_packet_type, Diperan::benchmark_mmul_command_pkt.c_str()) == 0 ||
                            strcmp(diperan_packet_type, Diperan::benchmark_mmul_double_command_pkt.c_str()) == 0 ||
                            strcmp(diperan_packet_type, Diperan::benchmark_crc32_command_pkt.c_str()) == 0 ||
                            strcmp(diperan_packet_type, Diperan::benchmark_sha2_command_pkt.c_str()) == 0 ||
                            strcmp(diperan_packet_type, Diperan::peer_configuration_command_pkt.c_str()) == 0) {

                            Diperan::incoming_packet_t temp_pkt;
                            temp_pkt.command = std::string(diperan_packet_type);
                            temp_pkt.UUID = std::string(zre_node_UUID);
                            temp_pkt.name = std::string(zre_node_name);
                            zframe_t *zframe_tmp = zmsg_pop(msg);
                            if (zframe_tmp) {
                                int temp_buffer_size = zframe_size(zframe_tmp);
                                temp_pkt.buffer.insert(temp_pkt.buffer.end(),
                                                       reinterpret_cast<uint8_t *>(zframe_data(zframe_tmp)),
                                                       reinterpret_cast<uint8_t *>(zframe_data(zframe_tmp)) +
                                                       temp_buffer_size);
                            }
                            zframe_destroy(&zframe_tmp);

                            Diperan::g_incoming_mutex.lock();
                            Diperan::g_state.in_pkts.push(temp_pkt);
                            if (Diperan::g_state.in_pkts.size() > Diperan::g_state.incoming_queue_length) {
                                Diperan::g_state.in_pkts.pop();
                            }
                            Diperan::g_incoming_mutex.unlock();
                        }
                    }
                }

                zstr_free(&diperan_packet_type);
                zstr_free(&zre_msg_type);
                zstr_free(&zre_node_name);
                zstr_free(&zre_node_UUID);
                if(zre_group) {
                    zstr_free(&zre_group);
                }
                zmsg_destroy(&msg);

                Diperan::thread_wait_random_time(g_state.listening_loop_wait_time, 1);
            }
        }
    }



}