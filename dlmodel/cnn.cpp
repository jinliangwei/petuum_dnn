#include "stdafx.h"
#include "cnn.h"

ConvNeuralNet::ConvNeuralNet()
{

}

ConvNeuralNet::ConvNeuralNet(int layernum, vector<int>chnlnum, vector<Trsfm> trsfms,vector<Dependency> dpd, ImgMeta imgmeta)
{
	this->layernum=layernum;
	this->chnlnum=chnlnum;
	this->trsfms=trsfms;
	this->dpd=dpd;
	this->numimgs=imgmeta.imgnum;
	this->imgsize=imgmeta.imgsize;
	
}

ConvNeuralNet::~ConvNeuralNet()
{

}
map<int,FilterPara> ConvNeuralNet::GetFPara()
{
	return fpara;
}

void ConvNeuralNet::Learn()
{
	//forward pass
	//construct a network of NSs
	vector<vector<NeuralSet>> network;
	//construct input NS
	vector<NeuralSet> inputlayer;
	for(int i=0;i<chnlnum[0];i++)
	{
		NeuralSet inns(imgsize,numimgs);
		inputlayer.push_back(inns);
	}
	network.push_back(inputlayer);
	//construct remaining layers
	for(int l=1;l<layernum;l++)
	{
		vector<NeuralSet> layer;
		for(int i=0;i<chnlnum[l];i++)
		{
			NeuralSet ns=Map(network[l-1][0],trsfms[0] );
			layer.push_back(ns);
		}
		network.push_back(layer);
	}
	
	//forward activation
	//foreach layer
	for(int l=0;l<layernum-1;l++)
	{
		//foreach ns in the next layer
		for(int n=0;n<chnlnum[l+1];n++)
		{
			//prepare a list of input ns by checking dependency
			vector<NeuralSet> src;
			if(dpd[l].dtype==ALL2ONE)
				src=network[l];
			else if(dpd[l].dtype==ONE2ONE)
				src.push_back(network[l][n]);
			else if(dpd[l].dtype==USERDEF)
			{
				vector<int> dlist=dpd[l].user_dpd[n];
				for(int i=0;i<dlist.size();i++)
					src.push_back(network[l][dlist[i]]);
			}
			//do tranformation
			Transform(src, network[l+1][n],trsfms[l]);
		}
	}
}


CNNModel CNNWapper(int layernum, vector<int>chnlnum,vector<Trsfm>trsfms, vector<Dependency> dpd, ImgMeta imgmeta)
{
	ConvNeuralNet mycnn(layernum, chnlnum,  trsfms,dpd, imgmeta);
	mycnn.Learn();
	CNNModel model;
	model.chnlnum=chnlnum;
	model.imgsize=imgmeta.imgsize;
	model.layernum=layernum;
	model.trsfms=trsfms;
	model.dpd=dpd;
	model.fpara=mycnn.GetFPara();
	return model;
}
void TestCNN()
{
	int layernum=6;
	vector<int> chnlnum;
}




















CNN::CNN()
{

}
CNN::CNN(int dim, int datanum,int* data_size, int* filter_size, int* pool_size)
{
	this->dim=dim;
	this->datanum=datanum;
	this->filter_size=filter_size;
	this->pool_size=pool_size;
	W=new float*[filter_size[0]];
	for(int i=0;i<filter_size[0];i++)
		W[i]=new float[filter_size[1]];
}
CNN::~CNN()
{
	for(int i=0;i<filter_size[0];i++)
		delete[]W[i];
	delete []W;
}
int * CNN::GetFilterSize()
{
	return filter_size;
}
int * CNN::GetPoolSize()
{
	return pool_size;
}
float **CNN::GetW()
{
	return W;
}
