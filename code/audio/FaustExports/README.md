# FAUST EXPORTS 

Each cpp file in this folder contains a faust cpp that has been 
generated using the audio_board.cpp architecture file.

audio_board.cpp is essensially the same as FAUST's minimal.cpp architcture file; 
however, it's stripped of the main function leaving just the dsp class.

The terminal command to generate a cpp from a FAUST .dsp looks like this:
* faust -a audio_board.cpp Delays.dsp -cn Delays -o Delays.cpp

where...

* -a specifices the architecture file followed by the DSP
* -cn is the class name you want to be generated instead of myDSP
* -o is the output file 

Each example's original FAUST code can be found here:
* https://github.com/thecoreyford/FAUST-Simples

If you want more examples you can basically just compile any fuast demo using the 
audio_board.cpp file: so go nuts. 

Corey Ford 
corey2.ford@live.uwe.ac.uk
