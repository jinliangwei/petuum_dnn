//created by Pengtao Xie
#include "stdafx.h"
#include "netclass.h"
#include "transformations.h"
#include <vector>
#include <map>
using namespace std;

struct CNNModel
{
	//number of layers
	int layernum;
	//number of channels in each layer
	vector<int> chnlnum;
	//tranformations between adjacent layers
	vector<Trsfm> trsfms;
	//image size
	Size imgsize;
	//filter parameters
	map<int,FilterPara> fpara;
	//dependency
	vector<Dependency> dpd;

};

class ConvNeuralNet
{
private:
	//number of layers
	int layernum;
	//number of channels in each layer
	vector<int> chnlnum;
	//tranformations between adjacent layers
	vector<Trsfm> trsfms;
	//image size
	Size imgsize;
	//image number
	int numimgs;
	//filter parameters
	map<int,FilterPara> fpara;
	//dependency
	vector<Dependency> dpd;

public:
	//constructors and destructor
	ConvNeuralNet();
	ConvNeuralNet(int layernum, vector<int>chnlnum, vector<Trsfm> trsfms, vector<Dependency> dpd, ImgMeta imgmeta);
	~ConvNeuralNet();
	//get and set
	map<int,FilterPara> GetFPara();
	//learn
	void Learn();
};
CNNModel CNNWapper(int layernum, vector<int>chnlnum,vector<Trsfm>trsfms, ImgMeta imgmeta);






















//convolutional neural networvector<Dependency> dpd,quare image, square filter, nonoverlap pool, one layer filter and one layer pool
class CNN
{
private:
	int dim;
	int datanum;
	//data size
	int * data_size;
	int *filter_size;
	//convolution weights
	float **W;
	//bias
	float b;
	
	//pooling size
	int *pool_size;

public:
	//constructor
	CNN();
	CNN(int dim,int datanum,int *datasize, int *filter_size, int *pool_size);
	//destructor
	~CNN();
	//get operations
	int* GetFilterSize();
	int* GetPoolSize();
	float **GetW();

	//learn
	void learn();
};
void CNN::learn()
{
	//load input data
	
	//construct the network
	//input layer id 0
	int *input_nndim=new int[dim];
	input_nndim[0]=data_size[0];
	input_nndim[1]=data_size[1];
	NS *input_layer=new NS(0, dim, input_nndim, datanum);
	//filter layer id 1
	int *filter_nndim=new int[dim];
	filter_nndim[0]=input_nndim[0]-filter_size[0]+1;
	filter_nndim[1]=input_nndim[1]-filter_size[1]+1;
	NS *filter_layer=new NS(1,dim, filter_nndim, datanum);
	//pool layer id 2
	int *pool_nndim=new int[dim];
	pool_nndim[0]=filter_nndim[0]/pool_size[0];
	pool_nndim[1]=filter_nndim[1]/pool_size[1];
	NS *pool_layer=new NS(2,dim, pool_nndim,datanum);

	//forward pass
	//filtering
	//Filter(input_layer, filter_layer,  W,b, filter_size, LOGISTIC);
	//pooling

	//clean up
	delete[]filter_nndim;
	delete[]input_nndim;
	delete[]pool_nndim;
	delete[]data_size;
}

void TestCNN2D()
{
	//200 images 2d 100-by-100 10-by-10, 5-by-5
	int dim=2;
	int datanum=200;
	int *datasize=new int[2];
	datasize[0]=100;
	datasize[1]=100;
	int *filtersize=new int[2];
	filtersize[0]=10;
	filtersize[1]=10;
	int *poolsize=new int[2];
	poolsize[0]=5;
	poolsize[1]=5;

	CNN * mycnn=new CNN(dim,datanum,datasize,filtersize,poolsize);
	mycnn->learn();
	//clean up
	delete[]datasize;
	delete[]filtersize;
	delete[]poolsize;
}