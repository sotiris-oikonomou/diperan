//
// Created by sotiris on 30/7/2018.
//

#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <vector>
#include <sys/utsname.h>
#include <string>
#include <cstdint>
#include <iostream>

#include "papi.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "hardware/system_info/caches/caches_info.h"

using namespace Diperan::System::Info;

namespace Diperan {
    int compile_system_info(std::vector <uint8_t> &output_buffer);
}
#endif //CLIENT_SYSTEM_INFO_H
