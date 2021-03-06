/*
 * ModelManager.cpp
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#include "ModelManager.h"

using namespace std;

ModelManager* ModelManager::instance;

ModelManager::ModelManager() :
	allModels()
{
}

ModelManager::~ModelManager()
{
	map<string, ModelSP>::iterator walker = allModels.begin();
	while (walker != allModels.end())
	{
		walker->second.reset();
		walker++;
	}
	allModels.clear();
}

ModelManager* ModelManager::getInstance()
{
	if (!instance)
	{
		instance = new ModelManager();
	}

	return instance;
}

void ModelManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

bool ModelManager::containsModelByKey(const string& key) const
{
	return allModels.find(key) != allModels.end();
}

const ModelSP& ModelManager::getModelByKey(const string& key) const
{
	return allModels.at(key);
}

void ModelManager::setModel(const string& key, const ModelSP& model)
{
	ModelSP currentModel = allModels[key];

	allModels[key] = model;
}
