//
//  daemon.h
//  Daemonize for a systemd system
//
//  Created by Sotiris Oikonomou.
//

#ifndef DAEMON_H
#define DAEMON_H

#define DAEMON_NAME "diperan"

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>
#include <zyre.h>
#include <papi.h>
#include "mainVariables.h"

namespace Diperan
{
void daemonShutdown();

void signal_handler(int sig);

void daemonize();

void signal_handler(int sig)
{
    switch (sig) {
        case SIGHUP:

            break;

        case SIGINT:
        case SIGTERM:
            daemonShutdown();
            exit(EXIT_SUCCESS);
            break;
        default:

            break;
    }
}

void daemonShutdown()
{
    zyre_stop(Diperan::g_state.node);
    zyre_destroy(&Diperan::g_state.node);
    zpoller_destroy(&Diperan::g_state.poller);
    PAPI_shutdown();
}

void daemonize()
{
    struct sigaction newSigAction;
    sigset_t newSigSet;

    /* Set signal mask - signals we want to block */
    sigemptyset(&newSigSet);
    sigaddset(&newSigSet,
              SIGCHLD); /* ignore child - i.e. we don't need to wait for it */
    sigaddset(&newSigSet, SIGTSTP); /* ignore Tty stop signals */
    sigaddset(&newSigSet, SIGTTOU); /* ignore Tty background writes */
    sigaddset(&newSigSet, SIGTTIN); /* ignore Tty background reads */
    sigprocmask(SIG_BLOCK, &newSigSet,
                NULL); /* Block the above specified signals */

    /* Set up a signal handler */
    newSigAction.sa_handler = signal_handler;
    sigemptyset(&newSigAction.sa_mask);
    newSigAction.sa_flags = 0;

    /* Signals to handle */
    sigaction(SIGHUP, &newSigAction, NULL);  /* catch hangup signal */
    sigaction(SIGTERM, &newSigAction, NULL); /* catch term signal */
    sigaction(SIGINT, &newSigAction, NULL);  /* catch interrupt signal */
}
}
#endif //DAEMON_H
