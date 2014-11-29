#  slgFramework
Sylvain Le Groux 2013


## About

A repository of cross-platform (only thoroughly tested on OS X for now) C++ classes for real-time audio, midi, and graphics processing.

A set of examples illustrate the use of each class with simple applications for audio, midi, graphics, GUI, etc.


######GRAPHICS
* slg2D (2D graphics)
* slg3D (3D graphics)
* slgGL (Open GL examples)
* slgCamera (controls camera in 3D)

######GUI
* slgGUI (GUI widget directly in opengl)
* slgCocoa (integrating C++ classes with Cocoa GUI)

######AUDIO
* slgAudio (Audio input/output)
* slgOsc (audio oscillator)
* slgFFTW (Fast Fourier Transform)

######MIDI
* slgMidi (MIDI input/output)
* slgFluidsynth (create a synthesizer that uses soundfonts)

#####ALL TOGETHER
* slgAudioscope (Integration of audio + graphics visualization)
* slgStk (use stk physical models to create a midi synthesizer)



## Dependencies
* **Linux:** need to install jack-audio dev
* **OS X:** developer tools


## Compilation
In each slg\<Name> subdirectory

make

./test

## License
GPL License included

##Email
<slegroux@stanford.edu>

