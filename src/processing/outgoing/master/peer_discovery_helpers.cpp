//
// Created by sotiris on 16/8/2018.
//

#include "peer_discovery_helpers.h"

namespace Diperan {
    void add_node_as_peer(std::string node_UUID) {
        Diperan::other_node_t temp_node;
        temp_node.UUID = node_UUID;
        Diperan::g_peers_mutex.lock();
        auto key_search = Diperan::g_state.other_nodes.find(node_UUID);
        if(key_search == Diperan::g_state.other_nodes.end()) {
            Diperan::g_state.other_nodes[temp_node.UUID] = temp_node;
        }
        Diperan::g_peers_mutex.unlock();
    }
}