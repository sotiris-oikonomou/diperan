//
// Created by sotiris on 13/8/2018.
//

#include "processing/incoming/node/in_processor_helpers_n.h"

namespace Diperan {
    void prepare_sys_info_packet() {
        Diperan::outgoing_packet_t temp_pkt;
        Diperan::compile_system_info(temp_pkt.buffer);
        temp_pkt.command = Diperan::sys_info_pkt;
        temp_pkt.distribution_type = "SHOUT";

        Diperan::g_outgoing_mutex.lock();
        Diperan::g_state.out_pkts.push(temp_pkt);
        if (Diperan::g_state.out_pkts.size() > Diperan::g_state.outgoing_queue_length) {
            Diperan::g_state.out_pkts.pop();
        }
        Diperan::g_outgoing_mutex.unlock();
    }

    void prepare_supported_papi_events_pkt() {
        Diperan::outgoing_packet_t temp_pkt;

        flatbuffers::FlatBufferBuilder builder(1024);
        auto flatb_vector_temp = builder.CreateVector(Diperan::g_state.supported_papi_events);
        EventsBuilder supported_papi_events_builder(builder);
        supported_papi_events_builder.add_event_codes(flatb_vector_temp);
        auto flatb_papi_events = supported_papi_events_builder.Finish();
        builder.Finish(flatb_papi_events);
        uint8_t* buffer = builder.GetBufferPointer();
        int buffer_size = builder.GetSize();

        temp_pkt.buffer.insert(temp_pkt.buffer.end(),
                               buffer,
                               buffer + buffer_size);
        temp_pkt.command = Diperan::papi_supported_events_reply_pkt;
        temp_pkt.distribution_type = "SHOUT";

        Diperan::g_outgoing_mutex.lock();
        Diperan::g_state.out_pkts.push(temp_pkt);
        if (Diperan::g_state.out_pkts.size() > Diperan::g_state.outgoing_queue_length) {
            Diperan::g_state.out_pkts.pop();
        }
        Diperan::g_outgoing_mutex.unlock();
    }
}