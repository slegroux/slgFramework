//
//  ViewController.h
//  OpenGL
//
//  Created by Sylvain Le Groux on 11/18/14.
//  Copyright (c) 2014 Sylvain Le Groux. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "slgSound.h"



@interface ViewController : NSViewController

@property (weak) IBOutlet NSTextField *text;
@property slgSound *sound;

- (IBAction)pushed:(id)sender;


@end

