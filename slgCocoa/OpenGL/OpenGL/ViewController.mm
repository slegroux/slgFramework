//
//  ViewController.m
//  OpenGL
//
//  Created by Sylvain Le Groux on 11/18/14.
//  Copyright (c) 2014 Sylvain Le Groux. All rights reserved.
//

#import "ViewController.h"


@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    [_text setStringValue:@"toto"];
    [self.sound startSound];
    //std::cout<<my_string<<std::endl;
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


- (IBAction)pushed:(id)sender {
    NSLog(@"%@",[_text stringValue]);
    [_text setStringValue:@"pushed"];

}
@end
