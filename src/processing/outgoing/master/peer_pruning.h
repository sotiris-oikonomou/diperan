//
// Created by sotiris on 27/8/2018.
//

#ifndef PEER_PRUNING_H
#define PEER_PRUNING_H

#include <string>
#include <zyre.h>

#include "mainVariables.h"

namespace Diperan {
    void peer_pruning();
    bool is_peer_node_in_zlist(std::string UUID);
}

#endif //PEER_PRUNING_H
