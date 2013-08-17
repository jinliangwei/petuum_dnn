#include "stdafx.h"
#include <map>
#include <vector>
using namespace std;
//a structure containing two values
#ifndef AuxDS_H
#define AuxDS_H
typedef pair<int,int> Point;
typedef pair<int,int> Size;
typedef float ** W;
//enum of job status
enum JOB_STATUS {UNVISITED, INQUEUE, INPROCESSING, DONE};
//enum of transformations
enum TRSFM_TYPE {FILTER, POOL, NORMALIZE, RECTIFY,STOCHASTICACT};
//enum of filter type
enum FILTER_TYPE{LINEAR, LOGISTIC,TANH};
//enum of pool type
enum POOL_TYPE{ AVERAGE,MAX,L2};
//enum of rectify type
enum RECTIFY_TYPE { NONNEG, ABS};
//enum of stochastic activitions
enum STOCHASTICACT_TYPE {BERNOULLI, GAUSSIAN};

enum DependType { ALL2ONE, ONE2ONE, USERDEF};
struct Trsfm
{
	//transform type
  int ttype;
	//operation type associated with transform type
	int otype;
	//window size
	Size winsize;
	//step size when moving a window
	Size stepsize;
};
struct FilterPara
{
	//W
	vector<W> ws;
	//bias
	float b;
};
struct Dependency
{
	//dependency type
	int dtype;
	//user provided dependency
	vector<vector<int>> user_dpd;
};
struct ImgMeta
{
	//img size
	Size imgsize;
	//number of images
	int imgnum;
	//image pixels
	float *** imgdata;
};

#endif
