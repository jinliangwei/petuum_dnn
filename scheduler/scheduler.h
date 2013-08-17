//created by Pengtao Xie
#include "stdafx.h"
#include "job.h"
#include "util.h"
#include "auxds.h"
#include <map>
#include <queue>

using namespace std;
//scheduler

class Scheduler
{
private:
	int numjobs;//number of jobs
	Job * jobs;//job list
	map<int,Job> jobid_job;//jobid job
	map<int,int> job_status;//job status
	map<int,int*> job_dpdingjobs;//job - depending jobs
	map<int,int> job_numdpding;//job - number of depending jobs
	map<int,int*>job_dpdedjobs;//job - depended jobs
	map<int,int>job_numdpded;//job- number of depended jobs
	map<int,int> job_numdonejobs;//job - number of finished depending jobs
	priority_queue<Job> ready_queue;//ready queue
public:
	//constructor
	Scheduler();
	Scheduler(int numjobs, Job* jobs, map<int,int> job_status,map<int,int*> job_dpdingjobs,map<int,int> job_numdpding,
		map<int,int*>job_dpdedjobs,map<int,int>job_numdpded);
	//destructor
	~Scheduler();
	//dispatch job to processor
	void Dispatch();
	//receive response from processor
	void ReceiveResponse();
};