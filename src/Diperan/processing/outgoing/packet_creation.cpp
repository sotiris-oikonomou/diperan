//
// Created by sotiris on 16/8/2018.
//

#include "packet_creation.h"

namespace Diperan {
    void create_shout_packet(std::string command) {
        Diperan::outgoing_packet_t temp_pkt;

        temp_pkt.command = command;
        temp_pkt.distribution_type = "SHOUT";

        Diperan::g_outgoing_mutex.lock();
        Diperan::g_state.out_pkts.push(temp_pkt);

        if (Diperan::g_state.out_pkts.size() > Diperan::g_state.outgoing_queue_length) {
            Diperan::g_state.out_pkts.pop();
        }
        Diperan::g_outgoing_mutex.unlock();
    }

    void create_shout_packet(std::string command, std::vector<uint8_t> buffer) {
        Diperan::outgoing_packet_t temp_pkt;

        temp_pkt.command = command;
        temp_pkt.distribution_type = "SHOUT";
        temp_pkt.buffer = buffer;

        Diperan::g_outgoing_mutex.lock();
        Diperan::g_state.out_pkts.push(temp_pkt);

        if (Diperan::g_state.out_pkts.size() > Diperan::g_state.outgoing_queue_length) {
            Diperan::g_state.out_pkts.pop();
        }
        Diperan::g_outgoing_mutex.unlock();
    }

    void create_whisper_packet(std::string command, std::string node_UUID) {
        Diperan::outgoing_packet_t temp_pkt;

        temp_pkt.command = command;
        temp_pkt.distribution_type = "WHISPER";
        temp_pkt.target_UUID = node_UUID;

        Diperan::g_outgoing_mutex.lock();
        Diperan::g_state.out_pkts.push(temp_pkt);

        if (Diperan::g_state.out_pkts.size() > Diperan::g_state.outgoing_queue_length) {
            Diperan::g_state.out_pkts.pop();
        }
        Diperan::g_outgoing_mutex.unlock();
    }

    void create_whisper_packet(std::string command, std::string node_UUID, std::vector<uint8_t> buffer) {
        Diperan::outgoing_packet_t temp_pkt;

        temp_pkt.command = command;
        temp_pkt.distribution_type = "WHISPER";
        temp_pkt.target_UUID = node_UUID;
        temp_pkt.buffer = buffer;

        Diperan::g_outgoing_mutex.lock();
        Diperan::g_state.out_pkts.push(temp_pkt);

        if (Diperan::g_state.out_pkts.size() > Diperan::g_state.outgoing_queue_length) {
            Diperan::g_state.out_pkts.pop();
        }
        Diperan::g_outgoing_mutex.unlock();
    }
}