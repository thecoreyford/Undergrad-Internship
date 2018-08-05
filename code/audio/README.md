# Audio Classes

### Audio Process
The audio process class is used to wrap the exported FAUST classes and simplify
access to modifyed buffers.

To generate the samples of say a sine wave...

```C++
// include classes
#include <audio/AudioProcess.hpp>
#include <audio/FaustExports/SineOsc.cpp> 

// create a new object, passing the DSP as a template argument!
pcaudio::AudioProcess<SineOsc> signalGenerator;

// retrive a pointer to the buffer within audio process like this...
auto frame = signalGenerator.getBuffer();

// you can then iterate through a frame sample by sample
for(int i = 0; i < kFrames; i++){
frame->buffers()[0][i];
//... and do what you like
}

// you would then want to update for the next set of frames
signalGenerator.updateFrames();

```
If you were using a DSP object that dosen't generate an input (such as Delays.cpp), then you would want to add your input signal to the buffer first and then call...

```C++
signalGenerator.updateFrames(frame->buffers());
```
... with the overidden parameter of the current buffer as is. 
However, this hasn't been tested yet. //TODO

### GPIOUI
The GPIOUI class inherits fausts UI class so its possible to interface with the 
audio boards pins.

```C++
// include classes
#include <audio/GPIOUI.hpp>

// To incorporateUI you need to know the labels from the faust program.
// for this example we will change "Frequency"...

// so lets make a new UI...
pcaudio::GPIOUI* control = new pcaudio::GPIOUI;

// ... and incorporate it into controlling the signal generator
signal.incorporateUI(control);

// now you can use the UI class to change values... i.e.
control->setInputValue("Frequency", 880); //< where Frequency is the label from the faust program and 880 is the new values

// I could then iterate through frames again and get a different frequency. 
```

There are a set of functions ready to tryout with the gpio.hpp library:

```C++
// List of interfacing functions for GPIOUI class. 
double getInputValue(const char* ID) const;
void setInputValue(const char* ID, const double newValue);
void setInputValueToGPIO(const char* ID, const DigitalIn & gpio);
void setInputValueToGPIO(const char* ID, const Button & gpio);
void setInputValueToGPIO(const char* ID, const AnalogIn & gpio);
```
These were never tested due to no codec, but would love to see if they can end up working.

Corey Ford 
corey2.ford@live.uwe.ac.uk
