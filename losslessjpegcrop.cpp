#include "losslessjpegcrop.h"

LosslessJpegCrop::LosslessJpegCrop()
{

    m_nCroppedJpegBufSize=0;
    m_nJpegFileSize=0;
}
LosslessJpegCrop::~LosslessJpegCrop()
{

    cout<<"dleted";
    if (m_jpegBuffer)
        delete[] m_jpegBuffer;
    if (m_CroppedJpegBuf)
        delete[] m_CroppedJpegBuf;

}

bool LosslessJpegCrop::LoadJpeg(string strPath)
{
    FILE * oJpegFile =NULL;
    oJpegFile  = fopen(strPath.c_str(), "rb");
    if(!oJpegFile)
    {
        return false;
    }

    //Get file size
    fseek(oJpegFile,0,SEEK_END);
    m_nJpegFileSize=ftell(oJpegFile);
    fseek(oJpegFile,0,SEEK_SET);

    m_jpegBuffer=new unsigned char[m_nJpegFileSize]();
    int nBytesRead = fread((unsigned char*)m_jpegBuffer, sizeof(unsigned char), m_nJpegFileSize, oJpegFile);

    if(nBytesRead!=m_nJpegFileSize)
    {
        fclose(oJpegFile);
        return false;
    }


   fclose(oJpegFile);
   return true;

}
bool LosslessJpegCrop::DoCrop(int nWidth,int nHeight,int nX,int nY)
{
    tjtransform oTjTransform;
    oTjTransform.r.h=nWidth;
    oTjTransform.r.w=nHeight;
    oTjTransform.r.x=nX;
    oTjTransform.r.y=nY;
    oTjTransform.op=TJXOP_NONE;
    oTjTransform.customFilter=NULL;
    oTjTransform.data=NULL;
    oTjTransform.options=TJXOPT_CROP|TJXOPT_PERFECT;

    tjhandle oTurboJpeg = tjInitTransform();
    int nRes =tjTransform(oTurboJpeg,m_jpegBuffer,m_nJpegFileSize,
                1,&m_CroppedJpegBuf,&m_nCroppedJpegBufSize,&oTjTransform,
                TJFLAG_ACCURATEDCT);

    m_strError =string(tjGetErrorStr2(oTurboJpeg));
    if (nRes!=0)
        return false;
    else
        return true;


}
bool LosslessJpegCrop::SaveCroppedJpeg(string strPath)
{
    std::ofstream outJpeg(strPath.c_str(),std::ofstream::binary);
    outJpeg.write ((char*)m_CroppedJpegBuf,m_nCroppedJpegBufSize);
    outJpeg.close();

}
