/*
    LosslessJpegCrop
    This class is a part of LosslessJpegCrop
    Copyright(C) 2018 Rupesh Sreeraman
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
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
    unsigned long  m_nCroppedJpegBufSize;
};

#endif // LOSSLESSJPEGCROP_H
