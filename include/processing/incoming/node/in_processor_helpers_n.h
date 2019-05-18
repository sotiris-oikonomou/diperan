//
// Created by sotiris on 13/8/2018.
//

#ifndef IN_PROCESSOR_HELPERS_N_H
#define IN_PROCESSOR_HELPERS_N_H

#include <algorithm>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "flatbuffers/event_info_generated.h"
#include "hardware/system_info/system_info.h"
#include "packet_type_definitions.h"

using namespace Diperan::Event::Info;

namespace Diperan {
    void prepare_sys_info_packet();
    void prepare_supported_papi_events_pkt();
}

#endif //CLIENT_PROCESSOR_HELPERS_H
