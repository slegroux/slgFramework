/*!
 *  (c) 2013 Sylvain Le Groux <slegroux@ccrma.stanford.edu>
 */

#include "slgAudioFile.h"

slgAudioFile::slgAudioFile(std::string path){
    path_ = path;
    SndfileHandle sfh(path_);
    sr_ = sfh.samplerate();
    channels_ = sfh.channels();
    format_ = sfh.format();
    n_frames_ = sfh.frames();
    duration_ = (float) n_frames_ / sr_ ;
    buffer_ = new float[n_frames_];
    memset(buffer_, 0, n_frames_);
    sfh.read(buffer_, n_frames_);
}

slgAudioFile::~slgAudioFile(){
    delete[] buffer_;
}

float* slgAudioFile::buffer(){
    return(buffer_);
}

int slgAudioFile::size(){
    return(n_frames_);
}

float slgAudioFile::duration(){
    return(duration_);
}

void slgAudioFile::Info(){
    cout<<"Path: "<<path_<<endl;
    cout<<"SR: "<<sr_<<endl;
    cout<<"Ch: "<<channels_<<endl;
    cout<<"#frames: "<<n_frames_<<endl;
    cout<<"Duration: "<<duration_<<endl;
    cout<<"Format: "<<hex<<format_<<endl;
}

void slgAudioFile::Write2Csv(std::string path){
    std::ofstream os(path);
    for (int i=0; i<(n_frames_-1);i++){
        os<<buffer_[i]<<',';
    }
    os<<buffer_[n_frames_ - 1];
}