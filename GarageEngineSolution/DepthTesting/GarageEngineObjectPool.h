#pragma once

#ifndef  GARAGE_ENGINE_POOL
#define GARAGE_ENGINE_POOL

#include "GarageEngineObject.h"
#include "GarageShaders.h"
#include "Model.h"
#include "vector"


/// <summary>
/// Stores all the garage engine objects and related components, including:
/// 
/// - EngineObjects
/// - RenderableObjects
/// - Models
/// - Shaders
/// </summary>

using namespace GarageEngine;

class GarageEngineObjectPool
{

private:
	
	vector<RenderableObject> renderableObjects;
	vector<Model> models;
	vector<Shader> shaders;

public:

	GarageEngineObjectPool();


};

#endif // ! GARAGE_ENGINE_POOL


