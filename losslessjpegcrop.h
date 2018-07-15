#ifndef LOSSLESSJPEGCROP_H
#define LOSSLESSJPEGCROP_H

#include <string.h>
#include <iostream>
#include <fstream>
#include "include/turbojpeg.h"

using namespace std;

class LosslessJpegCrop
{
public:
    LosslessJpegCrop();
    ~LosslessJpegCrop();
    //Load JPG
    bool LoadJpeg(string strPath);
    //Get file size
    inline long GetFileSize(){return m_nJpegFileSize;}
    //Do the crop
    bool DoCrop(int nWidth, int nHeight, int nX, int nY);
    //Get error description on LosslessCrop failure
    inline string GetCropErrString(){return m_strError;}
    //Save cropped Jpeg Image
    bool SaveCroppedJpeg(string strPath);
 private :
    string m_strError;
    long m_nJpegFileSize;
    unsigned char* m_jpegBuffer;
    unsigned char* m_CroppedJpegBuf;
    unsigned long  m_nCroppedJpegBufSize=0;
};

#endif // LOSSLESSJPEGCROP_H
