/*
 * LineGeometryVAO.h
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#ifndef LINEGEOMETRYVAO_H_
#define LINEGEOMETRYVAO_H_

#include "../../UsedLibs.h"

#include "../../layer0/shader/Program.h"
#include "../../layer0/shader/VAO.h"

class LineGeometry;

class LineGeometryVAO : public VAO {
public:
	LineGeometryVAO(const ProgramSP& program, const LineGeometry& lineGeometry);
	virtual ~LineGeometryVAO();
};

typedef boost::shared_ptr<LineGeometryVAO> LineGeometryVAOSP;

#endif /* LINEGEOMETRYVAO_H_ */
