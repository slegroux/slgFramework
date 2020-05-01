/*!
 *  (c) 2013 Sylvain Le Groux <slegroux@ccrma.stanford.edu>
 */

#include "slgAudioFile.h"

using namespace slg;

slgAudioFile::slgAudioFile(){

}

slgAudioFile::~slgAudioFile(){
    delete[] buffer_;
}

float* slgAudioFile::Read(string path){
    path_ = path;
    SndfileHandle sfh(path_);
    sr_ = sfh.samplerate();
    channels_ = sfh.channels();
    format_ = sfh.format();
    n_frames_ = sfh.frames();
    duration_ = (float) n_frames_ / sr_ ;
    buffer_ = new float[n_frames_ * channels_];
    memset(buffer_, 0, n_frames_ * channels_);
    sfh.read(buffer_, n_frames_);
    return(buffer_);
}

void slgAudioFile::Write(string path, float* buffer, int format, int channels, int sr){
    SndfileHandle file;
    format_ = format;
    channels_ = channels;
    sr_ = sr;
    file = SndfileHandle(path,SFM_WRITE,format_, channels_, sr_);
    buffer_ = new float[n_frames_ * channels_];
    memset(buffer_, 0, n_frames_ * channels_);
    buffer_ = buffer;
    file.write(buffer_, n_frames_*channels_);
}

float* slgAudioFile::buffer(){
    return(buffer_);
}

void slgAudioFile::set_buffer(float *buffer){
    buffer_ = buffer;
}

int slgAudioFile::size(){
    return(n_frames_*channels_);
}

float slgAudioFile::duration(){
    return(duration_);
}

int slgAudioFile::sr(){
    return(sr_);
}

void slgAudioFile::Info(){
    cout<<"Path: "<<path_<<endl;
    cout<<"SR: "<<sr_<<endl;
    cout<<"Ch: "<<channels_<<endl;
    cout<<"#frames: "<<n_frames_<<endl;
    cout<<"Duration: "<<duration_<<endl;
    //cout<<"Format: "<<hex<<format_<<endl;
}

void slgAudioFile::Write2Csv(std::string path){
    std::ofstream os(path);
    for (int i=0; i<(n_frames_-1);i++){
        os<<buffer_[i]<<',';
    }
    os<<buffer_[n_frames_ - 1];
}