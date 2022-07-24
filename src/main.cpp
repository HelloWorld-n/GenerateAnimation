#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>
#include <random>
#include <ctime>
#include <thread>
#include <chrono>
#include "AppUtil.cpp"

const int screenWidth = 800;
const int screenHeight = 600;
const int segmentSize = 4;
const int distanceFromEdge = 6;
const int segmentWidth = 5;

void handleEvents(SDL_Window *window, bool mainWindow = false){
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0){
		if (event.type == SDL_QUIT){
			SDL_DestroyWindow(window);
			SDL_Quit();
			if (mainWindow){
				std::exit(0);
			}
		}
	}
}

int enlimit(int num, int limit){
	if (num % (limit * 2) < limit){
		return num % limit;
	} else {
		return limit - (num % limit);
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args;
    for(int i = 1; i < argc; i++){
        args.push_back(argv[i]);   
    };
	AppSettings::apply(args);

	if (AppSettings::help){
		std::fstream file;
		file.open("./README.md");
		std::cout << file.rdbuf() << "\n";
		file.close();
		return 0;
	}

	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error: \e48;2;0;0;0m\e[38;2;255;0;0m" << SDL_GetError() << "\e[0m;\n";
		return -418;
	}
	
	window = SDL_CreateWindow(
		"GenerateShape",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		std::cerr << "Error: \e48;2;0;0;0m\e[38;2;255;0;0m" << SDL_GetError() << "\e[0m;\n";
		return -404;
	}
	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
	
	SDL_UpdateWindowSurface(window);

	srand(time(0));
	while (true){
		for (int i = 0; i < screenHeight / segmentSize; i++){
			for (int j = distanceFromEdge; j < (screenWidth / segmentSize) - distanceFromEdge; j++){
				if (j % (segmentWidth * 2) < segmentWidth){
					bool active = (rand() % 2) > 0;
					SDL_Rect segment {
						j * segmentSize, 
						i * segmentSize, 
						segmentSize,
						segmentSize,
					};
					
					SDL_FillRect(
						screenSurface, 
						&segment,
						SDL_MapRGB(
							SDL_CreateRGBSurface(
								0, 
								segmentSize, 
								segmentSize, 
								32, 0, 
								0, 0, 0
							)->format, 
							/* red */ (active)?(0):(255),
							/* green */ (active)?(0):(255),
							/* blue */ (active)?(0):(255)
						)
					);
				}
			}
		}
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
		SDL_UpdateWindowSurface(window);
		handleEvents(window, true);
	}
	return 0;
}
