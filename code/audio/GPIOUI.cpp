/**
 *  @file    GPIOUI.h
 *  @author  Corey Ford
 *  @date    22/06/2018
 *  @version 2.0
 *
 *  @brief Source file for the interface between the GPIO's and faust DSP.
 *
 *  @section DESCRIPTION
 *
 *  This extends the faust UI class to be used with the PCAudioBoard's
 *  custom FAUST architecture file.
 *
 */

#include <audio/GPIOUI.hpp>

namespace pcaudio{
    
    GPIOUI::GPIOUI(){
        for(int i = 0; i < MAX_PINS; i++){
            input[i].ID = nullptr;
            input[i].currentValue = nullptr;
        }
    }

    GPIOUI::~GPIOUI(){}
    
    //======================================================================
    
    void GPIOUI::openTabBox(const char* label) {}
    void GPIOUI::openHorizontalBox(const char* label) {}
    void GPIOUI::openVerticalBox(const char* label) {}
    void GPIOUI::closeBox() {}
    
    //======================================================================
    
    void GPIOUI::addButton(const char* label, FAUSTFLOAT* zone) {
        addToNextFreeInput(label, zone);
    }
    
    void GPIOUI::addCheckButton(const char* label, FAUSTFLOAT* zone) {
        addToNextFreeInput(label, zone);
    }
    
    void GPIOUI::addVerticalSlider(const char* label,
                                   FAUSTFLOAT* zone,
                                   FAUSTFLOAT init,
                                   FAUSTFLOAT min,
                                   FAUSTFLOAT max,
                                   FAUSTFLOAT step) {
        addToNextFreeInput(label, zone);
    }
    
    void GPIOUI::addHorizontalSlider(const char* label,
                                     FAUSTFLOAT* zone,
                                     FAUSTFLOAT init,
                                     FAUSTFLOAT min,
                                     FAUSTFLOAT max,
                                     FAUSTFLOAT step){
        addToNextFreeInput(label, zone);
    }
    
    void GPIOUI::addNumEntry(const char* label,
                             FAUSTFLOAT* zone,
                             FAUSTFLOAT init,
                             FAUSTFLOAT min,
                             FAUSTFLOAT max,
                             FAUSTFLOAT step) {
        addToNextFreeInput(label, zone);
    }
    
    //======================================================================
    
    void GPIOUI::addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    void GPIOUI::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max){}
    
    //======================================================================
    
    void GPIOUI::addSoundfile(const char* label, const char* filename, Soundfile** sf_zone){}
    
    //======================================================================
    

    double GPIOUI::getInputValue(const char* ID) const{
        int i = findIndexForID(ID);
        return *(input[i].currentValue);
    }
    
    void GPIOUI::setInputValue(const char* ID, const double newValue){
        int i = findIndexForID(ID);
        *input[i].currentValue = newValue;
    }
    
    void GPIOUI::setInputValueToGPIO(const char* ID, const DigitalIn & gpio){
        int i = findIndexForID(ID);
        *input[i].currentValue = (int)gpio.read();
    }
    
    void GPIOUI::setInputValueToGPIO(const char* ID, const Button & gpio)
    {
        //TODO(Corey2.Ford@live.uwe.ac.uk) Vaugley glitchy button states - not debounced.
        int i = findIndexForID(ID);
        int currentValue = 0;
        
        if(gpio.pressed() == true){
            currentValue = 1;
        }else if(gpio.held() == true){
            currentValue = 1;
        }else if(gpio.released() == true){
            currentValue = 0;
        }
        
        *input[i].currentValue = currentValue;
    }
    
    void GPIOUI::setInputValueToGPIO(const char* ID, const AnalogIn & gpio)
    {
        if(0)
        {
            //TODO(Corey2.Ford@live.uwe.ac.uk) Analouge not implemeneted yet so cannot be utilised.
//            int i = findIndexForID(ID);
//            *input[i].currentValue = gpio.read();
        }
    }
    
    
    //======================================================================
    
    int GPIOUI::findIndexForID(const char* ID) const{
        int current = 0;
        while(input[current].ID != ID){
            current++;
            if(current == MAX_PINS){
                write(2, "Pin with ID not found!\n", 24);
                return 0;
            }
        }
        return current;
    }
    
    void GPIOUI::addToNextFreeInput(const char* label, FAUSTFLOAT* zone){
        // Find the next avaliable input
        int current = 0;
        while(current < MAX_PINS){
            if(input[current].currentValue != nullptr){
                current++;
            }else{
                break;
            }
        }
        
        // Store values at this position
        input[current].ID = label;
        input[current].currentValue = zone;
    }
    
    //======================================================================
    
    
} // namespace pcaudio
