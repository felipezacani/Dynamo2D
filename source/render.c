#include "render.h"
#include <stdio.h>

/* Render all entities in the array */
void renderEntities(Entity* entities, int entityCount, SDL_Renderer* renderer) {
    for (int i = 0; i < entityCount; i++) {
        // Update the sprite's position based on the entity's float position
        entities[i].sprite->destRect.x = (int)entities[i].posX;
        entities[i].sprite->destRect.y = (int)entities[i].posY;

        // Render the sprite
        renderSprite(entities[i].sprite, renderer);
    }
}

/* Update the position of all entities (bouncing inside the screen) */
void updateEntities(Entity* entities, int entityCount, int screenWidth, int screenHeight) {
    for (int i = 0; i < entityCount; i++) {
        // Update position using velocity
        entities[i].posX += entities[i].velX;
        entities[i].posY += entities[i].velY;

        // Bounce off the screen edges (reverse velocity)
        if (entities[i].posX <= 0 || entities[i].posX + entities[i].sprite->destRect.w >= screenWidth) {
            entities[i].velX = -entities[i].velX;
        }
        if (entities[i].posY <= 0 || entities[i].posY + entities[i].sprite->destRect.h >= screenHeight) {
            entities[i].velY = -entities[i].velY;
        }
    }
}