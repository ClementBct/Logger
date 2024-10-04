#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <chrono>
#include <ctime>
#include <iostream>
#include <stdarg.h>
// Color of text
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

// Default log level
#define DEFAULT_MIN_LOG_LEVEL 2
// Default show timestamp
#define DEFAULT_ENABLE_TIMESTAMP false
enum LogLevel
{
    LEVEL_TRACE = 0,   /*!< Tracing log. */
    LEVEL_DEBUG = 1,   /*!< Debugging log. */
    LEVEL_INFO = 2,    /*!< LOG to inform user. */
    LEVEL_NOTICE = 3,  /*!< LOG to notice user of data. */
    LEVEL_WARNING = 4, /*!< LOG when warning expect. */
    LEVEL_ERROR = 5,   /*!< LOG when a recoverable error expect. */
    LEVEL_FATAL = 6    /*!< LOG when a unrecoverable error expect. */
};

typedef struct config_t
{
    LogLevel min_log_level;
    bool show_timestamp;
} config_t;

class Logger
{
  private:
    Logger() = default;
    static Logger *m_instance;
    config_t m_config;
    const char *log_level_to_str(LogLevel i_log_level);
    const char *get_color_from_log_level(LogLevel i_log_level);

  public:
    static Logger *get_instance();
    void log(LogLevel i_log_level, const char *str, ...);
    config_t get_config();
    void set_config(config_t i_config);
};

#endif