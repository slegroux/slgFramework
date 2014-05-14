#ifndef __SLGFILTER_H__
#define __SLGFILTER_H__
#include "Definitions.h"

class slgFilter{

public:
    slgFilter();
    virtual ~slgFilter();

public:
    SAMPLE lastOut();

protected:  
    float m_gain;
    SAMPLE *m_outputs;
    SAMPLE *m_inputs;
    SAMPLE m_lastOutput;
};

#endif
