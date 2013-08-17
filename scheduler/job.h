//created by Pengtao Xie
#include "stdafx.h"

//job class
class Job
{
private:
	int jobid;//jobId
	float priority;//priority of this job
public:
	//constructor
	Job();
	Job(int jobid, float priority);
	//get operations
	int GetJobId();
	float GetPriority();
	void SetJobId(int jobid);
	void SetPriority(float priority);
	//compute priority
	void ComputePriority();
	//compare two jobs based on priority
	friend bool operator<(Job j1, Job j2);
};

