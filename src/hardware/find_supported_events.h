//
// Created by sotiris on 29/7/2018.
//

#ifndef FIND_SUPPORTED_EVENTS_H
#define FIND_SUPPORTED_EVENTS_H

#include <cstring>
#include <papi.h>
#include <stdio.h>
#include <vector>
#include <iostream>

namespace Diperan {
    bool is_derived(PAPI_event_info_t*);
    int checkCounter(int);
    int get_papi_events(std::vector<int32_t>&);
}

#endif //CLIENT_FIND_SUPPORTED_EVENTS_H
