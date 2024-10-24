#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

/* Sprite structure */
typedef struct Sprite {
    SDL_Texture* texture;                           // Texture to render
    SDL_Rect srcRect;                               // Source rectangle (part of the texture to render)
    SDL_Rect destRect;                              // Destination rectangle (position and size on screen)
} Sprite;

/* Function prototypes */
Sprite* createImageSprite(const char* imagePath, SDL_Renderer* renderer, int x, int y, int width, int height);
Sprite* createShapeSprite(SDL_Renderer* renderer, int x, int y, int width, int height, void (*drawShape)(SDL_Renderer*, int, int, int, int));
void renderSprite(Sprite* sprite, SDL_Renderer* renderer);
void destroySprite(Sprite* sprite);

#endif