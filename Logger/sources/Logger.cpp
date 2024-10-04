#include "Logger.hpp"

Logger *Logger::m_instance = nullptr;

Logger *Logger::get_instance()
{
    if (nullptr == m_instance)
    {
        config_t config;
        config.min_log_level = (LogLevel)DEFAULT_MIN_LOG_LEVEL;
        config.show_timestamp = DEFAULT_ENABLE_TIMESTAMP;
        m_instance = new Logger();
        m_instance->m_config = config;
    }
    return m_instance;
}

const char *Logger::get_color_from_log_level(LogLevel i_log_level)
{
    switch (i_log_level)
    {
    case LEVEL_ERROR:
        return KRED;
    default:
        return KNRM;
    }
}

const char *Logger::log_level_to_str(LogLevel i_log_level)
{
    switch (i_log_level)
    {
    case LEVEL_TRACE:
        return "LEVEL_TRACE";
    case LEVEL_DEBUG:
        return "LEVEL_DEBUG";
    case LEVEL_INFO:
        return "LEVEL_INFO";
    case LEVEL_NOTICE:
        return "LEVEL_NOTICE";
    case LEVEL_WARNING:
        return "LEVEL_WARNING";
    case LEVEL_ERROR:
        return "LEVEL_ERROR";
    case LEVEL_FATAL:
        return "LEVEL_FATAL";
    default:
        return "LEVEL_UNKNOWN";
    }
}
void Logger::log(LogLevel i_log_level, const char *str, ...)
{
    if (i_log_level < m_config.min_log_level)
    {
        return;
    }
    // initializing list pointer
    va_list ptr;
    va_start(ptr, str);

    // char array to store token
    char token[1000];
    // index of where to store the characters of str in
    // token
    int k = 0;
    printf("%s[%s] ", get_color_from_log_level(i_log_level), log_level_to_str(i_log_level));
    if (m_config.show_timestamp)
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
        printf("[%ld] ", timestamp);
    }
    // parsing the formatted string
    for (int i = 0; str[i] != '\0'; i++)
    {
        token[k++] = str[i];
        if (str[i + 1] == '%' || str[i + 1] == '\0')
        {
            token[k] = '\0';
            k = 0;
            if (token[0] != '%')
            {
                fprintf(stdout, "%s",
                        token); // printing the whole token if
                                // it is not a format specifier
            }
            else
            {
                int j = 1;
                char ch1 = 0;

                // this loop is required when printing
                // formatted value like 0.2f, when ch1='f'
                // loop ends
                while ((ch1 = token[j++]) < 58)
                {
                }
                // for integers
                if (ch1 == 'i' || ch1 == 'd' || ch1 == 'u' || ch1 == 'h')
                {
                    fprintf(stdout, token, va_arg(ptr, int));
                }
                // for characters
                else if (ch1 == 'c')
                {
                    fprintf(stdout, token, va_arg(ptr, int));
                }
                // for float values
                else if (ch1 == 'f')
                {
                    fprintf(stdout, token, va_arg(ptr, double));
                }
                else if (ch1 == 'l')
                {
                    char ch2 = token[2];

                    // for long int
                    if (ch2 == 'u' || ch2 == 'd' || ch2 == 'i')
                    {
                        fprintf(stdout, token, va_arg(ptr, long));
                    }

                    // for double
                    else if (ch2 == 'f')
                    {
                        fprintf(stdout, token, va_arg(ptr, double));
                    }
                }
                else if (ch1 == 'L')
                {
                    char ch2 = token[2];

                    // for long long int
                    if (ch2 == 'u' || ch2 == 'd' || ch2 == 'i')
                    {
                        fprintf(stdout, token, va_arg(ptr, long long));
                    }

                    // for long double
                    else if (ch2 == 'f')
                    {
                        fprintf(stdout, token, va_arg(ptr, long double));
                    }
                }

                // for strings
                else if (ch1 == 's')
                {
                    fprintf(stdout, token, va_arg(ptr, char *));
                }

                // print the whole token
                // if no case is matched
                else
                {
                    fprintf(stdout, "%s", token);
                }
            }
        }
    }
    // ending traversal
    va_end(ptr);
    printf("%s\n", KNRM);
}

config_t Logger::get_config()
{
    return m_config;
}
void Logger::set_config(config_t i_config)
{
    m_config = i_config;
}
