//created by Pengtao Xie
#include "stdafx.h"
#include "auxds.h"
#include <map>
#include <math.h>
using namespace std;

void VectorCopy(int * src, int * dst, int dim);
void ReleaseMap(map<int,int*> ht);
float Logistic(float x);
float DotProd2D(float **W, float **X,int dim1, int dim2);
float DotProd1D(float * w, float * x, int dim);
void CpPatch2D(float **src, float **dst, Point * range);
float MaxMat(float ** matrix, int rows, int cols);
float SumMat(float ** matrix, int rows, int cols);
float AvgMat(float ** matrix, int rows, int cols);
float Max(float a, float b);
float RandGenBernou(float mu);
float L2NormMat(float ** matrix, int rows, int cols);
float RandGenGaussian(float mu,float sigma);