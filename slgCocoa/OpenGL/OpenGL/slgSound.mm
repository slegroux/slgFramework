//
//  Sound.m
//  OpenGL
//
//  Created by Sylvain Le Groux on 11/19/14.
//  Copyright (c) 2014 Sylvain Le Groux. All rights reserved.
//

#import "slgSound.h"

int AudioCallback( void * outputBuffer, void * inputBuffer,
                  unsigned int nFrames, double streamTime,
                  RtAudioStreamStatus status, void * userData )
{
    SAMPLE * out = (SAMPLE *)outputBuffer;
    SAMPLE * in = (SAMPLE *)inputBuffer;
     
    SAMPLE *audio_frame =(SAMPLE*)userData;
     //memset(g_buffer,0,g_bufferSize*sizeof(SAMPLE));
     //memset(g_audio_frames,0,kFrameSize*sizeof(SAMPLE));
    //memset(out,0,nFrames*sizeof(SAMPLE));
     
     //g_mutex.lock();
    int var=0;
    switch (var){
        case 0:
            for (int i=0;i<nFrames;i++){
                 out[i] = 0.7*::sin( 2 * M_PI * 300 * streamTime / kSampleRate);
            }
            break;
        case 1:
            for (int i=0;i<kFrameSize;i++){
                 //out[i] = in[i*kNumChannels];
            }
            break;
        }

    //g_mutex.unlock();
    
    return 0;
}

@implementation slgSound{
    double _toto;
}

-(id)init{
    self=[super init];
    if(self){
        self.g_audio_frames = NULL;
        self.g_audio_frames = new SAMPLE[kFrameSize];
        
        self.g_audio = new slgAudio(kNumChannels,kSampleRate,kFrameSize);
        self.g_audio->openStream(&AudioCallback,self.g_audio_frames);
        self.g_audio->info();
        
    }
    return(self);
}

-(void)startSound{
    NSLog(@"Start sound");
    self.g_audio->startStream();
}

-(void)stopSound{
    NSLog(@"Stop sound");
    self.g_audio->stopStream();
}

@end
