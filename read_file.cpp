/*********************************************
* Read files (mat files)
*
* By BONNEAU Sophie
* Date: 25 Nov 2014
* Last modified: 25 Nov 2014
* *******************************************/


#include "read_file.h"


/* *************** *
* Read a mat file *
* *************** */
mxArray *read_matfile(const char *filename, const char *varname)
{
	/* Open the mat file */
	MATFile *pmat;
	pmat = matOpen(filename, "r");

	if (pmat == NULL) {
		std::cout << "read_file.cpp: read_matfile: Error opening file" << std::endl;
	}

	/* Read the variables of mat file */
	mxArray *var = NULL;
	var = matGetVariable(pmat, varname);

	matClose(pmat);
	//print_matfile(var,varname);
	return var;
}


/* ****************************** *
* Print a variable of a mat file *
* ****************************** */
void print_matfile(const char *filename, const char *varname)
{
	mxArray *var;
	var = read_matfile(filename, varname);

	if (mxGetClassID(var) == 6) { //if var is a double

		double *cell = NULL;
		cell = mxGetPr(var);

		for (int i = 0; i<mxGetNumberOfElements(var); i++){
			std::cout << varname << " is " << *cell << std::endl;
			cell++;
		}
	}
	else { //Create a new case if an other class exist
		std::cout << "the class name of " << var << "is" << mxGetClassName(var) << std::endl;
	}
}


/* ****************************************************************** *
* Compute the number of dimension of a matfile's particular variable *
* ****************************************************************** */
Eigen::VectorXi no_dim(const char *filename, const char *varname) {

	mxArray *var = NULL;	
	var = read_matfile(filename, varname);

	size_t nb_dim;
	nb_dim = mxGetNumberOfDimensions(var);

	const size_t *dim;
	dim = mxGetDimensions(var);

	Eigen::initParallel();
	Eigen::VectorXi tab_dim(nb_dim);

	// Number of raws and columns
	for (int i = 0; i<nb_dim; i++) {
		tab_dim(i) = *dim;
		dim++;
	}

	return tab_dim;
}



/* ********************************************* *
* Store the matfile'variable: if it is a double *
* ********************************************* */
double store_matvar(const char *filename, const char *varname)
{
	double variable;

	mxArray * var;
	var = read_matfile(filename, varname);

	if (mxGetClassID(var) == 6) { //if var is a double
		double *cell = NULL;
		cell = mxGetPr(var);

		variable = *cell;
	}
	else { //Create a new case if an other class exist
		std::cout << "read_file: store_matvar: the class name of " << varname << " is " << mxGetClassName(var) << std::endl;
	}

	return variable;
}


/* ****************************************************** *
* Store the matfile'variable: if it is a matrix of double *
* ******************************************************* */
Eigen::MatrixXd store_mattab(const char *filename, const char *varname)
{
	mxArray *var;
	var = read_matfile(filename, varname);

	size_t nb_dim;
	nb_dim = mxGetNumberOfDimensions(var);

	Eigen::initParallel();
	Eigen::VectorXi tab_dim;
	tab_dim = no_dim(filename, varname);

	//if var is a double
	if (mxGetClassID(var) == 6) {
		if (nb_dim == 2) {
			Eigen::MatrixXd tab_var(tab_dim(0), tab_dim(1));

			double *cell = NULL;
			cell = mxGetPr(var);

			// Matrix creation
			for (int j = 0; j<tab_dim(1); j++) {
				for (int i = 0; i<tab_dim(0); i++) {
					tab_var(i, j) = *cell;
					cell++;
				}
			}
			return tab_var;
		}
		else {
			std::cout << "read_file: store_mattab: number of dim != 2";
		}
	}

	//if var is a struct
	else if (mxGetClassID(var) == 2) {
		int nb_fields;
		nb_fields = mxGetNumberOfFields(var);

		Eigen::MatrixXd tab_var(nb_fields, 1);

		// Matrix creation
		for (int i = 0; i<nb_fields; i++) {
			tab_var(i, 0) = *mxGetPr(mxGetCell(var, i));
		}

		return tab_var;

	}

	else { //Create a new case if an other class exist
		std::cout << "read_file: store_mattab: the class name of " << varname << " is " << mxGetClassName(var) << std::endl;
	}
}

/* ******************************************************* *
* Store the matfile'variable: if it is an array of matrix *
* ********************************************************* */
std::vector<Eigen::MatrixXd> store_mattab2(const char *filename, const char *varname)
{
	mxArray *var;
	var = read_matfile(filename, varname);

	double *cell = NULL;
	cell = mxGetPr(var);

	size_t nb_dim;
	nb_dim = mxGetNumberOfDimensions(var);

	const size_t *dim;
	dim = mxGetDimensions(var);

	Eigen::initParallel();
	Eigen::VectorXi tab_dim;
	tab_dim = no_dim(filename, varname);

	if (mxGetClassID(var) == 6) { //if var is a double

		if (nb_dim == 3) {
			std::vector<Eigen::MatrixXd> cell_var;
			Eigen::MatrixXd tab_var(tab_dim(0), tab_dim(1));

			// Matrix creation
			for (int k = 0; k<tab_dim(2); k++){
				for (int j = 0; j<tab_dim(1); j++) {
					for (int i = 0; i<tab_dim(0); i++) {
						tab_var(i, j) = *cell;
						cell++;
					}
				}
				cell_var.push_back(tab_var);
			}
			return cell_var;
		}
		else {
			std::cout << "read_file: store_mattab2: Number of dimensions: " << nb_dim << std::endl;
		}
	}
}