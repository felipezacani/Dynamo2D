#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

/* Screen parameters */
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

/* Function prototypes */
int init();
void close();
void loadConfig();

/* Main rendering window */
SDL_Window* gWindow = NULL;

/* Main renderer */
SDL_Renderer* gRenderer = NULL;

/* Load config file */
void loadConfig() {
    FILE* configFile = fopen("config/config.txt", "r");
    if (configFile == NULL) {
        printf("Error: Could not open config file, using default values.\n");
        return;
    }

    fscanf(configFile, "screen_width=%d\n", &SCREEN_WIDTH);
    fscanf(configFile, "screen_height=%d\n", &SCREEN_HEIGHT);
    fclose(configFile);
}

/* Initialize SDL and create a window */
int init() {
    loadConfig();  // Load configuration before SDL initialization

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error initializing SDL subsystems: %s\n", SDL_GetError());
        return 0;
    }

    gWindow = SDL_CreateWindow("Dynamo2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Error creating main window: %s\n", SDL_GetError());
        return 0;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        return 0;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return 1;
}

/* Free resources */
void close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Initialization error, aborting...\n");
        return -1;
    }

    int quit = 0; // Main loop control flag
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);

        // TODO: Implement and call our main render function

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}