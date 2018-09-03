//
// Created by sotiris on 9/8/2018.
//

#ifndef IN_PROCESSOR_H
#define IN_PROCESSOR_H

#include <string>
#include <cstdint>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "flatbuffers/event_info_generated.h"
#include "flatbuffers/flatbuffer_events_info_decode.h"
#include "flatbuffers/flatbuffer_benchmark_results_decode.h"
#include "flatbuffers/flatbuffer_node_configuration_decode.h"
#include "hardware/system_info/caches/caches_info.h"
#include "processing/incoming/master/in_processor_helpers_m.h"
#include "processing/incoming/node/in_processor_helpers_n.h"
#include "benchmarking/run_benchmark.h"

using namespace Diperan::System::Info;

namespace Diperan {
    void incoming_packet_processing_loop();
}

#endif //CLIENT_IN_PROCESSOR_H
