/**************************************************
* Event class
*
* By BONNEAU Sophie
* Date: 25 Nov 2014
* Last modified: 25 Nov 2014
* ************************************************/

#ifndef EVENT_HPP
#define EVENT_HPP

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits>
#include <algorithm>
#include <gsl/gsl_cblas.h>
#include <string>
#include <string.h>
#include <time.h>



class Event{
public:
	int s, e;
	Event(int s_, int e_){ s = s_; e = e_; }
	Event(){ s = -1; e = -1; }
	Event(const Event& other){ s = other.s; e = other.e; };

	bool isEmpty() const;
	double deltaLoss(Event const& otherEv) const;
	int length() const;

	//   bool operator < (const Event & otherEv) const{
	//      if (e < otherEv.e) return true;
	//      if ((e == otherEv.e) && (s <= otherEv.s)) return true;
	//      return false;
	//   }
	std::string str();
};

double diffclock(clock_t clock1, clock_t clock2);
void   cmpIntIm(double const *D, int d, int n, double *IntD);
void   cmpIntIm_1D(double const *D, int n, double *IntD);
void   sampleSeg(double const *D, int d, Event const& ev, int sd, double *raw_feat);


#endif // EVENT_H