/*!
 *  (c) 2013 Sylvain Le Groux
 *  <slegroux@ccrma.stanford.edu>
 */

#include "slgAudioFile.h"

int main(int argc, char *argv[]){
    std::string path = "../data/test.wav";
    slgAudioFile af(path);
    af.Info();
    cout<<af.duration()<<endl;
    af.Write2Csv("/tmp/test.txt");
    ofstream os("/tmp/test2.txt");
    for (int i=0; i<(af.size()-1);i++){
        os<<af.buffer()[i]<<',';
    }
    os<<af.buffer()[af.size()-1];
    return(0);
}