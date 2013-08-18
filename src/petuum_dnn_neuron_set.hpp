#ifndef __PETUUM_NEURON_SET_HPP__
#define __PETUUM_NEURON_SET_HPP__

#include <stdint.h>
#include <boost/unordered_map.hpp>
#include <boost/scoped_array.hpp>

namespace petuum {
  class NeuronScheBlock;
  class NeuronSetInternal;

  class Transformation {
    // the type of transformation:
    // 1) one patch to one neuron - filtering (overlapped patches) / pooling (non-overlapped patches)
    // 2) multiple patches to one patch - normalization
    // 3) one neuron to one neuron - rectification

    // patch size and overlap information

    // The transformation transforms a NeuronSet to another. In other words, the transformation is 1-to-1.
    // Given the original NeuronSet and the Transformation, the dimensions of the resulting NeuronSet and the dependencies between the two NeuronSets'
    // NeuronScheBlocks can be determined.
  };

  enum ENSAggregateType {Add};

  class NeuronSetLineage {

    int num_parents_; // set t 0 if the NeuronSet is directly read from file (like images)
    boost::scoped_array<int32_t> parent_ids_;
    Transformation trans_;

    ENSAggregateType aggreg_; // defines how each NeuronSet resulted from transforming a parent NeuronSet are combined together
                              // only effective when num_parents_ > 1.

    //TODO: add copy constructor - parent_ids_ should be deep copied
  };

  template<typename T>
  struct MultiDimensionalArray {
    int32_t num_dims_;
    int32_t dim_size_; // sizes along each dimensions
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
    int32_t host_id_;
    int32_t num_sche_blocks_;
    boost::scoped_array<int32_t> sche_block_dims_;

    //TODO: constructor
  };

  // NeuronScheBlock is a logical partition of a NeuronSet.
  // A NeuronPartition may consists of one or multiple NeuronScheBlock.
  // NeuronScheBlock is the unit of scheduling and node of dependency DAG.
  // Each NeuronScheBlock may consists of multiple NeuronPatch or part of a NeuronPatch.
  // Note that NeuronPartition or NeuronScheBlock is not necessarily partitioned along NeuronPatch boundaries, especially as NeuronPatchs may overlap.
  class NeuronScheBlock {
  private:
    int32_t neuron_set_id_;
    bool is_local_; // if the NeuronScheBlock resides on the same machine
    int32_t num_dims_;
    boost::scoped_array<int32_t> dim_size_;

    int32_t num_neurons_;
    int32_t num_updated_neurons_;

    int32_t clock_; // version of this block

    // block access to copy constructor
    NeuronScheBlock(NeuronScheBlock _nsb);

  public:

    // 0 if the updates are accepted
    // 1 if the updates are accepted and brings the NeuronScheBlock to READY state
    // negative if error
    // If a NeuronScheBlock is updated or not completely depends on the number of updated neurons.
    // so the scheduler should make sure all neurons are updated.
    int UpdateNeurons(int32_t _num_updated);

  };

  class NeuronSetInternal {
  private:
    int32_t num_dims_;
    boost::scoped_array<int32_t> dim_size_; // size along each dimensions

    // partition related
    boost::scoped_array<int32_t> partition_size_;
    boost::scoped_array<int32_t> partition_overlap_;
    boost::scoped_array<NeuronPartition> partitions_;

    NeuronSetLineage lineage_;
    int level_;

    int GetNeurons(MultiDimensionalArray &_data);
    float GetOneNeuron(int32_t _num_dims, int32_t *_indices);

    int SetNeurons(const MultiDimensionalArray &data);
    int SetNeuron(const int32_t *_indices);

    int SetLineage(const NeuronSetLineage &_lineage);

    int Partition();

  };
}
#endif
