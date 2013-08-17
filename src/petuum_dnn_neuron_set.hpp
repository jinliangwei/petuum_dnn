#ifndef __PETUUM_NEURON_SET_HPP__
#define __PETUUM_NEURON_SET_HPP__

#include <stdint.h>

namespace petuum {

  struct Dimensions {
    int32_t num_dims_;
    int32_t *dims_; // size or index along each dimension
  };

  template<typename T>
  struct MultiDimensionalArray {
    Dimensions dim_size_;
    int32_t size_;
    T *data_;
  };

  // Neuron and NeuronPatch are the basic unit of computation.
  // There are currently three kinds of computations:
  // 1) one NeuronPatch -> one Neuron (filtering, pooling)
  // 2) one Neuron -> one Neuron (rectification)
  // 3) multiple NeuronPatch -> one NeuronPatch (normalization)
  // This is a logical concept and we do not necessarily need to make a class for it.

  // A NeuronSet may consist of one or multiple NeuronPartitions, each of them resides on one machine.
  // NeuronPartition is the unit of data storage and distribution.
  class NeuronPartition {
    int32_t neuron_set_id_;

  };

  // NeuronScheBlock is a logical partition of a NeuronSet.
  // A NeuronPartition may consists of one or multiple NeuronScheBlock.
  // NeuronScheBlock is the unit of scheduling and node of dependency DAG.
  // Each NeuronScheBlock may consists of multiple NeuronPatch or part of a NeuronPatch.
  // Note that NeuronPartition or NeuronScheBlock is not necessarily partitioned along NeuronPatch boundaries, especially as NeuronPatchs may overlap.
  class NeuronScheBlock {
    int32_t neuron_set_id_;
    bool is_local_; // if the NeuronScheBlock resides on the same machine
    Dimensions dim_; // starting index along each dimensions

    float *neurons_; // set to NULL if the NeuronScheBlock is not local and data of it is not received

    MultiDimensionalArray GetData(Dimensions _dim);

  };

  class NeuronSet {
    Dimensions dim_;

    // contains logic for deciding how NeuronSet are split into partitions
    // contains logic for deciding which NeuronPartition a given NeuronScheBlock belongs to
  };

  class NeuronSetGlobal : public NeuronSet {


  };

  class NeuronSetClient : public NeuronSet {

  };
}
#endif
