#include <stdio.h>
#include <stdlib.h>
#include <GLEW/glew.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include "Engine.h"
#include "DeltaTime.h"

int main(int argc, char *argv[])
{
	auto engineInstance = Engine::GetInstance();

	while(engineInstance->isRunning())
	{
		engineInstance->getInput();
		engineInstance->update();
		engineInstance->render();
		DeltaTime::GetInstance()->update();
	}

	engineInstance->cleanUp();

	return 0;
}
