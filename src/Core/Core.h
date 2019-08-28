#pragma once
#include "pch.h"
#include "..\Structures\Structures.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

class Core {
private:
	float native_width{1920};
	float native_height{1080};

	unsigned int window_width{ 0 };
	unsigned int window_height{ 0 };

	std::vector<cn::Drawable*> drawables;

	//Call this in setup_window and in each resized_window call.
	void set_delta_values();

	//Call this on resize event.
	void resized_window(sf::Vector2u& new_size);

public:
	sf::RenderWindow window;
	sf::Event event{sf::Event::MouseMoved};
	sf::Mouse mouse;

	//Call this once when we start up the program.
	void setup_window(sf::VideoMode& mode, const uint32_t& style);


	//Call this when you want to add a drawable.
	void add_drawable(cn::Drawable& image);
	

	//This is our application.
	void main_loop(std::vector<cn::Drawable*>& in_frame, bool& loop_selector);
	//This is our pop-up loop.
	void pop_up_loop(std::vector<cn::Drawable*>& in_frame_background, std::vector<cn::Drawable*>& in_frame_foreground, sf::FloatRect& constraints, bool& loop_selector);
};



//================================================================================================================================
//================================================================================================================================
//================================================================================================================================