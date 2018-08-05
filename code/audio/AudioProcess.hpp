/**
 *  @file    AudioProcess.hpp
 *  @author  Corey Ford
 *  @date    8/06/2018
 *  @version 2.0
 *
 *  @brief Wraps faust dsp classes for frame by frame processing, and connection
 *  with the GPIOUI layer.
 *
 *  @section DESCRIPTION
 *
 *  This is a template class that wraps a faust generated dsp class and
 *  the GPIOUI class, giving a simplified syntax.
 *
 *  It is designed to work with @see faust/audio/channels.h, retreving and
 *  computing frames of X size (512 is fausts generated default).
 *
 *  Was previously FaustLinker.cpp - refactored for readability.
 */

//TODO(corey2.ford@live.uwe.ac.uk): refactor with smart pointers? (it was easier
//                                  to hack together with raw)!

#pragma once

#include <iostream> ///< required for library 'channels.h'
#include "faust/audio/channels.h"
#include <audio/GPIOUI.hpp>

#define kFrames 128  // 512 //FAUST default
#define sampleRate 16000 // 44100 //FAUST default

namespace pcaudio{

    template <class DSP>
    class AudioProcess{
    private:
        channels* chan; ///<Points the buffer object.
        DSP signal; ///< Create an object of our templated type
        int noOfOutputs; ///< Stores the number of outputs
        
    public:

        /**
        *   @brief  Constructor. Initialises variables from DSP class, 
        *           and allocates a buffer.
        */
        AudioProcess(){
            //intialise DSP member functions
            signal.init(sampleRate);
            noOfOutputs = signal.getNumOutputs();
            
            //initialise buffer frames
            chan = new channels(kFrames, noOfOutputs);
            updateFrames(); //update an initial set of frames. 
        }

        /**
        *   @brief Dealloctes buffer memory.
        */
        ~AudioProcess(){
            delete chan;
        }

        /**
          *   @brief  Emptys the buffer, then fills with next set of computed values.
          */
        void updateFrames(){
            chan->zero();
            signal.compute(kFrames, 0, chan->buffers());
        }
        
        /**
         *    @brief updates frames for audio processes that require an input 
         *          (e.g. delay or distortion).
         *    @param  the current input buffer
         */
        void updateFrames(float** input){
            signal.compute(kFrames, input, chan->buffers());
            //TODO(corey2.ford@live.uwe.ac.uk): test this with a DSP example.
        }

        /**
          *  @brief  Used for getting access to this processes buffer.
          * @return  Returns the pointer to the private buffer object.
        */
        channels* getBuffer(){
            return chan;
        }

        /**
          *   @brief  Wraps building the UI interface for the DSP object.
          */
        // This is important to be done seperatly to this class so that these
        // controls can be changed at runtime: possibly via callbacks.
        void incorporateUI(GPIOUI* interface) {
            signal.buildUserInterface(interface);
        }
    };
    
} // namespace pcaudio
