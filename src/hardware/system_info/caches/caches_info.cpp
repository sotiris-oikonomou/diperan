//
// Created by sotiris on 7/8/2018.
//

#include "hardware/system_info/caches/caches_info.h"

namespace Diperan {

    int compile_tlb_caches_info(std::vector <flatbuffers::Offset<CpuTlb>> &cpu_tlbs,
                                flatbuffers::FlatBufferBuilder &builder) {
        const PAPI_hw_info_t *system_info = NULL;
        PAPI_mh_level_t *L;

        system_info = PAPI_get_hardware_info();
        if (system_info == NULL) {
            std::cerr<<"Error! PAPI_get_hardware_info"<<std::endl;
            return 2;
        }
        //Memory Cache and TLB Hierarchy Information.
        L = (PAPI_mh_level_t * ) & (system_info->mem_hierarchy.level[0]);
        /* Scan the TLB structures */
        for (int32_t i = 0; i < system_info->mem_hierarchy.levels; i++) {
            for (int32_t j = 0; j < PAPI_MH_MAX_LEVELS; j++) {
                CpuTlbBuilder cpu_tlb(builder);
                cpu_tlb.add_level(i + 1);
                switch (PAPI_MH_CACHE_TYPE(L[i].tlb[j].type)) {
                    case PAPI_MH_TYPE_UNIFIED:
                        //printf("L%d Unified TLB:\n", i + 1);
                        cpu_tlb.add_type(CacheType_Unified);
                        break;
                    case PAPI_MH_TYPE_DATA:
                        //printf("L%d Data TLB:\n", i + 1);
                        cpu_tlb.add_type(CacheType_Data);
                        break;
                    case PAPI_MH_TYPE_INST:
                        //printf("L%d Instruction TLB:\n", i + 1);
                        cpu_tlb.add_type(CacheType_Instruction);
                        break;
                }
                if (L[i].tlb[j].type) {
                    if (L[i].tlb[j].page_size) {
                        //printf("  Page Size:         %6d KB\n",
                        //       L[i].tlb[j].page_size >> 10);
                        cpu_tlb.add_page_size(L[i].tlb[j].page_size >> 10);
                    }
                    //printf("  Number of Entries: %6d\n",
                    //       L[i].tlb[j].num_entries);
                    cpu_tlb.add_entries_num(L[i].tlb[j].num_entries);
                    switch (L[i].tlb[j].associativity) {
                        case 0: /* undefined */
                            cpu_tlb.add_associativity(0);
                            break;
                        case 1:
                            //printf("  Associativity:      Direct Mapped\n\n");
                            cpu_tlb.add_associativity(1);
                            break;
                        case SHRT_MAX:
                            //printf("  Associativity:       Full\n\n");
                            cpu_tlb.add_associativity(-1);
                            break;
                        default:
                            //printf("  Associativity:     %6d\n\n",
                            //       L[i].tlb[j].associativity);
                            cpu_tlb.add_associativity(L[i].tlb[j].associativity);
                            break;
                    }
                }
                auto cpu_tlb_finished = cpu_tlb.Finish();
                builder.Finish(cpu_tlb_finished);
                cpu_tlbs.push_back(cpu_tlb_finished);
            }
        }
        return PAPI_OK;
    }

    int compile_caches_info(std::vector <flatbuffers::Offset<CpuCache>> &cpu_caches,
                                     flatbuffers::FlatBufferBuilder &builder) {
        const PAPI_hw_info_t *system_info = NULL;
        PAPI_mh_level_t *L;

        system_info = PAPI_get_hardware_info();
        if (system_info == NULL) {
            std::cerr<<"Error! PAPI_get_hardware_info"<<std::endl;
            return 2;
        }

        //Memory Cache and TLB Hierarchy Information.
        L = (PAPI_mh_level_t * ) & (system_info->mem_hierarchy.level[0]);

        /* Scan the Cache structures */
        //printf("\nCache Information.\n\n");
        for (int32_t i = 0; i < system_info->mem_hierarchy.levels; i++) {
            for (int32_t j = 0; j < 2; j++) {
                CpuCacheBuilder cpu_cache(builder);
                cpu_cache.add_level(i + 1);
                switch (PAPI_MH_CACHE_TYPE(L[i].cache[j].type)) {
                    case PAPI_MH_TYPE_UNIFIED:
                        //printf("L%d Unified Cache:\n", i + 1);
                        cpu_cache.add_type(CacheType_Unified);
                        break;
                    case PAPI_MH_TYPE_DATA:
                        //printf("L%d Data Cache:\n", i + 1);
                        cpu_cache.add_type(CacheType_Data);
                        break;
                    case PAPI_MH_TYPE_INST:
                        //printf("L%d Instruction Cache:\n", i + 1);
                        cpu_cache.add_type(CacheType_Instruction);
                        break;
                    case PAPI_MH_TYPE_TRACE:
                        //printf("L%d Trace Buffer:\n", i + 1);
                        cpu_cache.add_type(CacheType_TraceBuffer);
                        break;
                    case PAPI_MH_TYPE_VECTOR:
                        //printf("L%d Vector Cache:\n", i + 1);
                        cpu_cache.add_type(CacheType_Vector);
                        break;
                }
                if (L[i].cache[j].type) {
                    //printf("  Total size:        %6d KB\n  Line size:         %6d B\n  Number of Lines:   %6d\n  Associativity:     %6d\n\n",
                    //       (L[i].cache[j].size) >> 10, L[i].cache[j].line_size,
                    //       L[i].cache[j].num_lines,
                    //       L[i].cache[j].associativity);
                    cpu_cache.add_size((L[i].cache[j].size) >> 10);
                    cpu_cache.add_line_size(L[i].cache[j].line_size);
                    cpu_cache.add_lines_num(L[i].cache[j].num_lines);
                    cpu_cache.add_associativity(L[i].cache[j].associativity);
                }
                auto cpu_cache_finished = cpu_cache.Finish();
                builder.Finish(cpu_cache_finished);
                cpu_caches.push_back(cpu_cache_finished);
            }
        }
        return PAPI_OK;
    }

}