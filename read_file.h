/*********************************************
* Read files (mat files)
*
* By BONNEAU Sophie
* Date: 25 Nov 2014
* Last modified: 25 Nov 2014
* *******************************************/

#ifndef READ_FILE_HPP
#define READ_FILE_HPP

#include <iostream>
#include <vector>

#include <Eigen/Dense>

#include "mat.h"
#include "matrix.h"

mxArray *read_matfile(const char *filename, const char *varname);

void print_matfile(const char *filename, const char *varname);
Eigen::VectorXi no_dim(const char *filename, const char *varname);

double store_matvar(const char *filename, const char *varname);
Eigen::MatrixXd store_mattab(const char *filename, const char *varname);
std::vector<Eigen::MatrixXd> store_mattab2(const char *filename, const char *varname);

#endif // READ_FILE_H
