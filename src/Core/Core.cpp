#include "pch.h"
#include "Core.h"
#include "..\Globals.h"



//Private:
void Core::set_delta_values() {
	cn::DELTA_X = 1 - (((native_width - static_cast<float>(window_width)) / (native_width / 100.0f)) / 100.0f);
	cn::DELTA_Y = 1 - (((native_height - static_cast<float>(window_height)) / (native_height / 100.0f)) / 100.0f);
}

void Core::resized_window(const std::unordered_map<int, cn::YearDrawables>& preloaded_years) {
	sf::Vector2u new_size = window.getSize();
	
	sf::FloatRect visibleArea(0, 0, static_cast<float>(new_size.x), static_cast<float>(new_size.y));
	window.setView(sf::View(visibleArea));
	
	window_width = new_size.x;
	window_height = new_size.y;

	float old_delta_x = 1 / cn::DELTA_X;
	float old_delta_y = 1 / cn::DELTA_Y;

	set_delta_values();

	for (auto each : preloaded_years) {
		//Do this shit when you finish the set up.
	}
}

//================================================================================================================================

//Public:
void Core::setup_window(const sf::VideoMode mode, const uint32_t style) {
	window.create(mode, "CaleNdar", style);

	//sf::Image icon;
	//window.setIcon(64, 64, icon.getPixelsPtr());

	window_width = mode.width;
	window_height = mode.height;

	set_delta_values();
}

void Core::main_loop(const std::unordered_map<int, cn::YearDrawables>& preloaded_years, const std::vector<cn::Drawable*> in_frame, const bool& loop_selector) {
	
	while (window.isOpen() && loop_selector) {
		for (auto each : in_frame) {
			if (each) each->draw(window, event, mouse);
		}
		window.display();


		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
			cn::APPLICATION_STATE = EXIT;
		}


		if (event.type == sf::Event::Resized) {
			resized_window(preloaded_years);
		}
	}
}

void Core::pop_up_loop(const std::unordered_map<int, cn::YearDrawables>& preloaded_years, const std::vector<cn::Drawable*> in_frame_background, const std::vector<cn::Drawable*> in_frame_foreground, const sf::FloatRect constraints, const bool& loop_selector) {
	
	while (window.isOpen() && loop_selector) {
		for (auto each : in_frame_background) {
			if (each) each->draw(window);
		}

		for (auto each : in_frame_foreground) {
			if (each) each->draw(window, event, mouse);
		}
		window.display();


		window.pollEvent(event);

		if (event.type == sf::Event::Closed) {
			window.close();
			cn::APPLICATION_STATE = EXIT;
		}

		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		if (!constraints.contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				break;
			}
		}

		if (event.type == sf::Event::Resized) {
			resized_window(preloaded_years);
		}
	}
}

void Core::scroll_loop() {
	//add this
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================