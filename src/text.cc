#include "text.h"
#include <iostream>

TTF_Font* Text::font = nullptr;

Text::Text(std::string text, SDL_Renderer* renderer)
	:width{}, height{}, texture{}, text{}
{
	texture = nullptr;
	init(text, renderer);
}

Text::~Text()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Text::init(std::string i_text, SDL_Renderer* renderer)
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	text = i_text;
	if (text.empty()) {text = " ";}

	if (font == nullptr)
	{
		font = TTF_OpenFont("./fonts/monoid.ttf", 40);
		if (font == nullptr)
		{
			throw FontLoadingException(std::string("Unable to load font: ") + TTF_GetError());
		}
	}

	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
}

void Text::set_text(const std::string& i_text, SDL_Renderer* renderer)
{
	if (text != i_text)
	{
		init(i_text, renderer);
	}
}

void Text::draw(const int x, const int y, SDL_Renderer* renderer)
{
	SDL_Rect dest_rect = { x, y, width, height };
	SDL_RenderCopy(renderer, texture, nullptr, &dest_rect);
}

int Text::get_height() const
{ return height; }

int Text::get_width() const
{ return width; }
