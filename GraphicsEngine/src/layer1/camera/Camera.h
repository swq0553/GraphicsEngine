/*
 * Camera.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Geometry.h"
#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Quaternion.h"
#include "../../layer0/math/Vector3.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer0/shader/Program.h"
#include "ViewFrustum.h"
#include "Viewport.h"

class Camera
{

protected:

	Point4 eye;
	Point4 center;
	Vector3 up;
	Vector3 direction;
	Matrix4x4 viewMatrix;

	Viewport viewport;
	float zNear;
	float zFar;
	Matrix4x4 projectionMatrix;
	Matrix4x4 biasedProjectionMatrix;
	Matrix4x4 biasMatrix;

	ViewFrustum viewFrustum;

	void updateViewFrustum();

public:

	Camera();
	Camera(const Camera& other);
	virtual ~Camera();

    void setPosition(const Point4& position);
    void setRotation(float angleZ, float angleY, float angleX);
    void setRotation(const Quaternion& rotation);
    void setPositionRotation(const Point4& position, const Quaternion& rotation);

	void lookAt(const Point4& eye, const Point4& center, const Vector3& up);

	virtual void updateProjectionMatrix() = 0;

	void updateViewport(const Viewport& viewport);

	const Point4& getEye() const;

	const Vector3& getDirection() const;

	const Matrix4x4& getViewMatrix() const;

	const Matrix4x4& getProjectionMatrix() const;

	const Matrix4x4& getBiasedProjectionMatrix() const;

	/**
	 * View Frustum is in world space.
	 */
	const ViewFrustum& getViewFrustum() const;

	float distanceToCamera(const BoundingSphere& boundingSphere) const;

	void setCameraProperties(const ProgramSP& program) const;

	//

	virtual void updateLocation(const Point4& location);

	virtual void updateOrientation(const Quaternion& orientation);

	virtual void updateLocationOrientation(const Point4& location, const Quaternion& orientation);

};

typedef boost::shared_ptr<Camera> CameraSP;

#endif /* CAMERA_H_ */
