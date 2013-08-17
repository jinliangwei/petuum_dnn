//created by Pengtao Xie
#include"stdafx.h"
#include "scheduler.h"


Scheduler::Scheduler()
{

}
Scheduler::Scheduler(int numjobs, Job* jobs, map<int,int> job_status,map<int,int*> job_dpdingjobs,map<int,int> job_numdpding,
		map<int,int*>job_dpdedjobs,map<int,int>job_numdpded)
{
  this->numjobs=numjobs;
	this->jobs=jobs;
	this->job_status=job_status;
	this->job_dpdingjobs=job_dpdingjobs;
	this->job_numdpding=job_numdpding;
	this->job_dpdedjobs=job_dpdedjobs;
	this->job_numdpded=job_numdpded;

	for(int i=0;i<numjobs;i++)
		jobid_job[jobs[i].GetJobId()]=jobs[i];
}
Scheduler::~Scheduler()
{
	delete[]jobs;
	ReleaseMap(job_dpdingjobs);
	ReleaseMap(job_dpdedjobs);
}

void Scheduler::Dispatch()
{
	Job job=ready_queue.top(); //pop the top job from the ready queue
	ready_queue.pop();
	//todo 
	//dispatch(job, processor);//dispatch the job to the idle processor
	job_status[job.GetJobId()]=INPROCESSING;//set the status of this job to in processing
}

void Scheduler::ReceiveResponse()
{
	//int doneJob=Receive(processor);//receive the finished job from a processor
	int donejob;
	job_status[donejob]=DONE;// set the status of this job to finished
	
	int * dpdedjobs=job_dpdedjobs[donejob];
	int dpdedjobsnum=job_numdpded[donejob];
	//for each job which depends on the finished job
	for(int i=0;i<dpdedjobsnum;i++)
	{
		int dpdedjob=dpdedjobs[i];
		job_numdonejobs[dpdedjob]++;
		//check whether dpdedJob is ready to be dispatched
		if(job_numdonejobs[dpdedjob]==job_numdpding[dpdedjob])//ready to go
		{
			ready_queue.push(jobid_job[dpdedjob]);
			job_status[dpdedjob]=INQUEUE;
		}
	}
}