//created by Pengtao Xie
#include "stdafx.h"
#include "netclass.h"
#include "util.h"

NeuralSet::NeuralSet()
{

}
NeuralSet::NeuralSet(string nsid,Size setsize,int datanum)
{
  this->nsid=nsid;
  this->setsize=setsize;
  this->datanum=datanum;
  CreatePartitions();
}
NeuralSet::~NeuralSet()
{
}
void NeuralSet::SetNsid(string nsid)
{
  this->nsid=nsid;
}
void NeuralSet::SetSize(Size s)
{
  this->setsize=s;
}
void NeuralSet::SetDataNum(int datanum)
{
  this->datanum=datanum;
}
string NeuralSet::GetNsid()
{
  return nsid;
}
Size NeuralSet::GetSize()
{
	return setsize;
}
int NeuralSet::GetDataNum()
{
	return datanum;
}
vector<Partition> NeuralSet::GetPartitions()
{
  return partitions;
}
void NeuralSet::CreatePartitions()
{
  //this is the interface between high level data abstraction and low level system implementation
  //number of rows in each partition
  int prows=setsize.first/numpts.first;
  //number of cols in each partition
  int pcols=setsize.second/numpts.second;
  for(int i=0;i<numpts.first;i++)
  {
    for(int j=0;j<numpts.second;j++)
    {
      string ptid=nsid+"_"+Num2String(i)+"_"+Num2String(j);
      int mid=0;//this should be a global variable, redo it later
      pair<int,int> offset(i*prows,j*pcols);
      Size sz;
      if(i<numpts.first-1&&j<numpts.second-1)
      {
        sz.first=prows;
        sz.second=pcols;
      }
      else if(i==numpts.first-1&&j<numpts.second-1)
      {
        sz.first=setsize.first-prows*(numpts.first-1);
        sz.second=pcols;
      }
      else if(i<numpts.first-1&&j==numpts.second-1)
      {
        sz.first=prows;
        sz.second=setsize.second-pcols*(numpts.second-1);
      }
      else if(i==numpts.first-1&&j==numpts.second-1)
      {
        sz.first=setsize.first-prows*(numpts.first-1);
        sz.second=setsize.second-pcols*(numpts.second-1);
      }
      Partition pt(ptid,mid, nsid,offset,sz,datanum);
      partitions.push_back(pt);
    }
  }
  
}

//get operations
int NS::GetNSId()//get NS id
{
	return nsid;
}
int NS::GetDim()//get NS dim
{
	return dim;
}
int NS::GetDataNum()//get number of data instances
{
	return datanum;
}
int * NS::GetNNDim()//get number of neurons along each dimension
{
	return nndim;
}
float *** NS::GetValues()//get neurons values
{
	return values;
}

//set operations
void NS::SetNSId(int nsid)//set NS id
{
	this->nsid=nsid;
}
void NS::SetDim(int dim)//set NS dim
{
	this->dim=dim;
}
void NS::SetDataNum(int datanum)//set number of data instances
{
	this->datanum=datanum;
}
void NS::SetNNDim(int * nndim)//set number of neurons along each dimension
{
	VectorCopy(this->nndim, nndim, dim);
}

//constructor
NS::NS()
{
	nsid=-1;//NS id
	dim=0;//dim of NS -- for now, the max dim is 2
	nndim=NULL;//number of neurons along each dimension
	datanum=0;//number of data instances
	values=NULL;//neuron values
}
NS::NS(int nsid, int dim, int * nndim, int datanum)
{
	this->nsid=nsid;
	this->dim=dim;
	this->nndim=nndim;
	this->datanum=datanum;
	this->nndim=new int[dim];
	VectorCopy(this->nndim, nndim, this->dim);
	values=new float**[datanum];
	for(int i=0;i<datanum;i++)
	{
		values[i]=new float*[nndim[0]];
		for(int j=0;j<nndim[0];j++)
			values[i][j]=new float[nndim[1]];
	}
}
//destructor
NS::~NS()
{
	delete[]nndim;
	//release values
	for(int i=0;i<datanum;i++)
	{
		for(int j=0;j<nndim[0];j++)
			delete[]values[i][j];
		delete[]values[i];
	}
	delete[]values;
}
