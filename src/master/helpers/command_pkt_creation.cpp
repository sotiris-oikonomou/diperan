//
// Created by sotiris on 3/9/2018.
//

#include "command_pkt_creation.h"

namespace Diperan {
    void create_peer_config_command(std::vector <int32_t> papi_events = {},
                                    uint32_t benchmark_warmup = 0,
                                    uint32_t benchmark_buffer_size = 0,
                                    uint32_t incoming_queue_length = 0,
                                    uint32_t outgoing_queue_length = 0) {

        flatbuffers::FlatBufferBuilder builder(1024);

        auto papi_events_flatb_vec = builder.CreateVector(papi_events);

        OptionsBuilder peer_conf(builder);

        peer_conf.add_used_papi_event_codes(papi_events_flatb_vec);
        peer_conf.add_benchmark_warmup(benchmark_warmup);
        peer_conf.add_benchmark_buffer_size(benchmark_buffer_size);
        peer_conf.add_incoming_queue_length(incoming_queue_length);
        peer_conf.add_outgoing_queue_length(outgoing_queue_length);

        auto peer_conf_finished = peer_conf.Finish();
        builder.Finish(peer_conf_finished);

        uint8_t *byte_buffer = builder.GetBufferPointer();
        int byte_buffer_size = builder.GetSize();

        outgoing_packet_t temp;
        temp.command = Diperan::peer_configuration_command_pkt;
        temp.distribution_type = "SHOUT";
        temp.buffer.reserve(byte_buffer_size);
        temp.buffer.insert(temp.buffer.end(), byte_buffer, byte_buffer + byte_buffer_size);

        Diperan::g_outgoing_mutex.lock();
        Diperan::g_state.out_pkts.push(temp);
        if (Diperan::g_state.out_pkts.size() > Diperan::g_state.outgoing_queue_length) {
            Diperan::g_state.out_pkts.pop();
        }
        Diperan::g_outgoing_mutex.unlock();

    }
}