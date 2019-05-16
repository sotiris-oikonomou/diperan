//
// Created by sotiris on 8/8/2018.
//

#include "peer_discovery.h"

namespace Diperan {
    void peer_discovery_loop() {
        while (!zsys_interrupted) {
            zlist_t *peers = zyre_peers(Diperan::g_state.node);

            char *temp_node_UUID;
            std::string temp_UUID_str;

            void* temp_node_voidptr_UUID = zlist_first(peers);
            temp_node_UUID = static_cast<char *>(temp_node_voidptr_UUID);

            if(temp_node_voidptr_UUID) {
                temp_UUID_str = temp_node_UUID;
                Diperan::add_node_as_peer(temp_UUID_str);
            }

            temp_node_voidptr_UUID = zlist_next(peers);
            while(temp_node_voidptr_UUID) {
                temp_node_UUID = static_cast<char *>(temp_node_voidptr_UUID);
                temp_UUID_str = temp_node_UUID;
                Diperan::add_node_as_peer(temp_UUID_str);

                temp_node_voidptr_UUID = zlist_next(peers);
            }
            Diperan::peer_pruning();
            if(peers) {
                zlist_destroy(&peers);
            }
            Diperan::thread_wait_random_time(Diperan::g_state.peer_update_loop_wait_time, 1);
        }
    }

    void get_complete_peer_info_loop() {
        while (!zsys_interrupted) {
            Diperan::g_peers_mutex.lock();
            for (auto node_temp : Diperan::g_state.other_nodes) {
                if(node_temp.second.sys_info_buffer.size() == 0) {
                    Diperan::create_whisper_packet(Diperan::sys_info_command_pkt, node_temp.second.UUID);
                }
                if(node_temp.second.papi_supported_events.size() == 0) {
                    Diperan::create_whisper_packet(Diperan::papi_supported_events_command_pkt, node_temp.second.UUID);
                }
                Diperan::thread_wait_random_time(5, 1);
            }
            Diperan::g_peers_mutex.unlock();
            Diperan::thread_wait_random_time(Diperan::g_state.peer_update_loop_wait_time, 1);
        }
    }
}