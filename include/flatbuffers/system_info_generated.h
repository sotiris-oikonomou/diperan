// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SYSTEMINFO_DIPERAN_SYSTEM_INFO_H_
#define FLATBUFFERS_GENERATED_SYSTEMINFO_DIPERAN_SYSTEM_INFO_H_

#include "flatbuffers/flatbuffers.h"

namespace Diperan {
namespace System {
namespace Info {

struct CpuTlb;

struct CpuCache;

struct BasicSystemInfo;

struct TotalSystemInfo;

enum CacheType {
  CacheType_Data = 0,
  CacheType_Instruction = 1,
  CacheType_Unified = 2,
  CacheType_TraceBuffer = 3,
  CacheType_Vector = 4,
  CacheType_MIN = CacheType_Data,
  CacheType_MAX = CacheType_Vector
};

inline const CacheType (&EnumValuesCacheType())[5] {
  static const CacheType values[] = {
    CacheType_Data,
    CacheType_Instruction,
    CacheType_Unified,
    CacheType_TraceBuffer,
    CacheType_Vector
  };
  return values;
}

inline const char * const *EnumNamesCacheType() {
  static const char * const names[] = {
    "Data",
    "Instruction",
    "Unified",
    "TraceBuffer",
    "Vector",
    nullptr
  };
  return names;
}

inline const char *EnumNameCacheType(CacheType e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesCacheType()[index];
}

struct CpuTlb FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TYPE = 4,
    VT_LEVEL = 6,
    VT_PAGE_SIZE = 8,
    VT_ENTRIES_NUM = 10,
    VT_ASSOCIATIVITY = 12
  };
  CacheType type() const {
    return static_cast<CacheType>(GetField<int8_t>(VT_TYPE, 0));
  }
  int32_t level() const {
    return GetField<int32_t>(VT_LEVEL, 0);
  }
  int32_t page_size() const {
    return GetField<int32_t>(VT_PAGE_SIZE, 0);
  }
  int32_t entries_num() const {
    return GetField<int32_t>(VT_ENTRIES_NUM, 0);
  }
  int32_t associativity() const {
    return GetField<int32_t>(VT_ASSOCIATIVITY, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_TYPE) &&
           VerifyField<int32_t>(verifier, VT_LEVEL) &&
           VerifyField<int32_t>(verifier, VT_PAGE_SIZE) &&
           VerifyField<int32_t>(verifier, VT_ENTRIES_NUM) &&
           VerifyField<int32_t>(verifier, VT_ASSOCIATIVITY) &&
           verifier.EndTable();
  }
};

struct CpuTlbBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(CacheType type) {
    fbb_.AddElement<int8_t>(CpuTlb::VT_TYPE, static_cast<int8_t>(type), 0);
  }
  void add_level(int32_t level) {
    fbb_.AddElement<int32_t>(CpuTlb::VT_LEVEL, level, 0);
  }
  void add_page_size(int32_t page_size) {
    fbb_.AddElement<int32_t>(CpuTlb::VT_PAGE_SIZE, page_size, 0);
  }
  void add_entries_num(int32_t entries_num) {
    fbb_.AddElement<int32_t>(CpuTlb::VT_ENTRIES_NUM, entries_num, 0);
  }
  void add_associativity(int32_t associativity) {
    fbb_.AddElement<int32_t>(CpuTlb::VT_ASSOCIATIVITY, associativity, 0);
  }
  explicit CpuTlbBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  CpuTlbBuilder &operator=(const CpuTlbBuilder &);
  flatbuffers::Offset<CpuTlb> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CpuTlb>(end);
    return o;
  }
};

inline flatbuffers::Offset<CpuTlb> CreateCpuTlb(
    flatbuffers::FlatBufferBuilder &_fbb,
    CacheType type = CacheType_Data,
    int32_t level = 0,
    int32_t page_size = 0,
    int32_t entries_num = 0,
    int32_t associativity = 0) {
  CpuTlbBuilder builder_(_fbb);
  builder_.add_associativity(associativity);
  builder_.add_entries_num(entries_num);
  builder_.add_page_size(page_size);
  builder_.add_level(level);
  builder_.add_type(type);
  return builder_.Finish();
}

struct CpuCache FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TYPE = 4,
    VT_LEVEL = 6,
    VT_SIZE = 8,
    VT_LINE_SIZE = 10,
    VT_LINES_NUM = 12,
    VT_ASSOCIATIVITY = 14
  };
  CacheType type() const {
    return static_cast<CacheType>(GetField<int8_t>(VT_TYPE, 0));
  }
  int32_t level() const {
    return GetField<int32_t>(VT_LEVEL, 0);
  }
  int32_t size() const {
    return GetField<int32_t>(VT_SIZE, 0);
  }
  int32_t line_size() const {
    return GetField<int32_t>(VT_LINE_SIZE, 0);
  }
  int32_t lines_num() const {
    return GetField<int32_t>(VT_LINES_NUM, 0);
  }
  int32_t associativity() const {
    return GetField<int32_t>(VT_ASSOCIATIVITY, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_TYPE) &&
           VerifyField<int32_t>(verifier, VT_LEVEL) &&
           VerifyField<int32_t>(verifier, VT_SIZE) &&
           VerifyField<int32_t>(verifier, VT_LINE_SIZE) &&
           VerifyField<int32_t>(verifier, VT_LINES_NUM) &&
           VerifyField<int32_t>(verifier, VT_ASSOCIATIVITY) &&
           verifier.EndTable();
  }
};

struct CpuCacheBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(CacheType type) {
    fbb_.AddElement<int8_t>(CpuCache::VT_TYPE, static_cast<int8_t>(type), 0);
  }
  void add_level(int32_t level) {
    fbb_.AddElement<int32_t>(CpuCache::VT_LEVEL, level, 0);
  }
  void add_size(int32_t size) {
    fbb_.AddElement<int32_t>(CpuCache::VT_SIZE, size, 0);
  }
  void add_line_size(int32_t line_size) {
    fbb_.AddElement<int32_t>(CpuCache::VT_LINE_SIZE, line_size, 0);
  }
  void add_lines_num(int32_t lines_num) {
    fbb_.AddElement<int32_t>(CpuCache::VT_LINES_NUM, lines_num, 0);
  }
  void add_associativity(int32_t associativity) {
    fbb_.AddElement<int32_t>(CpuCache::VT_ASSOCIATIVITY, associativity, 0);
  }
  explicit CpuCacheBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  CpuCacheBuilder &operator=(const CpuCacheBuilder &);
  flatbuffers::Offset<CpuCache> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CpuCache>(end);
    return o;
  }
};

inline flatbuffers::Offset<CpuCache> CreateCpuCache(
    flatbuffers::FlatBufferBuilder &_fbb,
    CacheType type = CacheType_Data,
    int32_t level = 0,
    int32_t size = 0,
    int32_t line_size = 0,
    int32_t lines_num = 0,
    int32_t associativity = 0) {
  CpuCacheBuilder builder_(_fbb);
  builder_.add_associativity(associativity);
  builder_.add_lines_num(lines_num);
  builder_.add_line_size(line_size);
  builder_.add_size(size);
  builder_.add_level(level);
  builder_.add_type(type);
  return builder_.Finish();
}

struct BasicSystemInfo FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_PAPI_VERSION = 4,
    VT_OS_INFO = 6,
    VT_CPU_VENDOR = 8,
    VT_CPU_MODEL = 10,
    VT_CPU_REV = 12,
    VT_CPUID = 14,
    VT_MAX_MHZ = 16,
    VT_MIN_MHZ = 18,
    VT_CORES = 20,
    VT_SMT_THREAD_PER_CORE = 22,
    VT_CORES_PER_SOCKET = 24,
    VT_SOCKETS = 26,
    VT_CORES_PER_NUMA_REGION = 28,
    VT_NUMA_REGIONS = 30,
    VT_IN_VM = 32,
    VT_VM_VENDOR = 34,
    VT_HARDWARE_COUNTERS_NUM = 36,
    VT_MAX_MULTIPLEX_COUNTERS = 38,
    VT_FAST_COUNTER_READ = 40
  };
  const flatbuffers::String *papi_version() const {
    return GetPointer<const flatbuffers::String *>(VT_PAPI_VERSION);
  }
  const flatbuffers::String *os_info() const {
    return GetPointer<const flatbuffers::String *>(VT_OS_INFO);
  }
  const flatbuffers::String *cpu_vendor() const {
    return GetPointer<const flatbuffers::String *>(VT_CPU_VENDOR);
  }
  const flatbuffers::String *cpu_model() const {
    return GetPointer<const flatbuffers::String *>(VT_CPU_MODEL);
  }
  float cpu_rev() const {
    return GetField<float>(VT_CPU_REV, 0.0f);
  }
  const flatbuffers::String *CPUID() const {
    return GetPointer<const flatbuffers::String *>(VT_CPUID);
  }
  int32_t max_mhz() const {
    return GetField<int32_t>(VT_MAX_MHZ, 0);
  }
  int32_t min_mhz() const {
    return GetField<int32_t>(VT_MIN_MHZ, 0);
  }
  int32_t cores() const {
    return GetField<int32_t>(VT_CORES, 0);
  }
  int32_t SMT_thread_per_core() const {
    return GetField<int32_t>(VT_SMT_THREAD_PER_CORE, 1);
  }
  int32_t cores_per_socket() const {
    return GetField<int32_t>(VT_CORES_PER_SOCKET, 1);
  }
  int32_t sockets() const {
    return GetField<int32_t>(VT_SOCKETS, 1);
  }
  int32_t cores_per_numa_region() const {
    return GetField<int32_t>(VT_CORES_PER_NUMA_REGION, 1);
  }
  int32_t numa_regions() const {
    return GetField<int32_t>(VT_NUMA_REGIONS, 0);
  }
  bool in_vm() const {
    return GetField<uint8_t>(VT_IN_VM, 0) != 0;
  }
  const flatbuffers::String *vm_vendor() const {
    return GetPointer<const flatbuffers::String *>(VT_VM_VENDOR);
  }
  int32_t hardware_counters_num() const {
    return GetField<int32_t>(VT_HARDWARE_COUNTERS_NUM, 0);
  }
  int32_t max_multiplex_counters() const {
    return GetField<int32_t>(VT_MAX_MULTIPLEX_COUNTERS, 0);
  }
  bool fast_counter_read() const {
    return GetField<uint8_t>(VT_FAST_COUNTER_READ, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_PAPI_VERSION) &&
           verifier.VerifyString(papi_version()) &&
           VerifyOffset(verifier, VT_OS_INFO) &&
           verifier.VerifyString(os_info()) &&
           VerifyOffset(verifier, VT_CPU_VENDOR) &&
           verifier.VerifyString(cpu_vendor()) &&
           VerifyOffset(verifier, VT_CPU_MODEL) &&
           verifier.VerifyString(cpu_model()) &&
           VerifyField<float>(verifier, VT_CPU_REV) &&
           VerifyOffset(verifier, VT_CPUID) &&
           verifier.VerifyString(CPUID()) &&
           VerifyField<int32_t>(verifier, VT_MAX_MHZ) &&
           VerifyField<int32_t>(verifier, VT_MIN_MHZ) &&
           VerifyField<int32_t>(verifier, VT_CORES) &&
           VerifyField<int32_t>(verifier, VT_SMT_THREAD_PER_CORE) &&
           VerifyField<int32_t>(verifier, VT_CORES_PER_SOCKET) &&
           VerifyField<int32_t>(verifier, VT_SOCKETS) &&
           VerifyField<int32_t>(verifier, VT_CORES_PER_NUMA_REGION) &&
           VerifyField<int32_t>(verifier, VT_NUMA_REGIONS) &&
           VerifyField<uint8_t>(verifier, VT_IN_VM) &&
           VerifyOffset(verifier, VT_VM_VENDOR) &&
           verifier.VerifyString(vm_vendor()) &&
           VerifyField<int32_t>(verifier, VT_HARDWARE_COUNTERS_NUM) &&
           VerifyField<int32_t>(verifier, VT_MAX_MULTIPLEX_COUNTERS) &&
           VerifyField<uint8_t>(verifier, VT_FAST_COUNTER_READ) &&
           verifier.EndTable();
  }
};

struct BasicSystemInfoBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_papi_version(flatbuffers::Offset<flatbuffers::String> papi_version) {
    fbb_.AddOffset(BasicSystemInfo::VT_PAPI_VERSION, papi_version);
  }
  void add_os_info(flatbuffers::Offset<flatbuffers::String> os_info) {
    fbb_.AddOffset(BasicSystemInfo::VT_OS_INFO, os_info);
  }
  void add_cpu_vendor(flatbuffers::Offset<flatbuffers::String> cpu_vendor) {
    fbb_.AddOffset(BasicSystemInfo::VT_CPU_VENDOR, cpu_vendor);
  }
  void add_cpu_model(flatbuffers::Offset<flatbuffers::String> cpu_model) {
    fbb_.AddOffset(BasicSystemInfo::VT_CPU_MODEL, cpu_model);
  }
  void add_cpu_rev(float cpu_rev) {
    fbb_.AddElement<float>(BasicSystemInfo::VT_CPU_REV, cpu_rev, 0.0f);
  }
  void add_CPUID(flatbuffers::Offset<flatbuffers::String> CPUID) {
    fbb_.AddOffset(BasicSystemInfo::VT_CPUID, CPUID);
  }
  void add_max_mhz(int32_t max_mhz) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_MAX_MHZ, max_mhz, 0);
  }
  void add_min_mhz(int32_t min_mhz) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_MIN_MHZ, min_mhz, 0);
  }
  void add_cores(int32_t cores) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_CORES, cores, 0);
  }
  void add_SMT_thread_per_core(int32_t SMT_thread_per_core) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_SMT_THREAD_PER_CORE, SMT_thread_per_core, 1);
  }
  void add_cores_per_socket(int32_t cores_per_socket) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_CORES_PER_SOCKET, cores_per_socket, 1);
  }
  void add_sockets(int32_t sockets) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_SOCKETS, sockets, 1);
  }
  void add_cores_per_numa_region(int32_t cores_per_numa_region) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_CORES_PER_NUMA_REGION, cores_per_numa_region, 1);
  }
  void add_numa_regions(int32_t numa_regions) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_NUMA_REGIONS, numa_regions, 0);
  }
  void add_in_vm(bool in_vm) {
    fbb_.AddElement<uint8_t>(BasicSystemInfo::VT_IN_VM, static_cast<uint8_t>(in_vm), 0);
  }
  void add_vm_vendor(flatbuffers::Offset<flatbuffers::String> vm_vendor) {
    fbb_.AddOffset(BasicSystemInfo::VT_VM_VENDOR, vm_vendor);
  }
  void add_hardware_counters_num(int32_t hardware_counters_num) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_HARDWARE_COUNTERS_NUM, hardware_counters_num, 0);
  }
  void add_max_multiplex_counters(int32_t max_multiplex_counters) {
    fbb_.AddElement<int32_t>(BasicSystemInfo::VT_MAX_MULTIPLEX_COUNTERS, max_multiplex_counters, 0);
  }
  void add_fast_counter_read(bool fast_counter_read) {
    fbb_.AddElement<uint8_t>(BasicSystemInfo::VT_FAST_COUNTER_READ, static_cast<uint8_t>(fast_counter_read), 0);
  }
  explicit BasicSystemInfoBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  BasicSystemInfoBuilder &operator=(const BasicSystemInfoBuilder &);
  flatbuffers::Offset<BasicSystemInfo> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<BasicSystemInfo>(end);
    return o;
  }
};

inline flatbuffers::Offset<BasicSystemInfo> CreateBasicSystemInfo(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> papi_version = 0,
    flatbuffers::Offset<flatbuffers::String> os_info = 0,
    flatbuffers::Offset<flatbuffers::String> cpu_vendor = 0,
    flatbuffers::Offset<flatbuffers::String> cpu_model = 0,
    float cpu_rev = 0.0f,
    flatbuffers::Offset<flatbuffers::String> CPUID = 0,
    int32_t max_mhz = 0,
    int32_t min_mhz = 0,
    int32_t cores = 0,
    int32_t SMT_thread_per_core = 1,
    int32_t cores_per_socket = 1,
    int32_t sockets = 1,
    int32_t cores_per_numa_region = 1,
    int32_t numa_regions = 0,
    bool in_vm = false,
    flatbuffers::Offset<flatbuffers::String> vm_vendor = 0,
    int32_t hardware_counters_num = 0,
    int32_t max_multiplex_counters = 0,
    bool fast_counter_read = false) {
  BasicSystemInfoBuilder builder_(_fbb);
  builder_.add_max_multiplex_counters(max_multiplex_counters);
  builder_.add_hardware_counters_num(hardware_counters_num);
  builder_.add_vm_vendor(vm_vendor);
  builder_.add_numa_regions(numa_regions);
  builder_.add_cores_per_numa_region(cores_per_numa_region);
  builder_.add_sockets(sockets);
  builder_.add_cores_per_socket(cores_per_socket);
  builder_.add_SMT_thread_per_core(SMT_thread_per_core);
  builder_.add_cores(cores);
  builder_.add_min_mhz(min_mhz);
  builder_.add_max_mhz(max_mhz);
  builder_.add_CPUID(CPUID);
  builder_.add_cpu_rev(cpu_rev);
  builder_.add_cpu_model(cpu_model);
  builder_.add_cpu_vendor(cpu_vendor);
  builder_.add_os_info(os_info);
  builder_.add_papi_version(papi_version);
  builder_.add_fast_counter_read(fast_counter_read);
  builder_.add_in_vm(in_vm);
  return builder_.Finish();
}

inline flatbuffers::Offset<BasicSystemInfo> CreateBasicSystemInfoDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *papi_version = nullptr,
    const char *os_info = nullptr,
    const char *cpu_vendor = nullptr,
    const char *cpu_model = nullptr,
    float cpu_rev = 0.0f,
    const char *CPUID = nullptr,
    int32_t max_mhz = 0,
    int32_t min_mhz = 0,
    int32_t cores = 0,
    int32_t SMT_thread_per_core = 1,
    int32_t cores_per_socket = 1,
    int32_t sockets = 1,
    int32_t cores_per_numa_region = 1,
    int32_t numa_regions = 0,
    bool in_vm = false,
    const char *vm_vendor = nullptr,
    int32_t hardware_counters_num = 0,
    int32_t max_multiplex_counters = 0,
    bool fast_counter_read = false) {
  return Diperan::System::Info::CreateBasicSystemInfo(
      _fbb,
      papi_version ? _fbb.CreateString(papi_version) : 0,
      os_info ? _fbb.CreateString(os_info) : 0,
      cpu_vendor ? _fbb.CreateString(cpu_vendor) : 0,
      cpu_model ? _fbb.CreateString(cpu_model) : 0,
      cpu_rev,
      CPUID ? _fbb.CreateString(CPUID) : 0,
      max_mhz,
      min_mhz,
      cores,
      SMT_thread_per_core,
      cores_per_socket,
      sockets,
      cores_per_numa_region,
      numa_regions,
      in_vm,
      vm_vendor ? _fbb.CreateString(vm_vendor) : 0,
      hardware_counters_num,
      max_multiplex_counters,
      fast_counter_read);
}

struct TotalSystemInfo FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CPU_TLBS = 4,
    VT_CPU_CACHES = 6,
    VT_BASIC_SYSTEM_INFO = 8
  };
  const flatbuffers::Vector<flatbuffers::Offset<CpuTlb>> *cpu_tlbs() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<CpuTlb>> *>(VT_CPU_TLBS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<CpuCache>> *cpu_caches() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<CpuCache>> *>(VT_CPU_CACHES);
  }
  const BasicSystemInfo *basic_system_info() const {
    return GetPointer<const BasicSystemInfo *>(VT_BASIC_SYSTEM_INFO);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_CPU_TLBS) &&
           verifier.VerifyVector(cpu_tlbs()) &&
           verifier.VerifyVectorOfTables(cpu_tlbs()) &&
           VerifyOffset(verifier, VT_CPU_CACHES) &&
           verifier.VerifyVector(cpu_caches()) &&
           verifier.VerifyVectorOfTables(cpu_caches()) &&
           VerifyOffset(verifier, VT_BASIC_SYSTEM_INFO) &&
           verifier.VerifyTable(basic_system_info()) &&
           verifier.EndTable();
  }
};

struct TotalSystemInfoBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_cpu_tlbs(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<CpuTlb>>> cpu_tlbs) {
    fbb_.AddOffset(TotalSystemInfo::VT_CPU_TLBS, cpu_tlbs);
  }
  void add_cpu_caches(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<CpuCache>>> cpu_caches) {
    fbb_.AddOffset(TotalSystemInfo::VT_CPU_CACHES, cpu_caches);
  }
  void add_basic_system_info(flatbuffers::Offset<BasicSystemInfo> basic_system_info) {
    fbb_.AddOffset(TotalSystemInfo::VT_BASIC_SYSTEM_INFO, basic_system_info);
  }
  explicit TotalSystemInfoBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  TotalSystemInfoBuilder &operator=(const TotalSystemInfoBuilder &);
  flatbuffers::Offset<TotalSystemInfo> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<TotalSystemInfo>(end);
    return o;
  }
};

inline flatbuffers::Offset<TotalSystemInfo> CreateTotalSystemInfo(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<CpuTlb>>> cpu_tlbs = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<CpuCache>>> cpu_caches = 0,
    flatbuffers::Offset<BasicSystemInfo> basic_system_info = 0) {
  TotalSystemInfoBuilder builder_(_fbb);
  builder_.add_basic_system_info(basic_system_info);
  builder_.add_cpu_caches(cpu_caches);
  builder_.add_cpu_tlbs(cpu_tlbs);
  return builder_.Finish();
}

inline flatbuffers::Offset<TotalSystemInfo> CreateTotalSystemInfoDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<CpuTlb>> *cpu_tlbs = nullptr,
    const std::vector<flatbuffers::Offset<CpuCache>> *cpu_caches = nullptr,
    flatbuffers::Offset<BasicSystemInfo> basic_system_info = 0) {
  return Diperan::System::Info::CreateTotalSystemInfo(
      _fbb,
      cpu_tlbs ? _fbb.CreateVector<flatbuffers::Offset<CpuTlb>>(*cpu_tlbs) : 0,
      cpu_caches ? _fbb.CreateVector<flatbuffers::Offset<CpuCache>>(*cpu_caches) : 0,
      basic_system_info);
}

inline const Diperan::System::Info::TotalSystemInfo *GetTotalSystemInfo(const void *buf) {
  return flatbuffers::GetRoot<Diperan::System::Info::TotalSystemInfo>(buf);
}

inline const Diperan::System::Info::TotalSystemInfo *GetSizePrefixedTotalSystemInfo(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<Diperan::System::Info::TotalSystemInfo>(buf);
}

inline bool VerifyTotalSystemInfoBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Diperan::System::Info::TotalSystemInfo>(nullptr);
}

inline bool VerifySizePrefixedTotalSystemInfoBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<Diperan::System::Info::TotalSystemInfo>(nullptr);
}

inline void FinishTotalSystemInfoBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Diperan::System::Info::TotalSystemInfo> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedTotalSystemInfoBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Diperan::System::Info::TotalSystemInfo> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace Info
}  // namespace System
}  // namespace Diperan

#endif  // FLATBUFFERS_GENERATED_SYSTEMINFO_DIPERAN_SYSTEM_INFO_H_
