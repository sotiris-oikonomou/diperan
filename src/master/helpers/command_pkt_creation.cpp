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

        std::vector<int32_t> papi_events_temp = {PAPI_L1_ICM, PAPI_L1_DCM, PAPI_TOT_INS};

        auto papi_events_flatb_vec = builder.CreateVector(papi_events_temp);

        OptionsBuilder peer_conf(builder);
        peer_conf.add_used_papi_event_codes(papi_events_flatb_vec);
        peer_conf.add_benchmark_warmup(benchmark_warmup);
        peer_conf.add_benchmark_buffer_size(benchmark_buffer_size);

        auto peer_conf_finished = peer_conf.Finish();
        builder.Finish(peer_conf_finished);

        uint8_t *buffer = builder.GetBufferPointer();
        int buffer_size = builder.GetSize();

        outgoing_packet_t temp;
        temp.command = Diperan::peer_configuration_command_pkt;
        temp.distribution_type = "SHOUT";
        temp.buffer.insert(temp.buffer.end(), buffer, buffer + buffer_size);

        Diperan::g_outgoing_mutex.lock();
        Diperan::g_state.out_pkts.push(temp);
        if (Diperan::g_state.out_pkts.size() > Diperan::g_state.outgoing_queue_length) {
            Diperan::g_state.out_pkts.pop();
        }
        Diperan::g_outgoing_mutex.unlock();

    }
}