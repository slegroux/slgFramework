#ifndef __SLGONEPOLE_H__
#define __SLGONEPOLE_H__


#include "slgFilter.h"

class slgOnePole : public slgFilter{
public:
    slgOnePole();
    ~slgOnePole();

public:
    void clear();
    void setPole(float aValue);
    void setGain(float aValue);
    SAMPLE tick(SAMPLE sample);

protected:  
    float m_poleCoeff;
    float m_sgain;
};

#endif
