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

    void peer_pruning() {
        Diperan::g_peers_mutex.lock();
        for(auto peer_node : Diperan::g_state.other_nodes) {
            if(!is_peer_node_in_zlist(peer_node.first)) {
                Diperan::g_state.other_nodes.erase(peer_node.first);
            }
        }
        Diperan::g_peers_mutex.unlock();
    }

    bool is_peer_node_in_zlist(std::string UUID) {
        zlist_t *peers = zyre_peers(Diperan::g_state.node);
        void* temp_UUID = zlist_first(peers);
        if(strcmp(static_cast<char *>(temp_UUID), UUID.c_str()) == 0) {
            return true;
        }
        else if(!temp_UUID) {
            return false;
        }

        temp_UUID = zlist_next(peers);
        while(temp_UUID) {
            if(strcmp(static_cast<char *>(temp_UUID), UUID.c_str()) == 0) {
                return true;
            }
            temp_UUID = zlist_next(peers);
        }
        //zstr_free(static_cast<char *>(temp_UUID));
        return false;
    }
}