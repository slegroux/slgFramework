//
//  MyGLView.m
//  OpenGL
//
//  Created by Sylvain Le Groux on 11/19/14.
//  Copyright (c) 2014 Sylvain Le Groux. All rights reserved.
//

#import "MyGLView.h"
#include <OpenGL/gl.h>
#include "slgGraphics.h"
#include "slgSound.h"



@implementation MyGLView

static void drawAnObject ()
{

    //Buffer1D(g_audio_frames, kFrameSize, -1.0,1.0);
 
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawAnObject();
    glFlush();
}

@end
