/**
 *  @file    VirtualMidiInOut.cpp
 *  @author  Corey Ford
 *  @date    28/06/2018
 *  @version 2.0
 *
 *  @brief Implemention for the VirtualMidiOutput class.
 *
 *  @section DESCRIPTION
 *
 *  This class implements functions to create a virtual midi output and input
 *   built on an instance of Jack's UART code. @see ../uart.hpp
 *
 */

#include "midi/VirtualMidiInOut.hpp"

namespace pcaudio{
namespace midi{
    
    VirtualMidiInOut::VirtualMidiInOut(UART* uart) : uart_(uart){
    }
    
    VirtualMidiInOut::~VirtualMidiInOut(){}
    
    VirtualMidiInOut::VirtualMidiInOut(const VirtualMidiInOut& rhs){
        if (this != &rhs) {
            uart_ = rhs.uart_;
        }
    }
    
    VirtualMidiInOut& VirtualMidiInOut::operator=(const VirtualMidiInOut& rhs){
        if (this != &rhs) {
            uart_ = rhs.uart_;
        }
        
        return *this;
    }
    
    void VirtualMidiInOut::sendMessage( const uint8_t *data, size_t size ){
        uart_->write(data, size);
    }

    void VirtualMidiInOut::sendMessage( const Message message ){
            const uint8_t *data = message.getData();
            const size_t size = message.getSize();
            
            uart_->write(data, size*sizeof(uint8_t));
    }
    
    //TODO(corey2.ford@live.uwe.ac.uk): test this works
    //TODO(corey2.ford@live.uwe.ac.uk): see it it works with bens isSysEx or isCC functions, probably should just
                                                        //didn't spot these earlier on.
    Message VirtualMidiInOut::recieveMessage()
    {
        //constants of comparable status bit information
        static const uint8_t sysEx_start_byte = 0xF0;
        static const uint8_t sysEx_end_byte = 0xF7;
        static const uint8_t program_change_nibble = 0b1100;
        static const uint8_t channel_pressure_nibble = 0b1101;

        std::vector<uint8_t> data; ///< create data storage
        uint8_t input = uart_->read(); ///< read the 1st byte
        
        if(input == sysEx_start_byte){
            
            while(input != sysEx_end_byte){ ///< wait until the end byte arrives
                
                data.push_back(input);
                input = uart_->read();
                
            }
            
            data.push_back(input); ///< include the end byte
            
            Message recieved_message(&data[0], data.size()); ///< create sys-ex
            return recieved_message;
        }
        else if ( (input >> 4) == program_change_nibble || (input >> 4) == channel_pressure_nibble ){
            data.push_back(input); // add this byte
            data.push_back(uart_->read()); // add the next byte
            
            Message recieved_message(data[0], data[1]); // create 2 byte midi message
            return recieved_message;
        }

        /// If we've reached here it must be a 3 byte message!!!
        data.push_back(input);
        for(int i = 0; i < 2; i++){
            data.push_back(uart_->read());
        }
        
        Message recieved_message(data[0], data[1], data[2]);
        return recieved_message;
    }

}// namespace midi
} // namespace pcaudio
