//
// Created by sotiris on 8/8/2018.
//

#ifndef PEER_DISCOVERY_H
#define PEER_DISCOVERY_H

#include <utility>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "hardware/system_info/caches/caches_info.h"
#include "processing/outgoing/master/peer_discovery_helpers.h"
#include "processing/outgoing/master/peer_pruning.h"
#include "packet_type_definitions.h"

namespace Diperan {
    void peer_discovery_loop();
    void get_complete_peer_info_loop();
}

#endif //CLIENT_PEER_INFO_UPDATER_H
