//
//  Created by Sotiris Oikonomou.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
namespace Diperan {
// Initialization struct for the spdlog
    struct loggerInitValues_t {
        std::string logfile;
        std::string loggerName;
        int numberOfFiles;
        int sizeInBytes;
    };
    struct loggerGlobalValues_t {
        size_t q_size;  // queue size must be power of 2
        int secondsToFlush;
        std::string formatPattern;
    };

    static loggerInitValues_t g_ClientLoggerInitValues = {
            "/var/log/diperan",
            "diperan",
            3,
            (1048576 * 5),
    };

    static loggerGlobalValues_t g_LoggerGlobalValues = {4096, 2,
                                                        "[%H:%M:%S]-[%L] %v"};

    inline void logGlobalInit() {
      spdlog::set_pattern(g_LoggerGlobalValues.formatPattern);
      // Block on queue full and flush every 2 seconds
      spdlog::set_async_mode(
              g_LoggerGlobalValues.q_size, spdlog::async_overflow_policy::block_retry,
              nullptr, std::chrono::seconds(g_LoggerGlobalValues.secondsToFlush));
    }

    inline void logClientInit() {
      auto diperanLogger = spdlog::rotating_logger_mt(
              g_ClientLoggerInitValues.loggerName, g_ClientLoggerInitValues.logfile,
              g_ClientLoggerInitValues.sizeInBytes, g_ClientLoggerInitValues.numberOfFiles);
      diperanLogger->set_level(spdlog::level::debug);
    }
}
#endif
