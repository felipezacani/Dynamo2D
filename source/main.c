#include <SDL2/SDL.h>
#include <stdio.h>
#include "sprite.h"
#include "render.h"

/* Screen parameters TODO: Move to a config file */
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

/* Function prototypes */
int init();
void close();

/* Main rendering window */
SDL_Window* gWindow = NULL;

/* Main renderer */
SDL_Renderer* gRenderer = NULL;

/* Custom function to draw a filled circle */
void drawCircle(SDL_Renderer* renderer, int x, int y, int width, int height) {
    int radius = width / 2;
    int centerX = x + radius;
    int centerY = y + radius;

    // Set the render color to red (you can change this to any color)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red with full opacity

    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;  // Horizontal distance
            int dy = radius - h;  // Vertical distance
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }

    printf("Circle drawn at (%d, %d) with radius %d\n", centerX, centerY, radius);
}

/* Simple debug rectangle function */
void drawRectangle(SDL_Renderer* renderer, int x, int y, int width, int height) {
    // Set the render color to red for visibility
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color with full opacity

    // Draw a filled rectangle
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);

    printf("Rectangle drawn at (%d, %d) with dimensions %dx%d\n", x, y, width, height);
}

/* Initialize SDL and create a window */
int init() {
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

    // Create a bouncing circle sprite, drawn onto a texture
    Sprite* circleSprite = createShapeSprite(gRenderer, 100, 100, 50, 50, drawCircle);

    // Create an entity for the circle with initial float position and velocity
    Entity circleEntity = {circleSprite, 100.0f, 100.0f, 2.5f, 2.5f};

    // Entity array
    Entity entities[1] = {circleEntity};

    int quit = 0;  // Main loop control flag
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Update entity positions
        updateEntities(entities, 1, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Clear the screen
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render all entities
        renderEntities(entities, 1, gRenderer);

        // Present the updated screen
        SDL_RenderPresent(gRenderer);
    }

    // Clean up
    destroySprite(circleSprite);
    close();

    return 0;
}