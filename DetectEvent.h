#ifndef __DETECTEVENT_H__
#define __DETECTEVENT_H__

#include <Eigen/Dense>

#include "KeyboardSimulator.h"
#include "crtFeatWindow.h"

#define nMyoSensors 2		//Number of Myo sensors

#define STRIDE		5		//Size of the stride between each sliding window
#define MINLENGTH	30		//Minimum size of a window
#define NFRAMES		100000	//Maximum number of frames
#define DIM			14		//Number of dimensions

Eigen::MatrixXd seq(DIM*nMyoSensors, NFRAMES);
//Eigen::MatrixXd seq2(DIM*nMyoSensors, NFRAMES);
int cpt_col = 0;
int compt = 0;


/* ******************************************************************** *
* Class containing the average and standard deviation for normalization *
* ********************************************************************* */
class NormParam {
public:
	Eigen::MatrixXd mean;
	Eigen::MatrixXd stand_dev;


	//Constructors
	NormParam()
	{
	}

	NormParam(Eigen::MatrixXd aver, Eigen::MatrixXd dev)
	{
		mean = aver;
		stand_dev = dev;
	}

	NormParam(const char* file)
	{
		mean = store_mattab(file,"average");
		stand_dev = store_mattab(file,"standDev");
	}
};


/* ********************************************** *
* Class containing all tha parameters of clusters *
* *********************************************** */
class Parameters {
public:	
	Eigen::MatrixXd mu;
	Eigen::VectorXi dim_mu;
	std::vector<Eigen::MatrixXd> sigma;
	Eigen::VectorXi dim_sigma;
	Eigen::MatrixXd mixmat;
	Eigen::MatrixXd w;
	double b;
	int d, sd, fd, featType;
	int maxSegLen;

	TimeSeries TS;
	
	int nbCluster;
	Eigen::MatrixXd Ds;

	//Call players'command	
	CallCommand *c;
	int label;
	double threshold;

	//Constructors
	Parameters()
	{
	}

	Parameters(const char *pstFile, int nb, double thresh)
	{
		label = nb;
		threshold = thresh;
		
		mu = store_mattab(pstFile, "mu");
		dim_mu = no_dim(pstFile, "mu");
		sigma = store_mattab2(pstFile, "sigma");
		dim_sigma = no_dim(pstFile, "sigma");
		mixmat = store_mattab(pstFile, "mixmat");
		
		nbCluster = mu.cols();
		
		/* Create the Time Series data */
		Ds.resize(nbCluster,NFRAMES);
		d = Ds.rows();

		w = store_mattab(pstFile, "w_instant");
		b = store_matvar(pstFile, "b_instant");

		/* Segment search options (sOpt) */
		maxSegLen = 2 * MINLENGTH;

		/* Kernel options (kOpt) */
		Eigen::MatrixXd kOpt;
		kOpt = store_mattab(pstFile, "kOpt");

		Kernel ker;
		ker.kerType = static_cast<int>(kOpt(0, 0));
		ker.kerN = static_cast<int>(kOpt(1, 0));
		ker.kerL = kOpt(2, 0);

		if (kOpt(5, 0) != 0) {
			ker.nSegDiv = static_cast<int>(kOpt(5, 0));
			if (ker.nSegDiv < 1)
				std::cout << "DetectEvent.h: nSegDiv must be >= 1" << std::endl;
		}
		else {
			ker.nSegDiv = 1;
		}

		featType = static_cast<int>(kOpt(3, 0));
		if (featType == FEAT_ORDER) {
			sd = static_cast<int>(kOpt(4, 0));
			fd = ker.get_fd(sd*d);
		}
		else if ((featType == FEAT_BAG) || (featType == FEAT_ENDDIFF)) {
			fd = ker.get_fd(d);
		}
		else {
			std::cout << "DetectEvent.h: Unknown feature option" << std::endl;
		}

		if (fd != w.rows()){
			std::cout << "DetectEvent.h: length of w is inconsistent with the dimension of data" << std::endl;
		}

		/* Time series options */
		TS.fd = fd;
		TS.ker = ker;
		TS.featType = featType;
		TS.d = d;

		c = new CallCommand();
	}

};

class DetectEvent {
private:
	unsigned thIDcomp, thIDRec;
	


public:
	Parameters* param;
	HANDLE hThComp, hThRec;

	DetectEvent() {
		hThComp = (HANDLE)1;
		hThRec = (HANDLE)1;
		param = new Parameters();
	}

	DetectEvent(const char *pstFile, int nb, double thresh)
	{
		hThComp = (HANDLE)1;
		hThRec = (HANDLE)1;
		param = new Parameters(pstFile, nb, thresh);
	}

	static unsigned __stdcall GetComputationLabel(void* param_ev)
	{	
		Parameters *param = (Parameters *)param_ev;

		Eigen::MatrixXd obslik;
		obslik = mixgauss_prob(seq.block(0,10,DIM*nMyoSensors, MINLENGTH), param->mu, param->dim_mu, param->sigma, param->dim_sigma, param->mixmat, param->nbCluster);

		//Top 3 values
		Eigen::MatrixXd top;
		top = top3(obslik);

		for(int i=0; i<MINLENGTH; i++) 
			param->Ds.col(i) = top.col(i);

		std::cout<<"top first"<<std::endl;

		return 0;
	}

	static unsigned __stdcall GetRecognizedLabel(void* param_ev)
	{
		Parameters *param = (Parameters *)param_ev;
		
		//Recognition code
		int eval = -1;
		
		Eigen::MatrixXd obslik;
		obslik = mixgauss_prob(seq.block(0,compt-STRIDE,DIM*nMyoSensors,STRIDE), param->mu, param->dim_mu, param->sigma, param->dim_sigma, param->mixmat, param->nbCluster);
		
		//Top 3 values
		Eigen::MatrixXd top;
		top = top3(obslik);

		for(int i=0; i<STRIDE; i++)
			param->Ds.col(MINLENGTH + STRIDE*cpt_col + i) = top.col(i);
	
		eval = evalKer(param->Ds.block(0,0,param->nbCluster,MINLENGTH+STRIDE*cpt_col+STRIDE), param->TS, param->w, param->b, MINLENGTH, param->maxSegLen, STRIDE, param->d, param->sd, param->featType, param->threshold);
		
		cpt_col++;
	
		//Recognition_results return a corresponding number which is reused as paramenter
		if(eval == 0){
			//Ehab's code to discriminate mvt (FIRST WAY)
			param->c->SendCommand(param ->label);

			
		}

		return 0;
	}

	void call_comp()
	{
		DWORD dwExCode;
		if (hThComp != NULL){
			GetExitCodeThread(hThComp, &dwExCode); //if the specified thread has not terminated and the function succeeds, the status returned is STILL_ACTIVE
			
			if (dwExCode == STILL_ACTIVE) {
//				printf("スレッド稼働中\n");
			} 
			else {	//Movement detected
				hThComp = (HANDLE)_beginthreadex(NULL, 0, GetComputationLabel, (void *)param, 0, &thIDcomp);
			}
		}
	}

	void call_recognize()
	{
		DWORD dwExCode;
		if (hThRec != NULL){
			GetExitCodeThread(hThRec, &dwExCode); //if the specified thread has not terminated and the function succeeds, the status returned is STILL_ACTIVE
			
			if (dwExCode == STILL_ACTIVE) {
//				printf("スレッド稼働中\n");
			}
			else {	//Movement detected
				hThRec = (HANDLE)_beginthreadex(NULL, 0, GetRecognizedLabel, (void *)param, 0, &thIDRec);
			}
		}
	}

};


#endif//__DETECTEVENT_H__