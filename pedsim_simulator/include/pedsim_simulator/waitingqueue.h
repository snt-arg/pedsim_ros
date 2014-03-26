/**
* Copyright 2014 Social Robotics Lab, University of Freiburg
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*    # Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*    # Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*    # Neither the name of the University of Freiburg nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* \author Billy Okal <okal@cs.uni-freiburg.de>
*/

#ifndef WAITING_QUEUE_H
#define WAITING_QUEUE_H

#include <pedsim_simulator/agent.h>
#include <pedsim_simulator/utilities.h>
#include <pedsim_simulator/waypoint.h>

#include <deque>


/// -----------------------------------------------------------------
/// \class WaitingQueue
/// \brief Simple queue model for pedestrians
/// Queues are modelled as locations which attract pedestrians and 
/// 'serve them' after a random wait time.
/// -----------------------------------------------------------------
class WaitingQueue
{
public:
    WaitingQueue();
    WaitingQueue ( const double x, const double y );
    WaitingQueue ( const double x, const double y, const double theta, std::string
                   id );
    ~WaitingQueue();

    void enqueueAgent ( Agent* a );
    void serveAgent();
    bool agentInQueue ( Agent* a );
	Agent* pickAgent( std::list<Agent*> neighbors, double x, double y );

public:
    // set of quickies
    void setWaitTime ( int wtime )
    {
        wait_time_ = wtime;
    }
    void setOrientation ( double theta )
    {
        theta_ = theta;
    }
    void setLocation ( double x, double y )
    {
        x_ = x;
        y_ = y;
    }

    int getWaitTime()
    {
        return wait_time_;
    }
    double getOrientation()
    {
        return theta_;
    }
    double getX()
    {
        return x_;
    }
    double getY()
    {
        return y_;
    }
    int getId()
    {
        return id_;
    }
    double getRadius()
	{
		return radius_;
	}
	
	double getThreshold()
	{
		return threshold_;
	}
	double getAlpha()
	{
		return alpha_;
	}
	
	int length()
	{
		return queueing_agents_.size();
	}
	
	Agent* lastPedestrian()
	{
		return queueing_agents_.back();
	}

private:
    // queue service location
    double x_, y_;

    std::string name_;
    int id_;

    // queue direction and angular range
    double theta_;
	double alpha_;
	
	// queue radius
	double radius_;
	
	// queue pick threshold
	double threshold_;

    // average wait time per person
    int wait_time_;

    // time passed since last service
    int time_passed_;

    std::deque<Agent*> queueing_agents_;
	
	// NOTE - maybe keep a list of 'queue' waypoints?

    void updateQueue ( double px, double py );
    void releaseAgent ( Agent* a );
    Ped::Tvector getQueueEnd();
};


typedef boost::shared_ptr<WaitingQueue> WaitingQueuePtr;
typedef boost::shared_ptr<WaitingQueue const> WaitingQueueConstPtr;


#endif