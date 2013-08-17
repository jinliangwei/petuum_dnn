//created by Pengtao Xie
#include "stdafx.h"
#include "job.h"

//constructor
Job::Job()
{
}
Job::Job(int jobid, float priority)
{
	this->jobid=jobid;
	this->priority=priority;
}
//get operations
int Job::GetJobId()
{
	return jobid;
}
float Job::GetPriority()
{
	return priority;
}
void Job::SetJobId(int jobid)
{
	this->jobid=jobid;
}
void Job::SetPriority(float priority)
{
	this->priority=priority;
}

void ComputePriority()
{

}
bool operator<(Job j1, Job j2)
{
	return j1.priority<j2.priority;
}