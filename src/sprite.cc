#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "sprite.h"
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, std::string filename, int x, int y)
	: Hitbox(x, y, 0, 0), filename{filename}, enabled{true}, texture{nullptr}
	{
		SDL_Surface* temp_surf = IMG_Load(filename.c_str());
		if ( temp_surf == nullptr )
		{
			std::cout << "IMG:" << IMG_GetError() << std::endl;
			//std::cout << "SDL:" << SDL_GetError() << std::endl;
			return;
		}
		texture = SDL_CreateTextureFromSurface(renderer, temp_surf);
		set_w(temp_surf->w); //Makes texture actual file size as default.
		set_h(temp_surf->h);
		SDL_FreeSurface(temp_surf);
	}

Sprite::~Sprite()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	else
	{
		std::cout << "Texture already destroyed." << std::endl;
	}
}

void Sprite::update()
{
	//Virtual
}

void Sprite::draw(SDL_Renderer* renderer)
{
	if (enabled)
	{
		SDL_Rect r = get_rect();
		SDL_RenderCopy(renderer, texture, nullptr, &r);
	}
}

bool Sprite::is_enabled() const
{ return enabled; }

void Sprite::set_enabled(bool state)
{ enabled = state; }
