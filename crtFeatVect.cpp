/**************************************************
* Create time series data for SVM-based detectors
*
* By BONNEAU Sophie
* Date:25 Nov 2014
* Last modified: 25 Nov 2014
* ************************************************/


#include "crtFeatVect.h"



/* ******************************************************************************* *
* Evaluate the probability density function of a consitionnal mixture of Gaussian *
* ******************************************************************************* */
Eigen::MatrixXd mixgauss_prob(Eigen::MatrixXd data, Eigen::MatrixXd mu, Eigen::VectorXi dim_mu, std::vector<Eigen::MatrixXd> sigma, Eigen::VectorXi dim_sigma, Eigen::MatrixXd mixmat, int nbCluster)
{
	int d, Q, M;

	if (dim_mu.size() == 2 && mu.cols() == 1){
		d = mu.rows();
		Q = 1;
		M = 1;
	}
	else if (dim_mu.size() == 2 && mu.cols() > 1) {
		d = mu.rows();
		Q = mu.cols();
		M = 1;
	}
	else if (dim_mu.size() == 3) {
		d = mu.rows();
		Q = mu.cols();
		M = dim_mu(2);
	}
	else {
		std::cout << "crtTSData: mixgauss_prob: Problem in mu dimension" << std::endl;
	}

	int T = data.cols();

	Eigen::MatrixXd B(Q, T);
	Eigen::MatrixXd D;  //in fact D is a vector
	std::vector<Eigen::MatrixXd> B2;

	if (dim_sigma.size() == 3) {
		//Eigen::MatrixXd B2(Q,M,T);
		std::vector<Eigen::VectorXcd> tab_eigvals;
		bool isposdef = 0;

		// Compute the eigenvalues for each matrix of sigma
		for (std::vector<Eigen::MatrixXd>::iterator it = sigma.begin(), it_end = sigma.end(); it != it_end; ++it) {
			Eigen::VectorXcd eigenvals;
			Eigen::MatrixXd cell = *it;

			eigenvals = cell.eigenvalues();
			tab_eigvals.push_back(eigenvals);
		}

		// Determine if the matrix is positively-definite
		for (std::vector<Eigen::VectorXcd>::iterator it = tab_eigvals.begin(), it_end = tab_eigvals.end(); it != it_end; ++it) {
			Eigen::VectorXcd cell = *it;

			for (int i = 0; i<cell.size(); i++) {
				if (std::imag(cell(i)) == 0) {
					if (std::real(cell(i)) > 0.0f) {
						isposdef = 1;
					}
					else {
						isposdef = 0;
					}
				}
				else {
					//std::cout << "crtFeatVect: mixgauss_prob: Eigenvalues shouldn't be complex" << std::endl;
				}
			}
		}

		int cpt = 0;


		//Compute the normal distribution function B2
		for (std::vector<Eigen::MatrixXd>::iterator it = sigma.begin(), it_end = sigma.end(); it != it_end; ++it) {
			Eigen::MatrixXd cell = *it;

			if (isposdef == 1) {
				Eigen::MatrixXd inv_sig;
				inv_sig = cell.inverse();
				D = square_dist(data, mu.col(cpt), inv_sig);
				D.transposeInPlace();

				//logB2 = -(d/2)*log(2*pi) - 0.5*log(det(sigma)) - 0.5*D is a vector
				Eigen::LLT<Eigen::MatrixXd> lltOfSigma(cell);
				Eigen::MatrixXd L;
				L = lltOfSigma.matrixL();

				Eigen::VectorXd diag;
				diag = L.diagonal();
				double sum_diag = 0;

				for (int i = 0; i<diag.rows(); i++) {
					diag(i) = log(diag(i));
					sum_diag += diag(i);
				}
				sum_diag = -sum_diag - (d / 2)*log(2 * M_PI);

				Eigen::MatrixXd logB2(D.rows(), D.cols());
				for (int i = 0; i<D.rows(); i++) {
					for (int j = 0; j<D.cols(); j++) {
						logB2(i, j) = sum_diag;
					}
				}
				logB2 = logB2 - 0.5*D;

				for (int i = 0; i<logB2.rows(); i++) {
					for (int j = 0; j<logB2.cols(); j++) {
						logB2(i, j) = exp(logB2(i, j));
					}
				}

				B2.push_back(logB2);
			}
			else {
				std::cout << "crtTSData: mixgauss_prob: sigma is not a positively definite matrix" << std::endl;
			}
			cpt++;
		}
	}
	else {
		std::cout << "crtTSData: mixgauss_prob: Problem of sigma dimension (cf mixgauss_prob to implement genral case)" << std::endl;
	}



	//if (Q < T) {
	int cpt2 = 0;

	for (std::vector<Eigen::MatrixXd>::iterator it = B2.begin(), it_end = B2.end(); it != it_end; ++it) {
		Eigen::MatrixXd cell = *it;

		for (int t = 0; t<T; t++) {
			B(cpt2, t) = mixmat(cpt2, 0) * cell(0, t); //Weight
		}
		cpt2++;
	}
	/*}
	else {
	std::cout << "crtTSData: mixgauss_prob: implement the other case (cf matlab mixgauss_prob)" << std::endl;
	}*/

	return B;
}


/* *********************************** *
* Retain the top 3 values of a matrix *
* *********************************** */
Eigen::MatrixXd top3(Eigen::MatrixXd mat){

	Eigen::MatrixXd matbis(mat.rows(), 1);
	Eigen::MatrixXd maxTab(mat.cols(), 3);

	//Compute the top three values
	for (int k = 0; k<mat.cols(); k++) {
		matbis = mat.col(k);

		for (int i = 0; i<3; i++) {
			Eigen::MatrixXf::Index maxRow, maxCol;
			double max = 0;

			max = matbis.maxCoeff(&maxRow, &maxCol);
			maxTab(k, i) = max;
			matbis(maxRow, maxCol) = 0;
		}
	}

	//Store the top 3 values of each columns in a matrix
	for (int c = 0; c<mat.cols(); c++) {
		for (int r = 0; r<mat.rows(); r++) {
			if (mat(r, c) != maxTab(c, 0) && mat(r, c) != maxTab(c, 1) && mat(r, c) != maxTab(c, 2)){
				mat(r, c) = 0;
			}
			else {
				if (mat(r, c) == 0) {
					mat(r, c) = 0;
				}
				else {
					mat(r, c) = log(mat(r, c));
				}
			}
		}
	}

	return mat;
}


/* ***************************************** *
* Compute square distance between 2 matrix  *
* m(i,j)=(p(:,i)-q(:,j))'*A*(p(:,i)-q(:,j)) *
* ***************************************** */
Eigen::MatrixXd square_dist(Eigen::MatrixXd p, Eigen::MatrixXd q, Eigen::MatrixXd A)
{
	Eigen::MatrixXd sqdist(p.cols(), q.cols());

	if (p.rows() != q.rows()) {
		//std::cout << "crtFeatVect: square_dist: number of rows must be the same" << std::endl;
	}
	else {
		Eigen::VectorXd sub_pq(p.rows());

		for (int i = 0; i<p.cols(); i++) {
			for (int j = 0; j<q.cols(); j++) {
				for (int k = 0; k<p.rows(); k++) {
					sub_pq(k) = p(k, i) - q(k, j);
				}
				sqdist(i, j) = sub_pq.transpose()*A*sub_pq;
			}
		}
	}

	return sqdist;
}