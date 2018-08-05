/**
 *  @file    GPIOUI.h
 *  @author  Corey Ford
 *  @date    13/06/2018
 *  @version 2.0
 *
 *  @brief Header file for the interface between the GPIO's and faust DSP.
 *
 *  @section DESCRIPTION
 *
 *  This extends the faust UI class to be used with the audio development board.
 *  @see AudioProcess.hpp 's incorporateUI() function to see how would be
 *      linked to values at runtime.
 */

#pragma once

#include "faust/gui/UI.h"
#include <semihost.hpp>
#include <gpio.hpp>

#define MAX_PINS 30

namespace pcaudio{

    class GPIOUI : public UI{
    private:
        
        //======================================================================
        
        /**
         *   @brief  Returns the current index matching the FAUST label.
         *   @param  ID is a c-string corresponding to the FAUST label initialised.
         *   @return The index position for the given string.
         */
        int findIndexForID(const char* ID) const;
        
        /**
         *   @brief  Finds the next avalible input and stores the parsed value.
         *   @param  label is the ID of the slider - used to identify throughout this class
         *   @param  zone is a pointer to the value in the faust DSP class being varied by the slider value
         */
        void addToNextFreeInput(const char* label, FAUSTFLOAT* zone);
        
        //======================================================================
        
        struct Control{
            const char* ID;
            float* currentValue;
        }; ///< Object for ID (matching faust label) and pointer to the DSP codes widget variable.
        
        Control input[MAX_PINS]; /// < Storage for all the initialised inputs.
        
    public:
        //======================================================================

        /**
          *   @brief  Constructor. All inputs are intialised to point to null.
          */
        GPIOUI();

        /**
          *   @brief  Destructor, virtual.
          */
        virtual ~GPIOUI();

        //======================================================================

        /** @brief  Faust virual widget layout code. Unused. */
        virtual void openTabBox(const char* label) override;
        /** @brief  Faust virual widget layout code. Unused. */
        virtual void openHorizontalBox(const char* label) override;
        /** @brief  Faust virual widget layout code. Unused. */
        virtual void openVerticalBox(const char* label) override;
        /** @brief  Faust virual widget layout code. Unused. */
        virtual void closeBox() override;

        //======================================================================

        /**
         *   @brief  Stores button used in the loaded faust program called via incorporateUI
         *              in the AudioProcess class.
         *   @param  label is the ID of the button - used to identify throughout this class
         *   @param  zone is a pointer to the value in the checkboxvaluesfaust DSP class being
                        varied by the button value
         */
        virtual void addButton(const char* label, FAUSTFLOAT* zone) override;
        
        /**
         *   @brief  Stores checkboxvalues used in the loaded faust program called via incorporateUI
         *              in the AudioProcess class.
         *   @param  label is the ID of the checkbox - used to identify throughout this class
         *   @param  zone is a pointer to the value in the faust DSP class being varied by the checkbox value
         */
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) override;

        /**
         *   @brief  Stores vertical sliders used in the loaded faust program called via incorporateUI
         *              in the AudioProcess class.
         *   @param  label is the ID of the slider - used to identify throughout this class
         *   @param  zone is a pointer to the value in the faust DSP class being varied by the slider value
         *   @param  init is the starting value for the slider
         *   @param  min is the lowest possible value for the slider
         *   @param  max is the largest possible value for the slider
         *   @param  step is the increment between points on the slider
         */
        virtual void addVerticalSlider(const char* label,
                                        FAUSTFLOAT* zone,
                                        FAUSTFLOAT init,
                                        FAUSTFLOAT min,
                                        FAUSTFLOAT max,
                                        FAUSTFLOAT step) override;

        /**
         *   @brief  Stores horizontal sliders used in the loaded faust program called via incorporateUI
         *              in the AudioProcess class.
         *   @param  label is the ID of the slider - used to identify throughout this class
         *   @param  zone is a pointer to the value in the faust DSP class being varied by the slider value
         *   @param  init is the starting value for the slider
         *   @param  min is the lowest possible value for the slider
         *   @param  max is the largest possible value for the slider
         *   @param  step is the increment between points on the slider
         */
        virtual void addHorizontalSlider(const char* label,
                                            FAUSTFLOAT* zone,
                                            FAUSTFLOAT init,
                                            FAUSTFLOAT min,
                                            FAUSTFLOAT max,
                                            FAUSTFLOAT step) override;

        /**
         *   @brief  Stores num entry box used in the loaded faust program called via incorporateUI
         *              in the AudioProcess class.
         *
         *   @param  label is the ID of the box - used to identify throughout this class
         *   @param  zone is a pointer to the value in the faust DSP class being varied by the box value
         *   @param  init is the starting value for the box
         *   @param  min is the lowest possible value for the box
         *   @param  max is the largest possible value for the box
         *   @param  step is the increment between points for the box
         */
        virtual void addNumEntry(const char* label,
                                    FAUSTFLOAT* zone,
                                    FAUSTFLOAT init,
                                    FAUSTFLOAT min,
                                    FAUSTFLOAT max,
                                    FAUSTFLOAT step) override;

        //======================================================================

        /** @brief  Faust virual  passive widget code. Unused. */
        virtual void addHorizontalBargraph(const char* label,
                                           FAUSTFLOAT* zone,
                                           FAUSTFLOAT min,
                                           FAUSTFLOAT max) override;
        
        /** @brief  Faust virual  passive widget code. Unused. */
        virtual void addVerticalBargraph(const char* label,
                                         FAUSTFLOAT* zone,
                                         FAUSTFLOAT min,
                                         FAUSTFLOAT max) override;

        //======================================================================

        /** @brief  Faust soundfile inclusion code. Unused. */
        virtual void addSoundfile(const char* label,
                                  const char* filename,
                                  Soundfile** sf_zone) override;

        //======================================================================
        
        //TODO(corey2.ford@live.uwe.ac.uk): these were never tested due to no
        //                                  codec, but would love to see if
        //                                  they can end up working.

        /**
         *   @brief  Returns the current value of the given input.
         *   @param  ID is a c-string corresponding to the FAUST label initialised.
         *   @return The current value fot the input asked for.
         */
        double getInputValue(const char* ID) const;

        /**
         *   @brief  Sets the given input to a new parsed value.
         *   @param  ID is a c-string corresponding to the FAUST label initialised.
         *   @param  newValue is the value in which the input will be updated to.
         */
        void setInputValue(const char* ID, const double newValue);

        /**
         *   @brief  Sets the given input to the value read from a digital input gpio.
         *   @param  ID is a c-string corresponding to the FAUST label initialised.
         *   @param  gpio is the digital input that will control this input.
         */
        void setInputValueToGPIO(const char* ID, const DigitalIn & gpio);
    
        /**
         *   @brief  Sets the given input to the value depending on a button state.
         *   @param  ID is a c-string corresponding to the FAUST label initialised.
         *   @param  gpio is the digital output that will control this input.
         */
        void setInputValueToGPIO(const char* ID, const Button & gpio);
        
        /**
         *   @brief  Sets the given input to the value depending on a analouge input.
         *   @param  ID is a c-string corresponding to the FAUST label initialised.
         *   @param  gpio is the analouge output that will control this input.
         */
        void setInputValueToGPIO(const char* ID, const AnalogIn & gpio);

        //======================================================================
    };

} // namespace pcaudio
