//created by Pengtao Xie
#include "stdafx.h"
#include "auxds.h"
#include "partition.h"
#include <vector>
using namespace std;
#ifndef NetClass_H
#define NetClass_H

class NeuralSet
{
private: 
  //neuralset id
  string nsid;
	Size setsize;
	int datanum;
  //number of parts along each dimension
  pair<int,int> numpts;//this should be a global value set by system and invisible to programmer
  //a list of partitions
  vector<Partition> partitions;
public:
	NeuralSet();
	NeuralSet(string nsid,Size setsize,int datanum);
	~NeuralSet();
  void SetNsid(string);
	void SetSize(Size);
	void SetDataNum(int);
  string GetNsid();
	Size GetSize();
	int GetDataNum();
  vector<Partition> GetPartitions();
  //break the neural set into partitions
  void CreatePartitions();
};



//neural set class
class NS
{	
private: 
	int nsid;//NS id
	int dim;//dim of NS -- for now, the max dim is 2
	int * nndim;//number of neurons along each dimension
	int datanum;//number of data instances
	float *** values;//neuron values

public :
	//constructor
	NS();
	NS(int nsid, int dim, int * nndim, int datanum);
	//destructor
	~NS();

	//get operations
	int GetNSId();//get NS id
	int GetDim();//get NS dim
	int GetDataNum();//get number of data instances
	int * GetNNDim();//get number of neurons along each dimension
	float *** GetValues();//get neurons values

	//set operations
	void SetNSId(int nsId);//set NS id
	void SetDim(int dim);//set NS dim
	void SetDataNum(int dataNum);//set number of data instances
	void SetNNDim(int * nnDim);//set number of neurons along each dimension

	
};
#endif