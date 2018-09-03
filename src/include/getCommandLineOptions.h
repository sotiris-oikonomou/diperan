//
//  Created by Sotiris Oikonomou.
//

#ifndef GET_COMMANDLINE_OPTIONS_H
#define GET_COMMANDLINE_OPTIONS_H

#include <unistd.h>

namespace Diperan {
    int getCommandLineOptions(int argc, char *argv[]) {
        int c;

        while ((c = getopt(argc, argv, "DM")) != -1) {
            switch (c) {
                case 'D':
                    g_cmdlnOptions.debugFull = true;
                    break;
                case 'M':
                    Diperan::g_state.is_master_node = true;
                    break;
                default:
                    //No commandline options
                    break;
            }
        }
        return 0;
    }
}
#endif