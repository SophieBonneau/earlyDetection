/**************************************************
* Create time series data for SVM-based detectors
*
* By BONNEAU Sophie
* Date: 25 Nov 2014
* Last modified: 25 Nov 2014
* ************************************************/

#ifndef CRTFEATVECT_HPP
#define CRTFEATVECT_HPP

#include "read_file.h"
#include <list>
#include <math.h>

#include <Eigen/Cholesky>

Eigen::MatrixXd mixgauss_prob(Eigen::MatrixXd seq, Eigen::MatrixXd mu, Eigen::VectorXi dim_mu, std::vector<Eigen::MatrixXd> sigma, Eigen::VectorXi dim_sigma, Eigen::MatrixXd mixmat, int nbCluster);

Eigen::MatrixXd top3(Eigen::MatrixXd mat);
Eigen::MatrixXd square_dist(Eigen::MatrixXd p, Eigen::MatrixXd q, Eigen::MatrixXd A);


#endif // CRTTSDATA_H