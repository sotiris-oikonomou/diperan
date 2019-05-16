//
// Created by sotiris on 20/7/2018.
//

#ifndef LISTENER_H
#define LISTENER_H
#include <zyre.h>
#include <string>
#include <cstdint>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "hardware/system_info/caches/caches_info.h"
#include "packet_type_definitions.h"

using namespace Diperan::System::Info;

namespace Diperan {
    void packet_listening_loop();
}

#endif //CLIENT_ZYRE_LISTENER_H

