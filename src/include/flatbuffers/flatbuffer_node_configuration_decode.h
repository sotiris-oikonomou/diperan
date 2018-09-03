//
// Created by sotiris on 23/8/2018.
//

#ifndef FLATBUFFER_NODE_CONFIGURATION_DECODE_H
#define FLATBUFFER_NODE_CONFIGURATION_DECODE_H

#include <memory>
#include <iostream>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/node_configuration_generated.h"

using namespace Diperan::Configuration;

namespace Diperan {
    inline void flatbuffer_node_configuration_decode(const std::vector<uint8_t>& buffer) {
        auto temp_verifier = flatbuffers::Verifier(reinterpret_cast<const uint8_t*>(buffer.data()), buffer.size());
        bool is_ok = VerifyOptionsBuffer(temp_verifier);

        if(is_ok) {
            auto options_flatb_obj = GetOptions(reinterpret_cast<const char*>(buffer.data()));

            if(options_flatb_obj->benchmark_warmup() > 0) {
                Diperan::g_state.benchmark_warmup = options_flatb_obj->benchmark_warmup();
            }

            if(options_flatb_obj->benchmark_buffer_size() > 0) {
                Diperan::g_state.benchmark_buffer_size = options_flatb_obj->benchmark_buffer_size();
            }

            if(options_flatb_obj->incoming_queue_length() > 0) {
                Diperan::g_state.incoming_queue_length = options_flatb_obj->incoming_queue_length();
            }

            if(options_flatb_obj->outgoing_queue_length() > 0) {
                Diperan::g_state.outgoing_queue_length = options_flatb_obj->outgoing_queue_length();
            }

            if(options_flatb_obj->used_papi_event_codes()->Length() > 0) {
                Diperan::g_state.used_papi_events.clear();
                Diperan::g_state.used_papi_events.resize(options_flatb_obj->used_papi_event_codes()->Length());

                for(uint i = 0; i < options_flatb_obj->used_papi_event_codes()->Length(); i++) {
                    Diperan::g_state.used_papi_events.at(i) = options_flatb_obj->used_papi_event_codes()->Get(i);
                }
            }
        }
        else {
            std::cerr<<"Peer Options flatbuffer verification Error"<<std::endl;
        }
    }
}
#endif //FLATBUFFER_NODE_CONFIGURATION_DECODE_H
