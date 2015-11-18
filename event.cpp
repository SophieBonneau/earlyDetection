/**************************************************
* Event class
*
* By BONNEAU Sophie
* Date: 25 Nov 2014
* Last modified: 25 Nov 2014
* ************************************************/


#include "event.h"
#include <sstream>
#include <iostream>

using namespace std;


bool
Event::isEmpty() const{
	if ((s < 0) || (e < s)) return true;
	else return false;
}

int Event::length() const{
	if (isEmpty()) return 0;
	else return (e - s + 1);
}

double
Event::deltaLoss(Event const& otherEv) const{
	if (isEmpty() && otherEv.isEmpty()) return 0;
	else if (isEmpty() || otherEv.isEmpty()) return 1;
	else{
		int mx_s = max(s, otherEv.s);
		int mn_e = min(e, otherEv.e);
		if (mn_e < mx_s) return 1;
		else {
			return 1 - 2 * ((double)(mn_e - mx_s + 1)) / (length() + otherEv.length());
		}
	}
}

void cmpIntIm(double const *D, int d, int n, double *IntD){
	memset(IntD, 0, d*sizeof(double));
	memcpy(IntD + d, D, d*n*sizeof(double)); //IntD ~ D ?
	for (int c = 1; c <= n; c++){
		cblas_daxpy(d, 1.0, IntD + d*(c - 1), 1, IntD + d*c, 1);    //IntD(:,c)=IntD(:,c)+IntD(:,c-1) ?
	}
}

void cmpIntIm_1D(double const *D, int n, double *IntD){
	IntD[0] = 0;
	for (int c = 1; c <= n; c++){
		IntD[c] = IntD[c - 1] + D[c - 1];
	}
}


double diffclock(clock_t clock1, clock_t clock2){
	double diffticks = clock1 - clock2;
	double diffms = diffticks / CLOCKS_PER_SEC;
	return diffms;
}

string Event::str(){
	ostringstream rslt;
	rslt << "(" << s << " " << e << ")";
	return rslt.str();
}


void sampleSeg(double const *D, int d, Event const& ev, int sd, double *raw_feat){
	double r, *raw_feat_i;
	int len = ev.length(), lo, up;
	for (int i = 0; i < sd; i++){
		raw_feat_i = raw_feat + i*d;
		r = ev.s + ((double)i*(len - 1)) / (sd - 1);
		lo = (int)floor(r);
		memcpy(raw_feat_i, D + d*lo, d*sizeof(double)); //copy D(:,lo) to raw_feat_i
		if (lo < r){
			up = lo + 1;
			cblas_dscal(d, r - lo, raw_feat_i, 1); // raw_feat_i = raw_feat_i*(r-lo);
			cblas_daxpy(d, up - r, D + d*up, 1, raw_feat_i, 1); // raw_feat_i = raw_feat_i + (up-r)*D(:,up)
		}
	}
}
