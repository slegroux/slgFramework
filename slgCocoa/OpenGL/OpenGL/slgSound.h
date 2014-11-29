//
//  Sound.h
//  OpenGL
//
//  Created by Sylvain Le Groux on 11/19/14.
//  Copyright (c) 2014 Sylvain Le Groux. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "slgAudio.h"
#include <string>
using namespace std;

//extern enum InputMode {kSine,kInput};
//extern InputMode g_inputSignal = kInput;
//SAMPLE* g_audio_frames;
//extern std::string my_string;

@interface slgSound : NSObject

@property slgAudio *g_audio;
@property SAMPLE* g_audio_frames;

-(void)startSound;
-(void)stopSound;
//-(id)init

@end
