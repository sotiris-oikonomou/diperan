//
// Created by sotiris on 20/7/2018.
//

#include "find_supported_events.h"

namespace Diperan {

    bool is_derived(PAPI_event_info_t *info) {
        if (strlen(info->derived) == 0)
            return false;
        else if(strcmp(info->derived, "NOT_DERIVED") == 0)
            return false;
        else if(strcmp(info->derived, "DERIVED_CMPD") == 0)
            return false;
        else
            return true;
    }

    int checkCounter(int eventcode) {
        int EventSet = PAPI_NULL;
        if(PAPI_create_eventset(&EventSet) != PAPI_OK)
            return 0;
        if(PAPI_add_event(EventSet, eventcode) != PAPI_OK)
            return 0;
        if(PAPI_cleanup_eventset(EventSet) != PAPI_OK)
            return 0;
        if(PAPI_destroy_eventset(&EventSet) != PAPI_OK)
            return 0;
        return 1;
    }

    int get_papi_events(std::vector<int32_t>& event_codes) {
        int retval;
        int check_avail_only = PAPI_ENUM_EVENTS;
        PAPI_event_info_t info;
        int check_counter = 0;
        int event_code;

        retval = PAPI_library_init(PAPI_VER_CURRENT);
        if(retval != PAPI_VER_CURRENT) {
            std::cerr<<"Error!  PAPI library mismatch!"<<std::endl;
            return 1;
        }

        retval = PAPI_set_debug(PAPI_VERB_ECONT);
        if(retval != PAPI_OK) {
            std::cerr<<"Error with PAPI_set debug!"<<std::endl;
            return 1;
        }

        if(retval != PAPI_OK) {
            std::cerr<<"Error with PAPI_get_hardware_info!"<<std::endl;
            return 1;
        }

        for(int i = 0; i < 2; i++) {
            // set the event code to fetch preset events the first time through loop and user events the second time through the loop
            if(i == 0) {
                event_code = 0 | PAPI_PRESET_MASK;
            } else {
                event_code = 0 | PAPI_UE_MASK;
            }

            /* For consistency, always ASK FOR the first event, if there is not one then nothing to process */
            if(PAPI_enum_event(&event_code, PAPI_ENUM_FIRST) != PAPI_OK) {
                continue;
            }

            do {
                if(PAPI_get_event_info(event_code, &info) == PAPI_OK) {
                    if(info.count) {
                        if((check_counter && checkCounter(event_code)) || !check_counter) {
                            event_codes.push_back(info.event_code);
                        }
                    }
                }
            } while (PAPI_enum_event(&event_code, check_avail_only) == PAPI_OK);
        }

        return 0;
    }
}