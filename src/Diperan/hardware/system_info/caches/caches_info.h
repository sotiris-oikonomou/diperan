//
// Created by sotiris on 7/8/2018.
//

#ifndef CACHES_INFO_H
#define CACHES_INFO_H

#include <vector>
#include <sys/utsname.h>
#include <string>
#include <cstdint>
#include <iostream>

#include "papi.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"

using namespace Diperan::System::Info;

namespace Diperan {
    int compile_tlb_caches_info(std::vector <flatbuffers::Offset<CpuTlb>> &,
                                flatbuffers::FlatBufferBuilder &);

    int compile_caches_info(std::vector <flatbuffers::Offset<CpuCache>> &,
                            flatbuffers::FlatBufferBuilder &);
}

#endif //CLIENT_CACHES_INFO_H
