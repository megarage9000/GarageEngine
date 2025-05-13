#pragma once

#ifndef GARAGE_ENGINE
#define GARAGE_ENGINE

#include "GarageEngineObject.h"
#include "GarageShaders.h"
#include "Model.h"
#include <vector>

class ObjectPooler {
	// Store renderable and game engine objects
	// - For now, use 
	vector<GarageEngine::EngineObject> engineObjects;
	vector<GarageEngine::RenderableObject> renderables;
	vector<Model> models;
	vector<Shader> shaders;

public:
	explicit ObjectPooler() : 
		engineObjects(vector<GarageEngine::EngineObject>()),
		renderables(vector<GarageEngine::RenderableObject>()), 
		models(vector<Model>()),
		shaders(vector<Shader>()) {}
	
};


#endif

