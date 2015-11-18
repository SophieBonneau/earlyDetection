/**************************************************
* Create time series data for a window of frames
*
* By BONNEAU Sophie
* Date: 25 Nov 2014
* Last modified: 14 Janvier 2015
* ************************************************/


#include "crtFeatWindow.h"
#include <sstream>
#include <math.h>



/* ********************************************************** *
* Evaluate the detection score function of a window of frames *
* *********************************************************** */
int evalKer(Eigen::MatrixXd Ds, TimeSeries TS, Eigen::MatrixXd w, double b, int minSegLen, int maxSegLen, int segStride, int d, int sd, int featType, double thresh)
{
	int n = Ds.cols();
	double minth = -125.803;
	double maxth = 130.957;
	
	if ((minSegLen < 1) || (maxSegLen < minSegLen) || (segStride < 1))
		std::cout << "crtFeatWindow: evalKer: invalid option for sOpt";
	if (minSegLen > n)
		std::cout << "crtFeatWindow: evalKer: minimum segment length is greater than the time series length" << std::endl;
	if (maxSegLen > n)
		maxSegLen = n;

	//Time series options
	TS.D = Ds.data();
	TS.n = n;

	if (featType == FEAT_BAG) {
		TS.IntD = new double[d*(n + 1)];
		cmpIntIm(TS.D, d, n, TS.IntD);
	}
	else if (featType == FEAT_ORDER) {
		TS.sd = sd;
	}

	TS.setSegLst(minSegLen, maxSegLen, segStride);
	TS.updateSegLstVals(w.data(), b);

	//Event mxEv;
	double mxVal = -std::numeric_limits<double>::infinity();
	int curIdx = 0, segLstSz = TS.segLst.size();

	for (int t = minSegLen; t<n; t++) {

		if (curIdx < segLstSz) {	// there are more segments to consider
			ExEvent curSeg = TS.segLst[curIdx];
			while (curSeg.e <= t) {
				mxVal = curSeg.val;

				//Detect the Event (if detect score sup to a threshold)
				if (mxVal > thresh) {
					//std::cout<<"sortie "<<mxVal << " > " <<thresh <<std::endl;
					return 0;
				}

				curIdx++;
				if (curIdx >= segLstSz)
					break;

				curSeg = TS.segLst[curIdx];

			}
		}
	}

	//std::cout << "crtFeatWindow: evalKer: No event was found" << std::endl;

	return -1;
}
