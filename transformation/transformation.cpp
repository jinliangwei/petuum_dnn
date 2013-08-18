//created by Pengtao Xie
#include "stdafx.h"
#include "transformations.h"
#include "util.h"
#include "auxds.h"
#include <vector>
using namespace std;

Size ComputeSize(Size src, Trsfm t)
{
	Size dst;
	if(t.ttype==FILTER)
	{

	}
	else if(t.ttype==POOL)
	{

	}
	else if(t.ttype==NORMALIZE)
	{

	}
	else if(t.ttype==RECTIFY||t.ttype==STOCHASTICACT)
		dst=src;
	return dst;
}

NeuralSet Map(NeuralSet src, Trsfm t)
{
	NeuralSet dst;
	dst.SetDataNum(src.GetDataNum());
	dst.SetSize(ComputeSize(src.GetSize(),t));
	return dst;
}
void Transform(vector<NeuralSet>src, const NeuralSet & dst,Trsfm t)
{
  //can be done in parallel
  vector<Partition> partitions;
  for(int i=0;i<partitions.size();i++)
  {
    Partition p=partitions[i];
    //find the dependent partitions
    vector<Partition> dp=FindDP(p, src,t);
    //do partition level transformation
    Transfrom(dp, p,  t);
  }
}


//transformations
void Map2d(int x,int y, int & x1,int & x2, int& y1, int& y2 )
{
	//todo
}
void Map1d(int x,int &x1,int &x2)
{
	//todo
}
void Conn(Point src, Point * range, int dim)
{
	int x=src.first;
	int y=src.second;
	int x1=-1,x2=-1,y1=-1,y2=-1;
	//for 1 dim neural net
	if(dim==1)
		Map1d(y,y1,y2);
	//for 2 dim neural net
	else if(dim==2)
		Map2d( x,y,  x1,x2, y1,  y2 );
	range[0]=Point(x1,x2);
	range[1]=Point(y1,y2);
}
//filtering
void Filter(NS * src, NS *dst)
{

	int datanum=src->GetDataNum();
	int dim=src->GetDim();
	int nndim1=0,nndim2=0;
	if(dim==1)
	{
		nndim1=1;
		nndim2=src->GetNNDim()[0];
	}
	else
	{
		nndim1=src->GetNNDim()[0];
		nndim2=src->GetNNDim()[1];
	}

	//for each data instance
	for(int d=0;d<datanum;d++)
	{
		for(int i=0;i<nndim1;i++)
		{
			for(int j=0;j<nndim2;j++)
			{
				//get range of lower layer neurons
				Point * range=new Point[2];
				Conn(Point(i,j), range,dim);
				//do computation
				delete[]range;
			}
		}
	}
}
//one to one filtering
void Filter(NS * src, NS *dst,int filter_type,  int * filter_size,float ** W,float b)
{
	NS ** srcs=new NS*[1];
	srcs[0]=src;
	float ***Ws=new float**[1];
	Ws[0]=W;
	MapNS(srcs, dst, 1, FILTER, filter_type, filter_size, Ws, b);
	delete[]W;
	delete[]srcs;
}


//multiple to one filtering
void Filter(NS ** src, NS *dst,int numsrcs,int filter_type, int * filter_size,float *** W,float b)
{
	MapNS(src, dst, numsrcs, FILTER, filter_type, filter_size, W, b);
}
//map multiple src NSs to one dst NS
void MapNS(NS ** src, NS *dst,int numsrcs, int trans_type,int operate_type, int * win_size, float *** W,float b)
{
	int datanum=src[0]->GetDataNum();
	int dim=src[0]->GetDim();
	int nndim1=0,nndim2=0;
	nndim1=src[0]->GetNNDim()[0];
	nndim2=src[0]->GetNNDim()[1];

	//for each data instance
	float ** patch=new float*[win_size[0]];
	for(int p=0;p<win_size[0];p++)
		patch[p]=new float[win_size[1]];
	Point * range=new Point[2];
	for(int d=0;d<datanum;d++)
	{
		for(int i=0;i<nndim1;i++)
		{
			for(int j=0;j<nndim2;j++)
			{
				//get range of lower layer neurons

				Conn(Point(i,j), range,dim);
				//do computation
				/*******************/
				/**  specialized  **/
				//copy patch

				float act=0;
				for(int s=0;s<numsrcs;s++)
				{
					if(trans_type==FILTER||trans_type==POOL)
					{
						CpPatch2D(src[s]->GetValues()[d], patch, range);
						if(trans_type==FILTER)
						{
							act+=DotProd2D(W[s], patch,win_size[0], win_size[1]);//LINEAR
							act+=b;
							if(operate_type==LOGISTIC)
								act=Logistic(act);
							else if(operate_type=TANH)
								act=tanh(act);
						}
						else if(trans_type==POOL)
						{
							if(operate_type==MAX)
								act=MaxMat(patch,win_size[0],win_size[1]);
							else if(operate_type==AVERAGE)
								act=AvgMat(patch,win_size[0],win_size[1]);
							else if(operate_type==L2)
								act=L2NormMat(patch, win_size[0], win_size[1]);
						}
					}
					else if(trans_type==RECTIFY||trans_type==STOCHASTICACT)
					{
						if(trans_type==RECTIFY)
						{
							if(operate_type==NONNEG)
								act=Max(0,src[s]->GetValues()[d][i][j]);
							else if(operate_type==ABS)
								act=abs(src[s]->GetValues()[d][i][j]);
						}
						else if(trans_type==STOCHASTICACT)
						{
							if(operate_type==BERNOULLI)
								act=RandGenBernou(src[s]->GetValues()[d][i][j]);
							else if(operate_type==GAUSSIAN)
								act=RandGenGaussian(src[s]->GetValues()[d][i][j],1);
						}
					}

				}
				dst->GetValues()[d][i][j]=act;

				/*******************/

			}
		}
		for(int p=0;p<win_size[0];p++)
			delete[]patch[p];
		delete[]patch;
		delete[]range;
	}
}
//one to one pooling
void Pool(NS * src, NS * dst, int * pool_size, int pool_type)
{
	NS ** srcs=new NS*[1];
	srcs[0]=src;
	MapNS(srcs, dst,1, POOL,pool_type, pool_size, NULL,0);
	delete[]srcs;
}
//one to one rectify
void Rectify(NS * src, NS * dst,  int rectify_type)
{
	NS ** srcs=new NS*[1];
	srcs[0]=src;
	MapNS(srcs, dst,1, RECTIFY,rectify_type, NULL, NULL,0);
	delete[]srcs;
}

//pooling
void Pool(NS * src, NS * dst);
//rectify
void Rectify(NS * src, NS * dst);
//normalize
void Normalize(NS * src, NS * dst);
//stochastic activation
void SA(NS *src, NS *dst);
//add noise to neurons for fine tuning
void Noise(NS *src, NS *dst);
//compute error in back propagation
void Bperror(NS *src, NS *dst);