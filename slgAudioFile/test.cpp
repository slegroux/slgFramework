/*!
 *  (c) 2013 Sylvain Le Groux
 *  <slegroux@ccrma.stanford.edu>
 */

#include "slgAudioFile.h"
using namespace slg;

int main(int argc, char *argv[]){
    std::string path = "../data/test.wav";
    slgAudioFile af;
    af.Read(path);
    af.Info();
    cout<<af.duration()<<endl;
    af.Write2Csv("/tmp/test.txt");
    ofstream os("/tmp/test2.txt");
    for (int i=0; i<(af.size()-1);i++){
        os<<af.buffer()[i]<<',';
    }
    os<<af.buffer()[af.size()-1];
    float *buffer = new float[af.size()];
    memcpy(buffer, af.buffer(), af.size()*sizeof(float));
    for (int i=0; i< af.size(); i++){
        buffer[i] = 0.8 * af.buffer()[i];
    }
    af.Write("/tmp/testwrite.aif", \
        buffer, SF_FORMAT_AIFF | SF_FORMAT_PCM_32, 1, 16000);
    return(0);
}