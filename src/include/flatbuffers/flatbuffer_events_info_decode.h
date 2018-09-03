//
// Created by sotiris on 23/8/2018.
//

#ifndef FLATBUFFER_EVENTS_INFO_DECODE_H
#define FLATBUFFER_EVENTS_INFO_DECODE_H

#include <memory>
#include <iostream>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/event_info_generated.h"
#include "optional.h"

using namespace Diperan::Event::Info;

namespace Diperan {
    inline std::experimental::optional<const Events*> flatbuffer_events_info_decode(const std::vector<uint8_t>& buffer) {
        auto temp_verifier = flatbuffers::Verifier(reinterpret_cast<const uint8_t*>(buffer.data()), buffer.size());
        bool is_ok = VerifyEventsBuffer(temp_verifier);

        if(is_ok) {
            auto events_obj = GetEvents(reinterpret_cast<const char*>(buffer.data()));
            return events_obj;
        }
        else {
            std::cerr<<"Events flatbuffer verification Error"<<std::endl;
            return {};
        }
    }

    inline void flatbuffer_events_info_print(const Events* flatbuffer_obj) {
        if(flatbuffer_obj == nullptr) {
            return;
        }
        auto papi_supported_events = flatbuffer_obj->event_codes();
        std::cout<<"Supported events"<<std::endl;
        for(uint32_t i = 0; i < papi_supported_events->Length(); i++) {
            std::cout<<papi_supported_events->Get(i)<<std::endl;
        }
    }
}
#endif //CLIENT_FLATBUFFER_EVENTS_INFO_DECODE_H
