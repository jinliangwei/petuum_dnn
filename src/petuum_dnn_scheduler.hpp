/*
 * petuum_dnn_scheduler.hpp
 *
 *  Created on: Aug 17, 2013
 *      Author: jinliang
 */

#ifndef __PETUUM_DNN_SCHEDULER_HPP__
#define __PETUUM_DNN_SCHEDULER_HPP__

namespace petuum {

 /* global scheduler work flow:
  * 1) Get a list of NeuronSets and their lineage as described in terms of NeuronPatch and neurons
  * 2) For each NeuronSet, decide if it should be partitioned and do the partition.
  * 3) Aggregate the message about NeuronSet partitioning and distributed it to
  *
  */

};


#endif /* PETUUM_DNN_SCHEDULER_HPP_ */
