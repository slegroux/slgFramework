#ifndef __SLGOSC_H__
#define __SLGOSC_H__

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"
#include <iostream>
//using namespace std;


class slgOscListener : public osc::OscPacketListener{
public:
    slgOscListener();
    ~slgOscListener();
  //  static void * cb_osc_listener( void * );
    virtual void ProcessMessage( const osc::ReceivedMessage & m, 
                                 const IpEndpointName & remoteEndpoint );
    
};

#endif