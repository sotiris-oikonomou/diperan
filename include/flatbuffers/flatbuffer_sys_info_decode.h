//
// Created by sotiris on 18/8/2018.
//

#ifndef FLATBUFFER_DECODE_H
#define FLATBUFFER_DECODE_H

#include <memory>

#include "mainVariables.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/system_info_generated.h"
#include "hardware/system_info/system_info.h"
#include "packet_type_definitions.h"
#include "optional.h"

using namespace Diperan::System::Info;
namespace Diperan {
    inline std::experimental::optional<const TotalSystemInfo*> flatbuffer_sys_info_decode(const std::vector<uint8_t>& buffer) {
        auto temp_verifier = flatbuffers::Verifier(reinterpret_cast<const uint8_t*>(buffer.data()), buffer.size());
        bool is_ok = VerifyTotalSystemInfoBuffer(temp_verifier);

        if(is_ok) {
            auto temp_system_info_obj = GetTotalSystemInfo(reinterpret_cast<const char*>(buffer.data()));
            return temp_system_info_obj;
        }
        else {
            std::cerr<<"TotalSystemInfo Flatbuffer verification Error"<<std::endl;
            return {};
        }
    }

    inline std::string flatbuffer_sys_info_cache_type_print(const CacheType type) {
        switch(type) {
            case CacheType_Data:
                return "Data";
            case CacheType_Instruction:
                return "Instruction";
            case CacheType_Unified:
                return "Unified";
            case CacheType_TraceBuffer:
                return "Tracebuffer";
            case CacheType_Vector:
                return "Vector";
            default:
                return "Unknown";
        }
    }

    inline void flatbuffer_sys_info_print(const TotalSystemInfo* flatbuffer_obj) {
        if(flatbuffer_obj == nullptr) {
            return;
        }
        auto basic_system_info = flatbuffer_obj->basic_system_info();
        std::cout<<"Basic system info"<<std::endl;
        std::cout<<" Papi version:             "<<basic_system_info->papi_version()->c_str()<<std::endl;
        std::cout<<" Os info:                  "<<basic_system_info->os_info()->c_str()<<std::endl;
        std::cout<<" CPU Vendor:               "<<basic_system_info->cpu_vendor()->c_str()<<std::endl;
        std::cout<<" CPU Model:                "<<basic_system_info->cpu_model()->c_str()<<std::endl;
        std::cout<<" CPU Rev:                  "<<basic_system_info->cpu_rev()<<std::endl;
        std::cout<<" CPUID:                    "<<basic_system_info->CPUID()->c_str()<<std::endl;
        std::cout<<" Max Mhz:                  "<<basic_system_info->max_mhz()<<std::endl;
        std::cout<<" Min Mhz:                  "<<basic_system_info->min_mhz()<<std::endl;
        std::cout<<" # Cores:                  "<<basic_system_info->SMT_thread_per_core()<<std::endl;
        std::cout<<" # Cores/socket:           "<<basic_system_info->cores_per_socket()<<std::endl;
        std::cout<<" # Sockets:                "<<basic_system_info->sockets()<<std::endl;
        std::cout<<" # Numa regions:           "<<basic_system_info->numa_regions()<<std::endl;
        std::cout<<" # Runs in VM:             "<<basic_system_info->in_vm()<<std::endl;
        std::cout<<" # VM vendor:              "<<basic_system_info->vm_vendor()->c_str()<<std::endl;
        std::cout<<" # Hardware counters:      "<<basic_system_info->hardware_counters_num()<<std::endl;
        std::cout<<" # Max multiplex counters: "<<basic_system_info->max_multiplex_counters()<<std::endl;
        std::cout<<" # Fast counter read:      "<<basic_system_info->fast_counter_read()<<std::endl;

        std::cout<<"CPU Tlb Caches"<<std::endl;
        auto cpu_tlbs = flatbuffer_obj->cpu_tlbs();
        auto cpu_tlbs_length = cpu_tlbs->Length();
        for(uint32_t i = 0; i < cpu_tlbs_length; i++) {
            std::cout<<" Tlb Cache Type: "<<flatbuffer_sys_info_cache_type_print(cpu_tlbs->Get(i)->type())<<std::endl;
            std::cout<<"  Level:         "<<cpu_tlbs->Get(i)->level()<<std::endl;
            std::cout<<"  Page size:     "<<cpu_tlbs->Get(i)->page_size()<<" KB"<<std::endl;
            std::cout<<"  # Entries:     "<<cpu_tlbs->Get(i)->entries_num()<<std::endl;
            std::cout<<"  Associativity: "<<cpu_tlbs->Get(i)->associativity()<<std::endl;
            std::cout<<"-----------------"<<std::endl<<std::endl;
        }

        std::cout<<"CPU Caches"<<std::endl;
        auto cpu_caches = flatbuffer_obj->cpu_caches();
        auto cpu_caches_length = cpu_caches->Length();
        for(uint32_t i = 0; i < cpu_caches_length; i++) {
            std::cout<<" Cache Type:     "<<flatbuffer_sys_info_cache_type_print(cpu_caches->Get(i)->type())<<std::endl;
            std::cout<<"  Level:         "<<cpu_caches->Get(i)->level()<<std::endl;
            std::cout<<"  Size:          "<<cpu_caches->Get(i)->size()<<" KB"<<std::endl;
            std::cout<<"  Line size:     "<<cpu_caches->Get(i)->line_size()<<" B"<<std::endl;
            std::cout<<"  # Lines:       "<<cpu_caches->Get(i)->lines_num()<<std::endl;
            std::cout<<"  Associativity: "<<cpu_caches->Get(i)->associativity()<<std::endl;
            std::cout<<"-------------------"<<std::endl;
        }
    }
}
#endif //CLIENT_FLATBUFFER_DECODE_H
