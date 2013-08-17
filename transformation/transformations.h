#include "stdafx.h"
#include "netclass.h"
#include "auxds.h"

//transformations
Size ComputeSize(Size src, Trsfm t);

NeuralSet Map(NeuralSet src, Trsfm t);

void Transform(vector<NeuralSet>src, const NeuralSet & dst,Trsfm t);
//user defined
void Map2d(int x,int y, int & x1,int & x2, int& y1, int& y2 );
void Map1d(int x,int &x1,int &x2);

//build connection relationship
void Conn(Point src, Point * range, int dim);
//map multiple src NSs to one dst NS
void MapNS(NS ** src, NS *dst,int numsrcs, int trans_type,int operate_type, int * win_size, float *** W,float b);
//filtering
void Filter(NS * src, NS *dst);
//a special case, 2d convoluation, logistic activation
void Filter(NS * src, NS *dst,int filter_type,  int * filter_size,float ** W,float b);
//filter multiple src NSs to a dst NS
void Filter(NS ** src, NS *dst,int numsrcs,int filter_type, int * filter_size,float *** W,float b);
//pooling
void Pool(NS * src, NS * dst);
void Pool(NS * src, NS * dst, int * pool_size, int pool_type);
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
