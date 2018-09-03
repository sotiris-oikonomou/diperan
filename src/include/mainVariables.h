//
//  Created by Sotiris Oikonomou.
//

#ifndef MAIN_VARIABLES_H
#define MAIN_VARIABLES_H

#include <execinfo.h>
#include <fcntl.h>
#include <signal.h>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>
#include <errno.h>
#include <cassert>
#include <exception>
#include <future>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <mutex>
#include <papi.h>
#include <zyre.h>

#include "hardware/find_supported_events.h"

//#include "Logger.h"

namespace Diperan {

    struct commandline_options_t {
        bool debugFull;

        commandline_options_t() {
            debugFull = false;
        }
    };

    struct other_node_t {
        std::string UUID;
        std::string name;
        std::vector<uint8_t> sys_info_buffer;
        std::vector<int32_t> papi_supported_events;
        other_node_t() {
            UUID = "";
            name = "";
        }
    };

    struct incoming_packet_t {
        std::string command;
        std::string UUID;
        std::string name;
        std::vector<uint8_t> buffer;
    };

    struct outgoing_packet_t {
        std::string command;
        std::string distribution_type;
        std::string target_UUID;
        std::vector<uint8_t> buffer;
    };

    struct node_state_t {
        bool is_master_node;
        std::string UUID;
        std::string name;
        zyre_t* node;
        zpoller_t* poller;
        std::string named_group;
        uint32_t benchmark_warmup;
        uint32_t benchmark_buffer_size;
        std::vector<int32_t> used_papi_events = {PAPI_L1_ICM, PAPI_L1_DCM, PAPI_L1_TCM, PAPI_TOT_INS};
        std::vector<int32_t> supported_papi_events;
        std::map <std::string, other_node_t> other_nodes;
        std::queue <incoming_packet_t> in_pkts;
        uint32_t incoming_queue_length = 1000;
        std::queue <outgoing_packet_t> out_pkts;
        uint32_t outgoing_queue_length = 1000;

        const uint32_t listening_loop_wait_time = 10;
        const uint32_t processing_incomings_loop_wait_time = 100;
        const uint32_t sending_loop_wait_time = 3;
        const uint32_t sending_loop_wait_time_modifier = 10;
        const uint32_t peer_update_loop_wait_time = 5000;

        node_state_t() {
            is_master_node = false;
            UUID = "";
            name = "";
            named_group = "";
            benchmark_warmup = 1;
            benchmark_buffer_size = 14000000;
            Diperan::get_papi_events(supported_papi_events);
        }

        ~node_state_t() {
            zyre_stop(node);
            zyre_destroy(&node);
            zpoller_destroy(&poller);
        }
    };

    extern std::mutex g_incoming_mutex;
    extern std::mutex g_outgoing_mutex;
    extern std::mutex g_peers_mutex;
    extern commandline_options_t g_cmdlnOptions;
    extern node_state_t g_state;

    inline void thread_wait_random_time(const int wait_time, const int wait_time_modifier) {
        if(wait_time <= 0 || wait_time_modifier <= 0) {
            return;
        }

        srand(time(NULL));
        int wait_random = rand() % wait_time_modifier + 1;
        zclock_sleep(wait_time + wait_random);
    }
}
#endif