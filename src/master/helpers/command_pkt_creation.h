//
// Created by sotiris on 3/9/2018.
//

#ifndef DIPERAN_COMMAND_PKT_CREATION_H
#define DIPERAN_COMMAND_PKT_CREATION_H

#include <vector>
#include <string>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/node_configuration_generated.h"
#include "processing/outgoing/packet_creation.h"
#include "packet_type_definitions.h"

using namespace Diperan::Configuration;

namespace Diperan {
    void create_peer_config_command(std::vector <int32_t>, uint32_t, uint32_t, uint32_t, uint32_t);
}

#endif //DIPERAN_COMMAND_PKT_CREATION_H
