/**************************************************
* Create time series data for a window of frames
*
* By BONNEAU Sophie
* Date: 25 Nov 2014
* Last modified: 14 Janvier 2015
* ************************************************/


#ifndef CRTFEATWINDOW_HPP
#define CRTFEATWINDOW_HPP

#include "crtFeatVect.h"
#include "kernelTS.h"

int evalKer(Eigen::MatrixXd Ds, TimeSeries TS, Eigen::MatrixXd w, double b, int minSegLen, int maxSegLen, int segStride, int d, int sd, int featType, double thresh);

#endif // CRTFEATWINDOW_H