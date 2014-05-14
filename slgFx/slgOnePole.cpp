#include "slgOnePole.h"
#include "string.h"

slgOnePole :: slgOnePole() : slgFilter()
{
    m_poleCoeff = 0.9;
    m_gain = 1.0;
    m_sgain = 0.1;
    m_outputs = new SAMPLE[1];
    memset(m_outputs,0,sizeof(SAMPLE));
}

slgOnePole :: ~slgOnePole()
{
  delete m_outputs;
}

void slgOnePole :: clear()
{
    m_outputs[0] = 0;
    m_lastOutput = 0.0;
}

void slgOnePole :: setPole(float aValue)
{
    m_poleCoeff = aValue;
    if (m_poleCoeff > 0.0) /*  Normalize gain to 1.0 max */
    m_sgain = m_gain * (1.0 - m_poleCoeff);
    else
        m_sgain = m_gain * (1.0 + m_poleCoeff);
}

void slgOnePole :: setGain(float aValue)
{
    m_gain = aValue;
    if (m_poleCoeff > 0.0)
        m_sgain = m_gain * (1.0 - m_poleCoeff);
    else
        m_sgain = m_gain * (1.0 + m_poleCoeff);
}

SAMPLE slgOnePole :: tick(SAMPLE sample)  /*   Perform Filter Operation */
{
    m_outputs[0] = (m_sgain * sample) + (m_poleCoeff * m_outputs[0]);              
    m_lastOutput = m_outputs[0];
    return m_lastOutput;
}
