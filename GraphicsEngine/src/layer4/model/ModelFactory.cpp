/*
 * ModelFactory.cpp
 *
 *  Created on: 04.09.2012
 *      Author: nopper
 */

#include "../../layer2/mesh/MeshFactory.h"
#include "../../layer3/node/Node.h"
#include "../../layer3/node/NodeTreeFactory.h"

#include "ModelFactory.h"

using namespace std;

ModelFactory::ModelFactory()
{
}

ModelFactory::~ModelFactory()
{
}

ModelSP ModelFactory::createModel(const string& name, const BoundingSphere& boundingSphere, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial) const
{
	vector<AnimationStackSP> allAnimStacks;
	bool joint = false;

	MeshFactory meshFactory;

	MeshSP mesh = meshFactory.createMesh(shape, surfaceMaterial);

	NodeTreeFactory nodeTreeFactory;

	NodeSP node = nodeTreeFactory.createNode(name, "", mesh, allAnimStacks, joint);

	return ModelSP(new Model(boundingSphere, node, 0, false, false));
}

ModelSP ModelFactory::createModel(const string& name, const BoundingSphere& boundingSphere, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial, const vector<AnimationStackSP>& allAnimStacks) const
{
	bool joint = false;

	MeshFactory meshFactory;

	MeshSP mesh = meshFactory.createMesh(shape, surfaceMaterial);

	NodeTreeFactory nodeTreeFactory;

	NodeSP node = nodeTreeFactory.createNode(name, "", mesh, allAnimStacks, joint);

	return ModelSP(new Model(boundingSphere, node, 0, true, false));
}
