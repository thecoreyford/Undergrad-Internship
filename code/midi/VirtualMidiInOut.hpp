/**
 *  @file    VirtualMidiOut.hpp
 *  @author  Corey Ford
 *  @date    28/06/2018
 *  @version 2.0
 *
 *  @brief A class for sending midi-messages via a UART connection.
 *
 *  @section DESCRIPTION
 *
 *  This class implements functions to create a virtual midi output and input
 *   built on an instance of Jack's UART code. @see ../uart.hpp
 *
 */

#pragma once

#include <uart.hpp>
#include <midi/message.hpp>
#include <vector>

namespace pcaudio{
namespace midi{
        
    class VirtualMidiInOut{
    private:
        /**
        *   @brief  Private constructor - UART must be provided.
        */
        VirtualMidiInOut();
        
        UART* uart_; ///< access to the board connection

    public:
        
        /**
         *   @brief  Initliases the UART connection
         *   @param  A reference to the initialised uart connection.
         */
        VirtualMidiInOut(UART* uart);
            
        /**
         *   @brief  Copy constructor.
         *   @param  The object to be copied.
         */
        VirtualMidiInOut(const VirtualMidiInOut & rhs);
            
        /**
         *   @brief  Copy operator
         *   @param  The object to be copied.
         */
        VirtualMidiInOut& operator =(const VirtualMidiInOut & rhs);
            
        /**
         *   @brief  Destructor. Cleans memory from any opened pins.
         */
        ~VirtualMidiInOut();
        
        /**
         *   @brief  Writes X amount of data depending on its size to the serial connection.
         *
         *   @param  data is a pointer to the first byte of whats to be transmitted.
         *   @param  size is the amount of data to be transmitted.
         */
        void sendMessage( const uint8_t *data, size_t size );
            
        /**
         *   @brief Writes a single midi message to the serial connection.
         *
         *   @param A midi message object to be transmitted.
         */
        void sendMessage( const Message message );
                        
        /**
         *   @brief  Gets a single incoming midi message.
         *
         *   @return The midi message that was recieved.
         */
        Message recieveMessage();
            
    };
    
} // namespace midi
} // namespace pcaudio
