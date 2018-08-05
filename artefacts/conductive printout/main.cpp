
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2018 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

#include <midi/message.hpp>
#include <midi/note.hpp>
#include <midi/VirtualMidiInOut.hpp>
#include <midi/sequence.hpp>
//--
#include <concurrency/scheduler.hpp>
#include <concurrency/timer.hpp>
#include <concurrency/task.hpp>
//--
#include <gpio.hpp>

// Global pointers
pcaudio::UART * uart;

// Sequencer constants
const double secInMinute = 60;
const int NO_OF_PINS = 6;
const int SEQUENCER_STEPS = 4;
const int STEP_OFFSET = 2; //< where output 1 starts.

// these will, in general, be dynamic inputs in someway to the app
// pots, sliders, and so on
const double bpm = 120;
const double beats = 2;

// this allows us to spread our sequence over one or more cycles
const size_t numOfBars = 1;

/**
 * @brief  The application entry point.
 * @retval None
 */
int main(void){
    //======================================================================
    //_____________________________STEP SEQUENCER_________________________//
    /*
     *  For the following step sequencer it is assumed that the grid and
     *  pins are matched up like so.
     *      Input A  = Pin 1
     *      Input B  = Pin 2
     *      Output 1 = Pin 3
     *      Output 2 = Pin 4
     *      Output 3 = Pin 5
     *      Output 4 = Pin 6
     *  The offset constant determins where output 1 starts.
     */
    //======================================================================
    
    // Initialise Storage
    pcaudio::midi::Sequence sequencer(SEQUENCER_STEPS);
    
    // Initialise Pins
    pcaudio::GPIO<>* pins[NO_OF_PINS];
    for(int i = 0; i < NO_OF_PINS; ++i){
        if( i >= 5 ) { /* Has to be done to skip the UART on pins 6 & 7*/
            int pinValue = static_cast<int>(pcaudio::EXT_PIN::PIN_8) + (i - 5);
            pins[i] = new pcaudio::GPIO<>(static_cast<pcaudio::EXT_PIN>(pinValue));
        }
        else{
            pins[i] = new pcaudio::GPIO<>(static_cast<pcaudio::EXT_PIN>(i));
        }
    }
    
    // Initialise UART and out MidiOutput Device
    __USART6_CLK_ENABLE();
    uart = new pcaudio::UART(pcaudio::EXT_PIN::PIN_6, pcaudio::EXT_PIN::PIN_7);
    pcaudio::midi::VirtualMidiInOut midiOut(uart);
    
    // Create Midi Messages
    auto channel = pcaudio::midi::Channel::CHANNEL1;
    uint8_t velocity = 99;
    auto snare = pcaudio::midi::noteOn (channel,
                                        pcaudio::midi::NoteSym::D2,
                                        velocity);
    auto kick = pcaudio::midi::noteOn (channel,
                                       pcaudio::midi::NoteSym::C2,
                                       velocity);
    
    // Set up stepper
    auto stepper =
    pcaudio::concurrency::Task<pcaudio::concurrency::MultiTasking::COOPERATIVE_WITHOUT_YIELD,void, size_t>([&] (size_t index){
        // Clear sequencer
        sequencer.reset();
        
        // Set Input A high, B low
        pins[0]->on();
        pins[1]->off();
        
        // Store values across all steps
        for(int i = STEP_OFFSET; i < (SEQUENCER_STEPS + STEP_OFFSET); ++i){
            if(pins[i]->read() == pcaudio::PIN_STATE::SET){
                sequencer.addMessageToStep(snare, i - STEP_OFFSET);
            }
        }
        
        // Set Input B high, A low
        pins[0]->off();
        pins[1]->on();
        
        // Store values across all steps
        for(int i = STEP_OFFSET; i < (SEQUENCER_STEPS + STEP_OFFSET); ++i){
            if(pins[i]->read() == pcaudio::PIN_STATE::SET){
                sequencer.addMessageToStep(kick, i - STEP_OFFSET);
            }
        }
        
        // Play through the sequencer container
        auto sequencerContainer = sequencer.getSequence();
        for (auto & message : sequencerContainer[index]){
            midiOut.sendMessage(message);
        }
    });
    
    // this is the "scheduler" loop
    for (;;){
        pcaudio::concurrency::sequentialSchedule(
         sequencer.size(),
         stepper,
         pcaudio::concurrency::Timer<std::ratio<1,1000>>(
             // timestep of each nth note in the sequence
             (bpm / secInMinute) * 1000,
             // duration of bar
             (bpm / secInMinute / (sequencer.size() / numOfBars)) * 1000));
    }
}

//*********************************************************************************

// WE NEED this as we are now compiling C++
extern "C" void SysTick_Handler(void){
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

///**
// * @brief  This function is executed in case of error occurrence.
// * @param  file: The file name as string.
// * @param  line: The line in file as a number.
// * @retval None
// */
void _Error_Handler(char *file, int line){
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while(1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
