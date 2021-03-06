#include "GraphicsEngine.h"

using namespace std;

GLUSboolean initGame(GLUSvoid)
{
	if (!initEngine(GLUS_LOG_INFO, 7))
	{
		return GLUS_FALSE;
	}

	OctreeFactory octreeFactory;
	OctreeSP octree = octreeFactory.createOctree(6, 1024, Point4(), 256.0f, 256.0f, 256.0f);
	ModelEntityManager::getInstance()->setOctree(octree);
	//octree->setDebug(true);

	PrimitiveEntityFactory primitiveEntityFactory;

	FbxEntityFactory entityFactory;

	ModelEntitySP entity;

	SurfaceMaterialFactory surfaceMaterialFactory;
	SurfaceMaterialSP surfaceMaterial;

	AnimationLayerSP animationLayer;
	vector<AnimationStackSP> allAnimStacks;

	Point4 position;

	string filename;

	// Red sphere

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Red", Color::RED);
	position = Point4(0.0f, 0.0f, -4.0f);

	entity = primitiveEntityFactory.createSpherePrimitiveEntity("RedSphere", 1.0f, 1.0f, 1.0f, surfaceMaterial);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Green torus

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Green", Color::GREEN);
	position = Point4(4.0f, 4.0f, -8.0f);

	entity = primitiveEntityFactory.createTorusPrimitiveEntity("GreenTorus", 1.0f, 1.0f, 1.0f, surfaceMaterial);
	entity->setPosition(position);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Blue cube

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Blue", Color::BLUE);
	position = Point4(8.0f, 8.0f, -12.0f);

	entity = primitiveEntityFactory.createCubePrimitiveEntity("BlueCube", 1.0f, 1.0f, 1.0f, surfaceMaterial);
	entity->setPosition(position);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Yellow cone

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Yellow", Color::YELLOW);
	position = Point4(12.0f, 12.0f, -16.0f);

	entity = primitiveEntityFactory.createConePrimitiveEntity("YellowCone", 1.0f, 1.0f, 1.0f, surfaceMaterial);
	entity->setPosition(position);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Cyan cylinder

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Cyan", Color::CYAN);
	position = Point4(16.0f, 16.0f, -24.0f);

	entity = primitiveEntityFactory.createCylinderPrimitiveEntity("CyanCylinder", 1.0f, 1.0f, 1.0f, surfaceMaterial);
	entity->setPosition(position);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Black sphere with emissive color animation

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Black", Color::BLACK);
	position = Point4(20.0f, 20.0f, -32.0f);

	animationLayer = AnimationLayerSP(new AnimationLayer());
	animationLayer->addEmissiveColorValue(AnimationLayer::R, 0.0f, 0.0f, LinearInterpolator::interpolator);
	animationLayer->addEmissiveColorValue(AnimationLayer::R, 1.0f, 1.0f, LinearInterpolator::interpolator);
	animationLayer->addEmissiveColorValue(AnimationLayer::R, 2.0f, 0.0f, LinearInterpolator::interpolator);
	allAnimStacks.push_back(AnimationStackSP(new AnimationStack(0.0f, 2.0f)));
	allAnimStacks[0]->addAnimationLayer(animationLayer);

	entity = primitiveEntityFactory.createSpherePrimitiveEntity("BlackSphere", 1.0f, 1.0f, 1.0f, surfaceMaterial, allAnimStacks);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Textured cube with rotation animation

	Texture2DSP cubeTexture = Texture2DManager::getInstance()->createTexture("crate.tga");
	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Crate", Color::DEFAULT_EMISSIVE, Color::DEFAULT_AMBIENT, Color::DEFAULT_DIFFUSE, cubeTexture, Color::DEFAULT_SPECULAR, 0.0f);
	position = Point4(24.0f, 24.0f, -40.0f);

	animationLayer = AnimationLayerSP(new AnimationLayer());
	animationLayer->addRotationValue(AnimationLayer::Y, 0.0f, 0.0f, LinearInterpolator::interpolator);
	animationLayer->addRotationValue(AnimationLayer::Y, 5.0f, 360.0f, LinearInterpolator::interpolator);
	allAnimStacks.clear();
	allAnimStacks.push_back(AnimationStackSP(new AnimationStack(0.0f, 5.0f)));
	allAnimStacks[0]->addAnimationLayer(animationLayer);

	entity = primitiveEntityFactory.createCubePrimitiveEntity("CrateCube", 5.0f, 5.0f, 5.0f, surfaceMaterial, allAnimStacks);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	//entity->setDebug(true);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Humanoids

	position = Point4(-10.0f, 10.0f, -16.0f);

	filename = "humanoid.fbx";
	entity = entityFactory.loadFbxFile("Humanoid0", filename, 0.01f);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	//entity->setDebug(true);

	ModelEntityManager::getInstance()->updateEntity(entity);

	//

	position = Point4(-20.0f, 10.0f, -16.0f);

	entity = entity->getNewInstance("Humanoid1");
	entity->setPosition(position);
	entity->setAnimation(1, 0);

	//entity->setDebug(true);

	ModelEntityManager::getInstance()->updateEntity(entity);

	//

	position = Point4(-30.0f, 10.0f, -16.0f);

	entity = entity->getNewInstance("Humanoid1");
	entity->setPosition(position);
	entity->setAnimation(2, 0);

	//entity->setDebug(true);
	//entity->setDebugAsMesh(true);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Lights

	Color ambient(0.5f, 0.5f, 0.5f, 1.0f);
	Color specular(0.5f, 0.5f, 0.5f, 1.0f);

	LightSP directionalLight = LightSP(new DirectionalLight(Vector3(0.0f, 0.0f, 1.0f), ambient, Color::WHITE, specular));
	LightManager::getInstance()->setLight("DirectionalLight", directionalLight);
	LightSP pointLight = LightSP(new PointLight(Point4(0.0f, 0.0f, 5.0f), 1.0f, 0.0f, 0.0f, ambient, Color::WHITE, specular));
	LightManager::getInstance()->setLight("PointLight", pointLight);
	LightSP spotLight = LightSP(new SpotLight(Vector3(0.0f, 0.0f, -1.0f), 0.5f, 2.0f, Point4(0.0f, 0.0f, 10.0f), 1.0f, 0.0f, 0.0f, ambient, Color::WHITE, specular));
	LightManager::getInstance()->setLight("SpotLight", spotLight);

	ProgramManagerProxy::setLightByType(ProgramManager::DEFAULT_PROGRAM_TYPE, directionalLight);

	//

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	glClearDepth(1.0f);

	return GLUS_TRUE;
}

GLUSvoid reshapeGame(GLUSint width, GLUSint height)
{
	reshapeEngine(width, height);
}

GLUSboolean updateGame(GLUSfloat deltaTime)
{
	if (!updateEngine(deltaTime))
	{
		return GLUS_FALSE;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera());

	ModelEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false);
	ModelEntityManager::getInstance()->updateMetrics();
	ModelEntityManager::getInstance()->sort();
	ModelEntityManager::getInstance()->update();
	ModelEntityManager::getInstance()->render();

	FpsPrinter::printer.print(deltaTime);

	return GLUS_TRUE;
}

GLUSvoid terminateGame(GLUSvoid)
{
	terminateEngine();
}

GLUSvoid mouseButtonGame(GLUSboolean pressed, GLUSint button, GLUSint xPos, GLUSint yPos)
{
	glusLogPrint(GLUS_LOG_DEBUG, "mouseButton %d %d %d %d", pressed, button, xPos, yPos);
	mouseButtonEngine(pressed, button, xPos, yPos);
}

GLUSvoid mouseWheelGame(GLUSint buttons, GLUSint ticks, GLUSint xPos, GLUSint yPos)
{
	glusLogPrint(GLUS_LOG_DEBUG, "mouseWheel %d %d %d %d", buttons, ticks, xPos, yPos);
	mouseWheelEngine(buttons, ticks, xPos, yPos);
}

GLUSvoid mouseMoveGame(GLUSint buttons, GLUSint xPos, GLUSint yPos)
{
	glusLogPrint(GLUS_LOG_DEBUG, "mouseMove %d %d %d", buttons, xPos, yPos);
	mouseMoveEngine(buttons, xPos, yPos);
}

GLUSvoid keyGame(GLUSboolean pressed, GLUSint key)
{
	glusLogPrint(GLUS_LOG_DEBUG, "key %d %d %c", pressed, key, (char)key);
	keyEngine(pressed, key);
}

int main(int argc, char* argv[])
{
	glusInitFunc(::initGame);
	glusReshapeFunc(::reshapeGame);
	glusUpdateFunc(::updateGame);
	glusTerminateFunc(::terminateGame);
	glusMouseFunc(::mouseButtonGame);
	glusMouseWheelFunc(::mouseWheelGame);
	glusMouseMoveFunc(::mouseMoveGame);
	glusKeyFunc(::keyGame);

	glusPrepareContext(4, 2, GLUS_FORWARD_COMPATIBLE_BIT);
	glusPrepareMSAA(8);
	glusPrepareNoResize(GLUS_TRUE);
	if (!glusCreateWindow("OpenGL Graphics Engine", 1024, 768, 24, 8, GLUS_FALSE))
	{
		return -1;
	}

	glusLogPrint(GLUS_LOG_INFO, "Initialization complete");

	glusRun();

	return 0;
}
