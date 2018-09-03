//
// Created by sotiris on 16/8/2018.
//

#ifndef PACKET_CREATION_H
#define PACKET_CREATION_H

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "hardware/system_info/system_info.h"
#include "packet_type_definitions.h"

namespace Diperan {
    void create_shout_packet(std::string);
    void create_shout_packet(std::string, std::vector<uint8_t>);
    void create_whisper_packet(std::string, std::string);
    void create_whisper_packet(std::string, std::string, std::vector<uint8_t>);
}


#endif //PACKET_CREATION_H
