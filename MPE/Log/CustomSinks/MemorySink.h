#pragma once

#include "spdlog/sinks/base_sink.h"

#include <mutex>
#include <sstream>

/**
 * @file MemorySink.h
 * @brief Custom memory sink for logging.
 * @date 2024-05-09
 * @author Sebastian Termen
 */

namespace MPE
{
/**
 * @brief Custom memory sink for logging.
 * @details This class is used to create a custom memory sink for logging.
 * @tparam Mutex The mutex type to use for the memory sink.
 * @date 2024-05-09
 */
template <typename Mutex>
class MemorySink : public spdlog::sinks::base_sink<Mutex>
{
  public:
    std::string get_contents_and_clear()
    {
        auto contents = this->get_contents();
        this->clear();
        return contents;
    }

    std::string get_contents() { return m_stream.str(); }

    void clear()
    {
        m_stream.str("");
        m_stream.clear();
    }

  protected:
    /**
     * @brief Log the message to memory.
     * @param msg The message to log.
     * @date 2024-05-09
     */
    void sink_it_(const spdlog::details::log_msg &msg) override
    {
        spdlog::memory_buf_t formatted;
        spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
        m_stream << fmt::to_string(formatted);
    }

    void flush_() override { m_stream.flush(); }

  private:
    std::stringstream m_stream;
};
}