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


	//Call this in setup_window and in each resized_window call.
	void set_delta_values();

	//Call this on resize event.
	void resized_window(const std::vector<cn::Drawable*> in_frame);

public:
	sf::RenderWindow window;
	sf::Event event{sf::Event::MouseMoved};
	sf::Mouse mouse;

	//Call this once when we start up the program.
	void setup_window(const sf::VideoMode mode, const uint32_t style);



	void main_loop(const std::vector<cn::Drawable*> in_frame, const bool& loop_selector);

	void pop_up_loop(const std::vector<cn::Drawable*> in_frame_background, const std::vector<cn::Drawable*> in_frame_foreground, const sf::FloatRect constraints, const bool& loop_selector);

	void scroll_loop();
};



//================================================================================================================================
//================================================================================================================================
//================================================================================================================================