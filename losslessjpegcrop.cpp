#include "losslessjpegcrop.h"

LosslessJpegCrop::LosslessJpegCrop()
{

    m_nCroppedJpegBufSize=0;
    m_nJpegFileSize=0;
}
LosslessJpegCrop::~LosslessJpegCrop()
{
    cout<<endl<<"clear"<<endl;
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
    /*lossless crop is restricted by the current JPEG format;
    the upper left corner of the selected region must fall on
    an iMCU( Minimum Coded Unit) boundary. If it doesn’t, then it is silently moved
    up and/or left to the nearest iMCU boundary
    (the lower right corner is unchanged.)
    //nx and ny must be multiple of 16*/

    int nxRem=nX%16;
    nX-=nxRem;
    //adjust width
    nWidth+=nxRem;
    //nWidth=AdjustMCUboundary(nX,nWidth);
    //nHeight=AdjustMCUboundary(nY,nHeight);
    int nyRem=nY%16;
    nY-=nyRem;
    //adjust height
    nHeight+=nyRem;

    cout<<nX<<" : "<<nY<<" xdelta :"<<nxRem<<" ydelta :"<< nyRem<<endl;
    cout<<nWidth<<" : "<<nHeight<<endl;

    tjtransform oTjTransform;
    oTjTransform.r.h=nHeight;
    oTjTransform.r.w=nWidth;
    oTjTransform.r.x=nX;
    oTjTransform.r.y=nY;
    oTjTransform.op=TJXOP_NONE;
    oTjTransform.customFilter=NULL;
    oTjTransform.data=NULL;
    oTjTransform.options=TJXOPT_CROP|TJXOPT_TRIM;

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
