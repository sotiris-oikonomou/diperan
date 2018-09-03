//
// Created by sotiris on 27/8/2018.
//

#include "peer_pruning.h"

namespace Diperan {
    void peer_pruning() {
        for(auto peer_node : Diperan::g_state.other_nodes) {
            if(!is_peer_node_in_zlist(peer_node.first)) {
                Diperan::g_state.other_nodes.erase(peer_node.first);
            }
        }
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