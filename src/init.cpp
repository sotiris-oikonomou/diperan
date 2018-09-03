#include "init.h"

namespace Diperan {

    commandline_options_t g_cmdlnOptions;
    node_state_t g_state;
    std::mutex g_incoming_mutex;
    std::mutex g_outgoing_mutex;
    std::mutex g_peers_mutex;

    void init() {
        Diperan::g_state.is_master_node = false;
        Diperan::g_state.named_group = "DIPERAN";
        Diperan::g_state.node = zyre_new(0);
        if (!Diperan::g_state.node) {
            //TODO: Log
            std::exit(EXIT_FAILURE);
        }
        Diperan::g_state.name = zyre_name(Diperan::g_state.node);
        Diperan::g_state.UUID = zyre_uuid(Diperan::g_state.node);

        zyre_start(Diperan::g_state.node);
        zyre_join(Diperan::g_state.node, Diperan::g_state.named_group.c_str());
        zsock_signal(zyre_socket(Diperan::g_state.node), 0);
        Diperan::g_state.poller = zpoller_new(zyre_socket(Diperan::g_state.node), NULL);
    }
}