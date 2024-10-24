#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>

/* Create an image sprite */
Sprite* createImageSprite(const char* imagePath, SDL_Renderer* renderer, int x, int y, int width, int height) {
    Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
    if (sprite == NULL) {
        printf("Error: Could not allocate memory for sprite.\n");
        return NULL;
    }

    SDL_Surface* loadedSurface = SDL_LoadBMP(imagePath);
    if (loadedSurface == NULL) {
        printf("Error loading image %s! SDL Error: %s\n", imagePath, SDL_GetError());
        free(sprite);
        return NULL;
    }

    sprite->texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (sprite->texture == NULL) {
        printf("Error creating texture from %s! SDL Error: %s\n", imagePath, SDL_GetError());
        free(sprite);
        return NULL;
    }

    // Set the source rectangle (full texture by default)
    sprite->srcRect.x = 0;
    sprite->srcRect.y = 0;
    SDL_QueryTexture(sprite->texture, NULL, NULL, &sprite->srcRect.w, &sprite->srcRect.h);

    // Set the destination rectangle (position and size)
    sprite->destRect.x = x;
    sprite->destRect.y = y;
    sprite->destRect.w = width;
    sprite->destRect.h = height;

    return sprite;
}

Sprite* createShapeSprite(SDL_Renderer* renderer, int x, int y, int width, int height, void (*drawShape)(SDL_Renderer*, int, int, int, int)) {
    Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
    if (sprite == NULL) {
        printf("Error: Could not allocate memory for sprite.\n");
        return NULL;
    }

    // Create a new texture to draw the shape on
    sprite->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (sprite->texture == NULL) {
        printf("Error creating texture for shape! SDL Error: %s\n", SDL_GetError());
        free(sprite);
        return NULL;
    }

    printf("Texture created successfully for shape sprite.\n");

    // Set blend mode to handle transparency
    SDL_SetTextureBlendMode(sprite->texture, SDL_BLENDMODE_BLEND);

    // Set the destination rectangle (position and size)
    sprite->destRect.x = x;
    sprite->destRect.y = y;
    sprite->destRect.w = width;
    sprite->destRect.h = height;

    // Set the render target to the texture (we'll draw on it)
    if (SDL_SetRenderTarget(renderer, sprite->texture) != 0) {
        printf("Error setting render target to texture: %s\n", SDL_GetError());
    } else {
        printf("Render target successfully set to texture.\n");
    }

    // Clear the texture with transparency (RGBA: 0, 0, 0, 0)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Call the custom shape drawing function (this draws onto the texture)
    drawShape(renderer, 0, 0, width, height);

    // Reset the render target back to the default (the screen)
    SDL_SetRenderTarget(renderer, NULL);

    return sprite;
}

/* Render a sprite */
void renderSprite(Sprite* sprite, SDL_Renderer* renderer) {
    if (sprite != NULL && sprite->texture != NULL) {
        // Print debug information for sprite rendering
        printf("Rendering sprite at position (%d, %d) with size (%d, %d)\n",
               sprite->destRect.x, sprite->destRect.y,
               sprite->destRect.w, sprite->destRect.h);

        // Ensure source rect is correctly set
        sprite->srcRect.x = 0;
        sprite->srcRect.y = 0;
        sprite->srcRect.w = sprite->destRect.w;
        sprite->srcRect.h = sprite->destRect.h;

        // Render the texture to the screen
        if (SDL_RenderCopy(renderer, sprite->texture, &sprite->srcRect, &sprite->destRect) != 0) {
            printf("Error rendering texture: %s\n", SDL_GetError());
        } else {
            printf("Sprite rendered successfully.\n");
        }
    }
}

/* Destroy a sprite and free memory */
void destroySprite(Sprite* sprite) {
    if (sprite == NULL) return;
    if (sprite->texture != NULL) {
        SDL_DestroyTexture(sprite->texture);
        sprite->texture = NULL;
    }
    free(sprite);
}