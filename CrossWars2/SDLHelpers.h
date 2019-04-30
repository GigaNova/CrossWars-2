#pragma once
#include <SDL/SDL.h>
#include <cstdio>

class SDLHelpers
{
public:
	static void checkSDLError(int t_line = -1)
	{
#ifndef NDEBUG
		const char *error = SDL_GetError();
		if (*error != '\0')
		{
			printf("SDL Error: %s\n", error);
			if (t_line != -1)
				printf(" + line: %i\n", t_line);
			SDL_ClearError();
		}
#endif
	}

	static void printSDLError(const char* t_message)
	{
		printf("%s: %s\n", t_message, SDL_GetError());
		SDL_Quit();
		exit(1);
	}
};

