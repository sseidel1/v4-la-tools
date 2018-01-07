#ifndef MODEL_H
#define MODEL_H

#include "CSMatrix.h"
#include "LocatingArray.h"
#include "VectorXf.h"

// QR and least squares workspace
typedef struct WorkSpace {
	float **dataQ;
	float **dataR;
	
	float *workVec;
} WorkSpace;

typedef struct TermIndex {
	int termIndex;
	struct TermIndex *next;
} TermIndex;

class Model {
private:
	static WorkSpace *workSpace;
	
	// CSMatrix to work with
	CSMatrix *csMatrix;
	
	// the maximum number of terms his model can accomodate
	int maxTerms;
	
	// the number of rows or tests
	int tests;
	
	// number of terms in the model
	int terms;
	
	// list with term indices
	TermIndex *hTermIndex;
	
	// response vector (this is actual data from the response file)
	VectorXf *response;
	
	// actual response of the model
	float *modelResponse;
	
	float *coefVec; // n by 1
	float *resiVec; // m by 1
	
	float rSquared;
	
	
public:
	// constructer - initialize the model
	Model(VectorXf *response, int maxTerms, CSMatrix *csMatrix);
	
	// constructor - duplicate a model
	Model(Model *model);
	
	// print the model factors' names
	void printModelFactors();
	
	// perform least squares on this model
	void leastSquares();
	
	// get the residuals vector for this model
	float *getResiVec();
	
	// get r-squared
	float getRSquared();
	
	// check if term is part of the model
	bool termExists(int col_i);
	
	// add a term to the model
	bool addTerm(int col_i);
	
	// remove a term from the model
	bool removeTerm(int col_i);
	
	// get the number of terms
	int getTerms();
	
	// destructor
	~Model();
	
	// static: setup the global workspace
	static void setupWorkSpace(int rows, int cols);
};

#endif
