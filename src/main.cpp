//
//  Created by Sotiris Oikonomou.
//

#include "init.h"
#include "mainVariables.h"
#include "getCommandLineOptions.h"
#include "daemon.h"
#include "network/outgoing/sender.h"
#include "network/incoming/listener.h"
#include "processing/outgoing/master/peer_discovery_helpers.h"
#include "processing/outgoing/master/peer_discovery.h"
#include "processing/incoming/in_processor.h"
#include "hardware/find_supported_events.h"
#include "benchmarking/run_benchmark.h"
#include "master/master.h"


int main(int argc, char *argv[])
{
    Diperan::init();
    Diperan::getCommandLineOptions(argc, argv);

    if (!Diperan::g_state.is_master_node) {
        setlogmask(LOG_UPTO(LOG_INFO));
        openlog(DAEMON_NAME, LOG_CONS | LOG_PERROR, LOG_USER);

        syslog(LOG_INFO, "starting up");

        /* Deamonize */
        Diperan::daemonize();

        syslog(LOG_INFO, "running");
    }

    std::thread diperan_sending(Diperan::packet_sending_loop);
    std::thread diperan_listening(Diperan::packet_listening_loop);
    std::thread diperan_sys_info(Diperan::incoming_packet_processing_loop);


    if (Diperan::g_state.is_master_node) {
        std::thread diperan_peer_discovery(Diperan::peer_discovery_loop);
        std::thread diperan_peer_updater(Diperan::get_complete_peer_info_loop);
        std::thread master(Diperan::master_run);

        diperan_peer_discovery.join();
        diperan_peer_updater.join();
        master.join();
    }

    diperan_sending.join();
    diperan_listening.join();
    diperan_sys_info.join();

    return EXIT_SUCCESS;
}
