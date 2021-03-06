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

namespace slg{
class slgAudioFile{
    public:
        slgAudioFile();
        ~slgAudioFile();
        float * Read(std::string path);
        void Write(std::string path, float* buffer, int format, int channels, int sr);
        void Info();
        void Write2Csv(std::string path);
        // get/set-ters
        float* buffer();
        void set_buffer(float *buffer);
        float duration();
        int sr();
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
}