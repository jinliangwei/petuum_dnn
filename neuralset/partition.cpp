//created by Pengtao Xie
#include "stdafx.h"
#include "partition.h"
Partition::Partition()
{

}
Partition::Partition(string ptid,int mid, string nsid,pair<int,int> offset,Size sz, int datanum)
{
  this->ptid=ptid;
  this->mid=mid;
  this->nsid=nsid;
  this->offset=offset;
  this->sz=sz;
  this->datanum=datanum;
}
Partition::~Partition()
{

}

//get function and set function
string Partition::GetPtid()
{
  return ptid;
}
int Partition::GetMid()
{
  return mid;
}
string Partition::GetNsid()
{
  return nsid;
}
pair<int,int> Partition::GetOffset()
{
  return offset;
}
Size Partition::GetSz()
{
  return sz;
}
int Partition::GetDatanum()
{
  return datanum;
}
void Partition::SetPtid(string ptid)
{
  this->ptid=ptid;
}
void Partition::SetMid(int mid)
{
  this->mid=mid;
}
void Partition::SetNsid(string nsid)
{
  this->nsid=nsid;
}
void Partition::SetOffset(pair<int,int> offset)
{
  this->offset=offset;
}
void Partition::SetSz(Size sz)
{
  this->sz=sz;
}
void Partition::SetDatanum(int datanum)
{
  this->datanum=datanum;
}