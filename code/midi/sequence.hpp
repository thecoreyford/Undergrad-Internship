/**
 *  @file    Sequence.hpp
 *  @author  Corey Ford
 *  @date    17/07/2018
 *  @version 1.0
 *
 *  @brief A class holding midi messages for multiple steps of a sequence.
 *
 *  @section DESCRIPTION
 *
 *  This class wraps a vector of steps (a vector of midi messages)
 *  so that each step of a step of the sequencer can hold many messages.
 *
 */

#pragma once

#include <vector>
#include <cassert>
#include <algorithm> // for std::remove
#include <midi/message.hpp>

namespace pcaudio{
namespace midi{
    
    using Step = std::vector<Message>; ///< alias
    
    class Sequence {
    private:
        std::vector<Step> sequence; ///< our main sequence container
        
        const Message dummySysEx = Message((uint8_t)0xF0,
                                           (uint8_t)0x00,
                                           (uint8_t)0xF7);
        /**
         *   @brief  Private Constructor - a size must be provided.
         *   @param  data is a pointer to the first byte of whats to be transmitted.
         *   @param  size is the amount of data to be transmitted.
         */
        Sequence();
        
    public:
        
        /**
         *   @brief  Constructor: fills vector with dummy sys ex messages.
         *   @param  specifies size of sequence (how many sysex are pushed).
         */
        Sequence(const int sequenceSize);
        
        /**
         *  @brief Destructor. Currently does nothing.
         */
        ~Sequence();
        
        /**
         *   @brief  Copy constructor.
         *   @param  Object to be copied.
         */
        Sequence(const Sequence & rhs);
        
        /**
         *   @brief  Copy operator.
         *   @param  Object to be copied.
         */
        Sequence& operator =(const Sequence & rhs);
        
        /**
         *   @brief  Adds the input message to the desired step.
         *   @param  message is the midi to be added to the step.
         *   @param  step is the index to the chosen step.
         */
        void addMessageToStep(const Message & message, const int step);
        
        /**
         *   @brief  Removes the input message from the desired step.
         *   @param  message is the midi to be added to the step.
         *   @param  step is the index to the chosen step.
         */
        void removeMessageFromStep(const Message & message, const int step);
        
        /**
         *   @brief  Getter for the sequence container.
         *   @return The sequence array.
         */
        std::vector<Step> getSequence() const;
        
        /**
         *   @brief  Getter for the size of our sequence.
         *   @return the size of our sequence..
         */
        int size() const;
        
        /**
         *   @brief Clears all the values in the sequence to original dummy sys ex's.
         */
        void reset();
        
    };
    
}// namespace midi
}// namespace pcaudio
