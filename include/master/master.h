//
// Created by sotiris on 18/8/2018.
//

#ifndef MASTER_H
#define MASTER_H

#include <papi.h>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "flatbuffers/node_configuration_generated.h"
#include "hardware/system_info/caches/caches_info.h"
#include "flatbuffers/flatbuffer_sys_info_decode.h"
#include "flatbuffers/flatbuffer_events_info_decode.h"
#include "processing/outgoing/packet_creation.h"
#include "packet_type_definitions.h"
#include "master/helpers/command_pkt_creation.h"
#include "master/ui/linenoise.hpp"
#include "master/ui/rang.hpp"

namespace Diperan {
    void master_run();
}

#endif //MASTER_H
