#include "Dog.h"
#include "Defs.h"

Dog::Dog() : 
	texture(nullptr), position({100, 100, 50, 50}), velocity(0), gravity(1500), flightForce(100)
{
    renderer = Game::GetGameInstance()->GetRenderer();
    texture = IMG_LoadTexture(renderer, "./Resources/Textures/Dog.png");
}

Dog::~Dog()
{
	SDL_DestroyTexture(texture);
}

void Dog::Update(double deltaTime)
{
    velocity += gravity * deltaTime;
    position.y += static_cast<int>(velocity * deltaTime);

    // Keeps dog on screen
    int textureHeight, textureWidth;
    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

    if (position.y < textureHeight / 2) {
        position.y = textureHeight / 2;
        velocity = 0;
    }
    else if (position.y + textureHeight > SCREEN_HEIGHT) {
        position.y = SCREEN_HEIGHT - textureHeight;
        velocity = 0;
    }
}

void Dog::Render()
{
	SDL_RenderCopy(renderer, texture, nullptr, &position);
}

void Dog::Restart()
{
    position.y = 100;
    velocity = 0;
    Render();
}

void Dog::Flight()
{
	velocity = -sqrt(2.0f * gravity * flightForce);
}

SDL_Rect* Dog::GetPosition()
{
    return &position;
}
