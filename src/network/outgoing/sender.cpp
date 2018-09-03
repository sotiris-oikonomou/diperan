//
// Created by sotiris on 1/8/2018.
//
#include "sender.h"

namespace Diperan {

    void packet_sending_loop() {

        while (!zsys_interrupted) {
            if(Diperan::g_state.out_pkts.size() > 0) {

                Diperan::g_outgoing_mutex.lock();
                auto temp_pkt = Diperan::g_state.out_pkts.front();
                Diperan::g_state.out_pkts.pop();
                Diperan::g_outgoing_mutex.unlock();

                zmsg_t *temp_msg = zmsg_new();
                zmsg_addstr(temp_msg, temp_pkt.command.c_str());
                if(temp_pkt.buffer.size() > 0) {
                    zmsg_addmem(temp_msg, reinterpret_cast<void*>(temp_pkt.buffer.data()), temp_pkt.buffer.size());
                }

                if(strcmp(temp_pkt.distribution_type.c_str(), "SHOUT") == 0) {
                    zyre_shout(Diperan::g_state.node, g_state.named_group.c_str(), &temp_msg);
                }

                if(strcmp(temp_pkt.distribution_type.c_str(), "WHISPER") == 0) {
                    zyre_whisper(Diperan::g_state.node, temp_pkt.target_UUID.c_str(), &temp_msg);
                }
                zmsg_destroy(&temp_msg);
            }

            Diperan::thread_wait_random_time(Diperan::g_state.sending_loop_wait_time, Diperan::g_state.sending_loop_wait_time_modifier);
        }
    }

}

