#include "victory.h"

Victory::Victory(SDL_Renderer* renderer, std::string filename)
    : Sprite(renderer, filename),
        retry_button{new Sprite(renderer, "./img/retry_button.png")},
        next_button{new Sprite(renderer, "./img/next_button.png")},
        time{new Text("00:00", renderer)},
        best_time_title{new Text("Best Time:", renderer)}, enabled{false}
{
    set_w(400);
    set_h(300);
    set_x(400);
    set_y(200);

    retry_button->set_x(get_x() + 30);
    retry_button->set_y(get_y() + 160);

    next_button->set_x(get_x() + 210);
    next_button->set_y(get_y() + 160);
}

Victory::~Victory()
{
    delete retry_button;
    delete next_button;
    delete time;
    delete best_time_title;
}

void Victory::draw(SDL_Renderer* renderer)
{
    if (enabled)
    {
        Sprite::draw(renderer);
        next_button->draw(renderer);
        retry_button->draw(renderer);
        best_time_title->draw(get_x() + 70, get_y() + 30, renderer);
        time->draw(get_x() + 130, get_y() + 90, renderer);
    }
}

void Victory::set_enabled(bool const& state)
{ enabled = state; }

bool Victory::is_enabled()
{ return enabled; }

Sprite* Victory::get_next_button()
{ return next_button; }

Sprite* Victory::get_retry_button()
{ return retry_button; }

Text* Victory::get_text_object()
{
    return time;
}
