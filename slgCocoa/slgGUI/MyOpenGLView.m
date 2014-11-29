//
//  MyOpenGLView.m
//  slgGUI
//
//  Created by Sylvain Le Groux on 11/18/14.
//  Copyright (c) 2014 Sylvain Le Groux. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MyOpenGLView.h"
#include <OpenGL/gl.h>

@implementation MyOpenGLView

static void drawAnObject ()
{
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);
    }
    glEnd();
}

-(void)prepareOpenGL{
    //init_gl();
    //swap interval for double buffering
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter: NSOpenGLCPSwapInterval];
    // this enables alpha in the frame buffer (commented now)
    //  GLint opaque = 0;
    //  [[self openGLContext] setValues:&opaque forParameter:NSOpenGLCPSurfaceOpacity];
}

-(void) drawRect: (NSRect) bounds
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawAnObject();
    //glFlush();
    [[self openGLContext] flushBuffer];
}

- (void)reshape {
    NSLog(@"view reshape {%.02f %.02f}", [self frame].size.width, [self frame].size.height);
    
    // window resize; width and height are in pixel coordinates
    // but they are floats
    float screen_w = [self frame].size.width;
    float screen_h = [self frame].size.height;
    
    // here I cast floats to ints; most systems use integer coordinate systems
    //screen_resize((int)screen_w, (int)screen_h);
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)keyDown:(NSEvent *)theEvent {
    if ([theEvent isARepeat])
        return;
    
    NSString *str = [theEvent charactersIgnoringModifiers];
    unichar c = [str characterAtIndex:0];
    
    if (c < ' ' || c > '~')     // only ASCII please
        c = 0;
    
    //key_down([theEvent keyCode], c);
}

- (void)keyUp:(NSEvent *)theEvent {
    //key_up([theEvent keyCode]);
}

@end