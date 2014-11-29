#ifndef __MYFLUIDSYNTH_H__
#define __MYFLUIDSYNTH_H__

#include "fluidsynth.h"
#include "Definitions.h"


class slgFluidSynth
{
public:
	// constructor
	//slgFluidSynth() : m_settings(NULL), m_synth(NULL) { }
	
	// initialization
	slgFluidSynth( int srate);
	~slgFluidSynth();

	// load a font
	bool Load( const char * filename );
	
	// program change
	void ProgramChange( int channel, int program );
	
	// noteOn
	void NoteOn( int channel, int pitch, int velocity );
	
	// noteOff
	void NoteOff( int channel, int pitch );
	
	// synthesize (stereo)
	bool Render(SAMPLE * buffer, unsigned int numFrames);

private:
    
	fluid_settings_t * m_settings;
	fluid_synth_t * m_synth;
};



#endif