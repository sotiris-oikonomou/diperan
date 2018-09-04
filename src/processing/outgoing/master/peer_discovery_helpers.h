//
// Created by sotiris on 16/8/2018.
//

#ifndef PEER_DISCOVERY_HELPERS_H
#define PEER_DISCOVERY_HELPERS_H

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "hardware/system_info/system_info.h"
#include "processing/outgoing/packet_creation.h"
#include "packet_type_definitions.h"


namespace Diperan {
    void add_node_as_peer(std::string);
    void peer_pruning();
    bool is_peer_node_in_zlist(std::string);
}
#endif //PEER_DISCOVERY_HELPERS_H
