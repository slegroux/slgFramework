#include "slgFluidSynth.h"
//#include <iostream.h>
#include <stdio.h>
#include "defs.h"

// initialization
slgFluidSynth::slgFluidSynth( int srate){  
    printf("---------FLUIDSYNTH------------\n");
    /*if( m_synth != NULL )
    {
        printf( "synth already initialized...\n");
        //return false;
    }*/
    m_synth = NULL;
    m_settings = NULL;
    
    // log
    printf( "Initializing synth...\n" );
    
    // instantiate settings
    m_settings = new_fluid_settings();
    
    fluid_settings_setint(m_settings, (char *)"synth.polyphony", 32);
    
    // set sample rate
    fluid_settings_setnum( m_settings, (char *)"synth.sample-rate", (double)srate );
	
    // turn on a chorus effect
    //fluid_settings_setstr( m_settings, (char *)"synth.chorus.active", (char *)"yes" );
    
    fluid_settings_setnum( m_settings, (char *)"audio.period-size", (double)BUFFER_SIZE );
    
    // instantiate the synth
    m_synth = new_fluid_synth( m_settings );
    
    //this->load( filename );
    //return m_synth != NULL;
}

slgFluidSynth::~slgFluidSynth(){
    // clean up
    if( m_synth ) delete_fluid_synth( m_synth );
    if( m_settings ) delete_fluid_settings( m_settings );
    m_synth = NULL;
    m_settings = NULL;
    printf("cleanup fluidsynth\n");
}

// load a font
bool slgFluidSynth::Load( const char * filename )
{
    if( m_synth == NULL ) 
        return false;
    
    if( fluid_synth_sfload( m_synth, filename, true ) == -1 )
    {
        // error
        printf("cannot load font file: %s\n", filename );
        return false;
    }

    printf("Loaded soundfont %s\n",filename);
	    
    return true;
}

// program change
void slgFluidSynth::ProgramChange( int channel, int program )
{
    if( m_synth == NULL ) return;
    if( program < 0 || program > 127 ) return;
    fluid_synth_program_change( m_synth, channel, program );
}

// noteOn
void slgFluidSynth::NoteOn( int channel, int pitch, int velocity )
{
    // sanity check
    if( m_synth == NULL ) return;
    // integer pitch
    int pitch_i = (int)(pitch + .5f);
    // difference
    float diff = pitch - pitch_i;
    // if needed
    if( diff != 0 )
    {
        // pitch bend
        fluid_synth_pitch_bend( m_synth, channel, (int)(8192 + diff * 8191) );
    }
    // sound note
    fluid_synth_noteon( m_synth, channel, pitch, velocity );
}

// noteOff
void slgFluidSynth::NoteOff( int channel, int pitch )
{
    if( m_synth == NULL ) return;
    fluid_synth_noteoff( m_synth, channel, pitch );
}

// synthesize (stereo)
bool slgFluidSynth::Render( SAMPLE * buffer, unsigned int numFrames )
{
    if( m_synth == NULL ) return false;
    // get it from fluidsynth
    int retval = fluid_synth_write_float( m_synth, numFrames, buffer, 0, 2, buffer, 1, 2 );
    return retval == 0;
}
