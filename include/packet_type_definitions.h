//
// Created by sotiris on 5/8/2018.
//

#ifndef PACKET_TYPE_DEFINITIONS_H
#define PACKET_TYPE_DEFINITIONS_H

#include <string>

namespace Diperan
{
namespace PacketTypes
{
enum Types {
    SYS_INFO_REPLY,
    SYS_INFO_CMD,
    PAPI_EVENTS_REPLY,
    PAPI_EVENTS_CMD,
    PAPI_BENCH_MMUL_DOUBLE_CMD,
    PAPI_BENCH_MMUL_DOUBLE_REPLY,
    PAPI_BENCH_MMUL_CMD,
    PAPI_BENCH_MMUL_REPLY,
};
}
const std::string sys_info_pkt = "SYS-INFO-REPLY";
const std::string sys_info_command_pkt = "SYS-INFO-CMD";
const std::string papi_supported_events_reply_pkt = "PAPI-EVENTS-REPLY";
const std::string papi_supported_events_command_pkt = "PAPI-EVENTS-CMD";
const std::string benchmark_warmup_command_pkt = "PAPI-BENCH-WARMUP-CMD";
const std::string benchmark_mmul_command_pkt = "PAPI-BENCH-MMUL-CMD";
const std::string benchmark_mmul_double_command_pkt = "PAPI-BENCH-MMUL-DOUBLE-CMD";
const std::string benchmark_crc32_command_pkt = "PAPI-CRC32-CMD";
const std::string benchmark_sha2_command_pkt = "PAPI-SHA2-CMD";
const std::string benchmark_results_reply_pkt = "PAPI-BENCH-RESULTS-REPLY";
const std::string peer_configuration_command_pkt = "PEER-CONFIGURATION-COMMAND";
}

#endif //CLIENT_COMMAND_TYPES_H
