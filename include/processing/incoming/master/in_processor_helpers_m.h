//
// Created by sotiris on 13/8/2018.
//

#ifndef IN_PROCESSOR_HELPERS_M_H
#define IN_PROCESSOR_HELPERS_M_H

#include <algorithm>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "flatbuffers/event_info_generated.h"
#include "hardware/system_info/system_info.h"
#include "packet_type_definitions.h"

namespace Diperan {
    void save_peer_node(incoming_packet_t node);
    void save_node_papi_supported_events(std::string UUID, const std::vector<int32_t>& events);
}

#endif //CLIENT_PROCESSOR_HELPERS_H
