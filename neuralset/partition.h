//created by Pengtao Xie
#include "stdafx.h"
#include "auxds.h"
#include <string>
using namespace std;
#ifndef PARTITION_H
#define PARTITION_H
//class partition
//partition is a rectangular region of neural set
//each neural set consists of multiple nonoverlap partitions
//partitions are distribued in different machines.
class Partition
{
private:
  string ptid;//partition id;
  int mid;//id of machine where the partition is in
  string nsid;//id of neural set to which the partition belongs
  pair<int,int> offset;//offset in neural set
  Size sz;//partition size
  int datanum;//number of data instances
  //data
  float ** data;//change this to Jinliang's interface
public:
  //constructor 
  Partition();
  Partition(string ptid,int mid, string nsid,pair<int,int> offset,Size sz, int datanum);
  //destructor
  ~Partition();

  //get function and set function
  string GetPtid();
  int GetMid();
  string GetNsid();
  pair<int,int> GetOffset();
  Size GetSz();
  int GetDatanum();
  void SetPtid(string ptid);
  void SetMid(int mid);
  void SetNsid(string nsid);
  void SetOffset(pair<int,int> offset);
  void SetSz(Size sz);
  void SetDatanum(int datanum);
};


#endif
