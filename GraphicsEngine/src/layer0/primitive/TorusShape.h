/*
 * TorusShape.h
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#ifndef TORUSSHAPE_H_
#define TORUSSHAPE_H_

#include "Shape.h"

class TorusShape : public Shape
{

public:

	TorusShape(float innerRadius, float outerRadius, boost::uint32_t numberSlices, boost::uint32_t numberStacks);
	virtual ~TorusShape();

};

#endif /* TORUSSHAPE_H_ */
