/*
 * petuum_dnn_scheduler.hpp
 *
 *  Created on: Aug 17, 2013
 *      Author: jinliang
 */

#ifndef __PETUUM_DNN_SCHEDULER_HPP__
#define __PETUUM_DNN_SCHEDULER_HPP__

#include <boost/unordered_map.hpp>

#include "petuum_dnn_neuron_set.hpp"

namespace petuum {

 /* global scheduler work flow:
  * 1) Get a list of NeuronSets and their lineage as described in terms of NeuronPatch and neurons
  * 2) For each NeuronSet, decide if it should be partitioned and do the partition.
  * 3) Aggregate the message about NeuronSet partitioning and distributed it to
  *
  */

  class GlobalScheduler {

    std::vector<NeuronSetInternal> neuron_sets_;

    // register a group of NeuronSets
    int RegisterNeuronSets(int32_t _num_neuron_sets, NeuronSetInternal *_neuron_sets);

    // While setting the transformation, the dimensions and lineage of the NeuronSet is set
    // Thus the NeuronSet is also partitioned. But the dependency graph is not built.
    int SetTransformation(int32_t _neuronset_id, const Transformation &_trans);

  };

  // In order to support single machine (one process, multiple threads) and multiple machines (multiple processes),
  // we let GlobalScheduler talks to LocalScheduler through a proxy which provides a uniform interface for both cases
  // but does different things.
  class SchedulerProxy {};

  class LocalScheduler {
    // need to keep track of all local and some external scheduling blocks
    // need to keep track of their dependencies (bi-directional) and if the dependencies are ready.
  };

};


#endif /* PETUUM_DNN_SCHEDULER_HPP_ */
