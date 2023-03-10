#include "Dog.h"
#include "Defs.h"

Dog::Dog() : 
	position({100, 100, 50, 50}), velocity(0), gravity(1500), flightForce(100), textureIndex(0), lastTextureUpdateTime(0)
{
    renderer = Game::GetGameInstance()->GetRenderer();
    textures.push_back(IMG_LoadTexture(renderer, "./Resources/Textures/Dog.png"));
    textures.push_back(IMG_LoadTexture(renderer, "./Resources/Textures/Dog1.png"));

}

Dog::~Dog()
{
    for (SDL_Texture* texture : textures) {
        SDL_DestroyTexture(texture);
    }
}

void Dog::Update(double deltaTime)
{
    velocity += gravity * deltaTime;
    position.y += static_cast<int>(velocity * deltaTime);

    // Keeps dog on screen
    int textureHeight, textureWidth;
    SDL_QueryTexture(textures[textureIndex], nullptr, nullptr, &textureWidth, &textureHeight);

    if (position.y < textureHeight / 2) {
        position.y = textureHeight / 2;
        velocity = 0;
    }
    else if (position.y + textureHeight > SCREEN_HEIGHT) {
        position.y = SCREEN_HEIGHT - textureHeight;
        velocity = 0;
    }

    lastTextureUpdateTime += deltaTime;
    if (lastTextureUpdateTime > 0.25)
    {
        textureIndex = (textureIndex == 0) ? 1 : 0;
        lastTextureUpdateTime = 0;
    }
}

void Dog::Render()
{
	SDL_RenderCopy(renderer, textures[textureIndex], nullptr, &position);
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
