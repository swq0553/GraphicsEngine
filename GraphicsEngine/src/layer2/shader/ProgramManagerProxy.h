/*
 * ProgramManagerProxy.h
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#ifndef PROGRAMMANAGERPROXY_H_
#define PROGRAMMANAGERPROXY_H_

#include "../../layer0/math/Matrix4x4.h"
#include "../../layer1/camera/Camera.h"
#include "../../layer1/light/Light.h"

class ProgramManagerProxy
{

private:

	ProgramManagerProxy();
	~ProgramManagerProxy();

public:

	static void setLightByType(const std::string& programType, const LightSP& light);

	static void setCameraByType(const std::string& programType, const CameraSP& camera);

};

#endif /* PROGRAMMANAGERPROXY_H_ */
