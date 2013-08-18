//created by Pengtao Xie
#include "stdafx.h"
#include "util.h"
#include <ctime>
#include <math.h>
#include <random>
using namespace std;
string Num2String(int digit)
{
  char str[512];
  sprintf(str,"%d",digit);
  return str;
}
void VectorCopy(int * src, int * dst, int dim)
{
	for(int i=0;i<dim;i++)
		dst[i]=src[i];
}
void ReleaseMap(map<int,int*> ht)
{
	map<int,int*>::iterator it;
	for(it=ht.begin();it!=ht.end();it++)
		delete[]it->second;
}
float Logistic(float x)
{
	return 1/(1+exp(-x));
}
float DotProd2D(float **W, float **X,int dim1, int dim2)
{
	float sum=0;
	for(int i=0;i<dim1;i++)
	{
		for(int j=0;j<dim2;j++)
			sum+=W[i][j]*X[i][j];
	}
	return sum;
}
float DotProd1D(float * w, float * x, int dim)
{
	float sum=0;
	for(int i=0;i<dim;i++)
		sum+=w[i]*x[i];
	return sum;
}
void CpPatch2D(float **src, float **dst, Point * range)
{
	int x1=range[0].first;
	int x2=range[0].second;
	int y1=range[1].first;
	int y2=range[1].second;
	for(int x=x1;x<=x2;x++)
	{
		for(int y=y1;y<=y2;y++)
			dst[x-x1][y-y1]=src[x1][y1];
	}
}
float MaxMat(float ** matrix, int rows, int cols)
{
	float maxvalue=-1e+5;
	for(int r=0;r<rows;r++)
	{
		for(int c=0;c<cols;c++)
		{
			maxvalue=Max(maxvalue, matrix[r][c]);
		}
	}
	return maxvalue;
}

float SumMat(float ** matrix, int rows, int cols)
{
	float sum=0;
	for(int r=0;r<rows;r++)
	{
		for(int c=0;c<cols;c++)
			sum+=matrix[r][c];
	}
	return sum;
}

float AvgMat(float ** matrix, int rows, int cols)
{
	return SumMat(matrix,rows,cols)/(rows*cols);
}
float Max(float a, float b)
{
	return a>b?a:b;
}
float RandGenBernou(float mu)
{
	srand((unsigned)time(0));
	float a=(rand()%10000)*1.0/10000;
	return a<mu?1:0;
}
float L2NormMat(float ** matrix, int rows, int cols)
{
	float ss=0;
	for(int r=0;r<rows;r++)
	{
		for(int c=0;c<cols;c++)
			ss+=pow(matrix[r][c],2);
	}
	return sqrt(ss);
}
float RandGenGaussian(float mu,float sigma)
{
	default_random_engine generator;
	normal_distribution<float> distribution(mu, sigma);
	return distribution(generator);
}
