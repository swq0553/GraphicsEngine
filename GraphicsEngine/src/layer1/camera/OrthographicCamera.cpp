/*
 * OrthographicCamera.cpp
 *
 *  Created on: 14.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera() : Camera()
{
	updateProjectionMatrix();
}

OrthographicCamera::OrthographicCamera(const OrthographicCamera& other) : Camera(other)
{
	updateProjectionMatrix();
}

OrthographicCamera::~OrthographicCamera()
{
}

void OrthographicCamera::updateProjectionMatrix()
{
	orthographic(viewport, zNear, zFar);
}

void OrthographicCamera::orthographic(const Viewport& viewport, float nearVal, float farVal)
{
	float result[16];

	this->viewport = viewport;
	this->zNear = zNear;
	this->zFar = zFar;

	float horizontal = static_cast<float>(viewport.getWidth()) / 2.0f;
	float vertical = static_cast<float>(viewport.getHeight()) / 2.0f;

	glusOrthof(result, -horizontal, horizontal, -vertical, vertical, nearVal, farVal);

	projectionMatrix.setM(result);

	biasedProjectionMatrix = biasMatrix * projectionMatrix;

	updateViewFrustum();
}
