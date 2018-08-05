/**
 *  @file    timer.hpp
 *  @author  Jack Ransom and Corey Ford
 *  @date    11/06/2018
 *  @version 1.0
 *
 *  @brief Timers used by schedulers for M4 architecture.
 *
 *  @section DESCRIPTION
 *
 *  This class produces timer information based on HAL library functions.
 *  For version using threads @see indexedTimer.hpp.
 */

//TODO(corey2.ford@live.uwe.ac.uk): eventually extend to implement duration,
//                                   timestep and index dependent capabilities!

#pragma once

#include <cstdint>
#include <cstddef>
#include <chrono>
#include <cassert>

namespace pcaudio {
namespace concurrency {
        
    template<class Period = std::ratio<1>>
    class Timer {
    private:
        const uint32_t duration_;
        const uint32_t timestep_;
        
        uint32_t before_;
    public:
        /**
        * Conconstructor
        * @param duration [description]
        * @param timestep [description]
        */
        Timer(float duration, float timestep) :
        duration_(static_cast<uint32_t>(duration)),
        timestep_(static_cast<uint32_t>(timestep)) {
        }
            
        /**
        * @brief unspecialised - breaks for unsupported timing
        * @param index [description]
        */
        void now(size_t index) {
            assert(0 && "Template param length not supported.");
        }
            
        /**
        * unspecialised - breaks for unsupported timings
        * @param index [description]
        */
        void wait(size_t index) const {
            assert(0 && "Template param length not supported.");
        }
    };
        
    /**
    * @brief current timestamp in milliseconds
    * @param index [description]
    */
    template<>
    void Timer<std::ratio<1,1000>>::now(size_t index) {
        #ifdef __ARCH_M4__
            before_ = HAL_GetTick();
        #endif //__ARCH_M4__
    }
        
    /**
    * @brief pause until timestep complete in milliseconds
    * @param index [description]
    */
    template<>
    void Timer<std::ratio<1,1000>>::wait(size_t index) const {
        #ifdef __ARCH_M4__
            // calculate the time remaining till next step
            auto timeLeft = timestep_ - ( HAL_GetTick() - before_);
            HAL_Delay( timeLeft );
        #endif /*__ARCH_M4_*/
    }

} // namespace concurrency
} // namespace pcaudio
