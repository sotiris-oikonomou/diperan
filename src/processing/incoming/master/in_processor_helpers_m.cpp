//
// Created by sotiris on 13/8/2018.
//

#include "in_processor_helpers_m.h"

namespace Diperan {
    void save_peer_node(incoming_packet_t pkt) {
        if (Diperan::g_state.other_nodes.find(pkt.UUID) == Diperan::g_state.other_nodes.end()) {
            std::cerr<<"There is no existing node registered with this UUID"<<std::endl;
            return;
        } else {
            auto node_in_map = Diperan::g_state.other_nodes.find(pkt.UUID);
            node_in_map->second.name = pkt.name;
            node_in_map->second.UUID = pkt.UUID;
            node_in_map->second.sys_info_buffer = pkt.buffer;
        }
    }

    void save_node_papi_supported_events(std::string UUID, const std::vector <int32_t> &events) {
        if (Diperan::g_state.other_nodes.find(UUID) == Diperan::g_state.other_nodes.end()) {
            std::cerr<<"There is no existing node registered with this UUID"<<std::endl;
            return;
        } else {
            auto node_in_map = Diperan::g_state.other_nodes.find(UUID);
            node_in_map->second.papi_supported_events = events;
        }
    }
}