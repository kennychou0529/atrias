#ifndef __ASC_SPRING_TORQUE_H__
#define __ASC_SPRING_TORQUE_H__

/*! \file controller_component.h
 *  \author Ryan Van Why
 *  \brief Orocos Component header for the asc_spring_torque subcontroller.
 */

// Orocos
#include <rtt/os/main.h>
#include <rtt/RTT.hpp>
#include <rtt/Logger.hpp>
#include <rtt/TaskContext.hpp>
#include <rtt/Component.hpp>

// C
#include <stdlib.h>

// Our stuff
#include <asc_spring_torque/controller_log_data.h>
#include <atrias_asc_loader/ASCLoader.hpp>

// Actual data.
#include "processed_data.h"

using namespace RTT;
using namespace Orocos;
using namespace asc_spring_torque;

namespace atrias {
namespace controller {

class ASCSpringTorque : public TaskContext {
	private:
		// Operations
		double getConst(double defl);
		double getTorque(double deflection);
		double getDeflection(double Torque);

		// These load and unload our subcontrollers.
		ASCLoader linearInterp0SubCont;
		ASCLoader linearInterp1SubCont;
		
		// Subcontroller components
		TaskContext *linearInterp0;
		TaskContext *linearInterp1;
		
		// Subcontroller operations
		OperationCaller<void(double samples[], int, double, double, bool)> linearInterp0InputPoints;
		OperationCaller<double(double)> linearInterp0GetValue;
		OperationCaller<void(double samples[], int, double, double, bool)> linearInterp1InputPoints;
		OperationCaller<double(double)> linearInterp1GetValue;
		
		// Logging
		OutputPort<controller_log_data> logPort;
		
	public:
		// Constructor
		ASCSpringTorque(std::string name);
		
		// Standard Orocos hooks
		bool configureHook();
		bool startHook();
		void updateHook();
		void stopHook();
		void cleanupHook();
};

}
}

#endif