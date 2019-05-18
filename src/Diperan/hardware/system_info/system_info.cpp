//
// Created by sotiris on 30/7/2018.
//
#include "hardware/system_info/system_info.h"

namespace Diperan {

    int compile_system_info(std::vector <uint8_t> &output_buffer) {
        const PAPI_hw_info_t *system_info = NULL;
        int retval;

        retval = PAPI_library_init(PAPI_VER_CURRENT);
        if (retval != PAPI_VER_CURRENT) {
            std::cerr<<"Error! PAPI_library_init"<<std::endl;
            return retval;
        }

        system_info = PAPI_get_hardware_info();
        if (system_info == NULL) {
            std::cerr<<"Error! PAPI_get_hardware_info"<<std::endl;
            return 2;
        }

        flatbuffers::FlatBufferBuilder builder(1024);

        std::vector <flatbuffers::Offset<CpuTlb>> cpu_tlbs;
        std::vector <flatbuffers::Offset<CpuCache>> cpu_caches;
        Diperan::compile_caches_info(cpu_caches, builder);
        Diperan::compile_tlb_caches_info(cpu_tlbs, builder);
        int cnt, mpx;
        struct utsname uname_info;
        PAPI_option_t options;
        PAPI_get_opt(PAPI_COMPONENTINFO, &options);
        uname(&uname_info);

        std::string papi_major_version = std::to_string(PAPI_VERSION_MAJOR(PAPI_VERSION));
        std::string papi_minor_version = std::to_string(PAPI_VERSION_MINOR(PAPI_VERSION));
        std::string papi_revision_version = std::to_string(PAPI_VERSION_REVISION(PAPI_VERSION));
        std::string papi_increment_version = std::to_string(PAPI_VERSION_INCREMENT(PAPI_VERSION));
        std::string papi_version = papi_major_version + "." + papi_minor_version + "." + papi_revision_version + "." + papi_increment_version;
        auto papi_version_fb_string = builder.CreateString(papi_version);

        std::string sysname = uname_info.sysname;
        std::string release = uname_info.release;
        std::string os_info = sysname + release;
        auto os_info_fb_string = builder.CreateString(os_info);

        std::string cpu_vendor = (*system_info).vendor_string;
        auto cpu_vendor_fb_string = builder.CreateString(cpu_vendor);

        std::string cpu_model = (*system_info).model_string;
        auto cpu_model_fb_string = builder.CreateString(cpu_model);

        std::string CPUID_family = std::to_string((*system_info).cpuid_family);
        std::string CPUID_model = std::to_string((*system_info).cpuid_model);
        std::string CPUID_stepping = std::to_string((*system_info).cpuid_stepping);
        std::string CPUID = CPUID_family + " / " + CPUID_model + " / " + CPUID_stepping;
        auto CPUID_fb_string = builder.CreateString(CPUID);

        std::string vm_vendor = (*system_info).virtual_vendor_string;
        auto vm_vendor_fb_string = builder.CreateString(vm_vendor);

        BasicSystemInfoBuilder basic_sys_info(builder);
        basic_sys_info.add_papi_version(papi_version_fb_string);
        basic_sys_info.add_os_info(os_info_fb_string);
        basic_sys_info.add_cpu_vendor(cpu_vendor_fb_string);
        basic_sys_info.add_cpu_model(cpu_model_fb_string);
        basic_sys_info.add_cpu_rev((*system_info).revision);
        basic_sys_info.add_CPUID(CPUID_fb_string);
        basic_sys_info.add_max_mhz((*system_info).cpu_max_mhz);
        basic_sys_info.add_min_mhz((*system_info).cpu_min_mhz);
        basic_sys_info.add_cores((*system_info).totalcpus);
        basic_sys_info.add_SMT_thread_per_core((*system_info).threads);
        basic_sys_info.add_cores_per_socket((*system_info).cores);
        basic_sys_info.add_sockets((*system_info).sockets);
        basic_sys_info.add_cores_per_numa_region((*system_info).ncpu);
        basic_sys_info.add_numa_regions((*system_info).nnodes);
        basic_sys_info.add_in_vm((*system_info).virtualized);
        basic_sys_info.add_vm_vendor(vm_vendor_fb_string);

        cnt = PAPI_get_opt(PAPI_MAX_HWCTRS, NULL);
        mpx = PAPI_get_opt(PAPI_MAX_MPX_CTRS, NULL);

        basic_sys_info.add_hardware_counters_num(cnt);
        basic_sys_info.add_max_multiplex_counters(mpx);
        basic_sys_info.add_fast_counter_read(options.cmp_info->fast_counter_read);

        auto basic_sys_info_finished = basic_sys_info.Finish();
        builder.Finish(basic_sys_info_finished);

        auto cpu_tlbs_fb_vector = builder.CreateVector(cpu_tlbs);
        auto cpu_caches_fb_vector = builder.CreateVector(cpu_caches);

        TotalSystemInfoBuilder system_information(builder);
        system_information.add_cpu_tlbs(cpu_tlbs_fb_vector);
        system_information.add_cpu_caches(cpu_caches_fb_vector);
        system_information.add_basic_system_info(basic_sys_info_finished);
        auto papi_system_info = system_information.Finish();
        builder.Finish(papi_system_info);

        uint8_t *byte_buffer = builder.GetBufferPointer();
        int byte_buffer_size = builder.GetSize();

        output_buffer.reserve(byte_buffer_size);
        output_buffer.insert(output_buffer.end(), byte_buffer, byte_buffer + byte_buffer_size);

        return PAPI_OK;
    }

}