#pragma once

#include "MPE/Core/_CORE.h"

/**
 * @file Time.h
 * @brief Time class for the MPE engine.
 * @date 2024-05-05
 * @author Sebastian Termen
 */

namespace MPE
{
    /**
     * @brief Time class for the MPE engine.
     * @details This class is used to define the time for the MPE engine.
     * @date 2024-05-05
     */
    class MPE_API Time
    {
    public:
        Time(float time = 0.0f);

        float GetSeconds() const;
        float GetMilliSeconds() const;

        /**
         * @brief Conversion operator to float.
         * @details This operator is used to convert the Time object to a float.
         * @return The time in seconds.
         */
        operator float() const;

    private:
        float SYS_TIME;
    };
}