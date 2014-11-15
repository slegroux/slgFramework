#include "Blit.h"
#include "ADSR.h"
#include "JCRev.h"

class Synthesizer
{
public:
    Synthesizer()
    {
        m_rev = stk::JCRev( 10 );
        m_blit.setFrequency( 220.0 );
        m_adsr.setAllTimes( 0.1, 0.1, 0.9, 0.01 );
        m_blit.setHarmonics( 10 );
    }
    
    SAMPLE Tick()
    {
        return m_rev.tick( m_adsr.tick() * m_blit.tick() );
    }
    
    void NoteOn( float freq )
    {
        m_blit.setFrequency( freq );
        m_adsr.keyOn();
    }

    void NoteOff()
    {
        m_adsr.keyOff();
    }
    
    void SetHarmonics( unsigned int harms )
    {
        m_blit.setHarmonics(harms);
    }

private:
    stk::Blit m_blit;
    stk::ADSR m_adsr;
    stk::JCRev m_rev;
};
