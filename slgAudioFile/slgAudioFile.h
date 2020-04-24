/*!
 *  (c) 2013 Sylvain Le Groux <slegroux@ccrma.stanford.edu>
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sndfile.hh>

using namespace std;
using std::cout;
using std::endl;

class slgAudioFile{
    public:
        slgAudioFile();
        ~slgAudioFile();
        float * Read(std::string path);
        void Write(std::string path);
        void Info();
        void Write2Csv(std::string path);
        float* buffer();
        float duration();
        int size();

    private:
        std::string path_;
        float *buffer_;
        int sr_;
        int channels_;
        int format_;
        int n_frames_;
        float duration_;
};