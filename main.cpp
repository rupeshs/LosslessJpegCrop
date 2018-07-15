#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include "include/turbojpeg.h"
#include <stdio.h>
#include "losslessjpegcrop.h"

using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LosslessJpegCrop oJpegCrop;
    oJpegCrop.LoadJpeg("F:\\Om\\Projects\\jpeg\\LosslessJpegCrop\\car.jpg");
    bool bOk=oJpegCrop.DoCrop(10,10,10,10);
    oJpegCrop.SaveCroppedJpeg("F:\\Om\\Projects\\jpeg\\LosslessJpegCrop\\crop.jpg");
    cout<<oJpegCrop.GetCropErrString();
    return a.exec();
}
