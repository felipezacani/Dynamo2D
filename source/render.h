#ifndef RENDER_H
#define RENDER_H

#include "sprite.h"
#include <SDL2/SDL.h>

/* Entity structure */
typedef struct {
    Sprite* sprite;   // The sprite to render
    float posX;       // X position
    float posY;       // Y position
    float velX;       // Velocity along the X-axis
    float velY;       // Velocity along the Y-axis
} Entity;

/* Function prototypes */
void renderEntities(Entity* entities, int entityCount, SDL_Renderer* renderer);
void updateEntities(Entity* entities, int entityCount, int screenWidth, int screenHeight);

#endif