#include "pch.h"
#include "Core.h"
#include "..\Globals.h"



//Private:
void Core::set_delta_values() {
	cn::DELTA_X = 1 - (((native_width - static_cast<float>(window_width)) / (native_width / 100.0f)) / 100.0f);
	cn::DELTA_Y = 1 - (((native_height - static_cast<float>(window_height)) / (native_height / 100.0f)) / 100.0f);
}

void Core::resized_window(sf::Vector2u& new_size) {
	window_width = new_size.x;
	window_height = new_size.y;

	float old_delta_x = 1 / cn::DELTA_X;
	float old_delta_y = 1 / cn::DELTA_Y;

	set_delta_values();

	for (auto& each : drawables) {
		each->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
	}
}

//================================================================================================================================

//Public:
void Core::setup_window(sf::VideoMode& mode, const uint32_t& style) {
	window.create(mode, "CaleNdar", style);

	//sf::Image icon;
	//window.setIcon(64, 64, icon.getPixelsPtr());

	window_width = mode.width;
	window_height = mode.height;

	set_delta_values();
}

void Core::add_drawable(cn::Drawable& image) {
	drawables.push_back(&image);
}

void Core::main_loop(std::vector<cn::Drawable*>& in_frame, bool& loop_selector) {
	while (window.isOpen() && loop_selector) {
		for (auto& each : in_frame) {
			if (each) each->draw(window, event, mouse);
		}
		window.display();


		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
			cn::APPLICATION_STATE = EXIT;
		}

		sf::Vector2u new_size = window.getSize();
		if ((window_width != new_size.x) || (window_height != new_size.y)) {
			resized_window(new_size);
			sf::FloatRect visibleArea(0, 0, static_cast<float>(new_size.x), static_cast<float>(new_size.y));
			window.setView(sf::View(visibleArea));
		}

	}
}

void Core::pop_up_loop(std::vector<cn::Drawable*>& in_frame_background, std::vector<cn::Drawable*>& in_frame_foreground, sf::FloatRect& constraints, bool& loop_selector) {
	while (window.isOpen() && loop_selector) {
		for (auto& each : in_frame_background) {
			each->draw(window);
		}

		for (auto& each : in_frame_foreground) {
			each->draw(window, event, mouse);
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

		sf::Vector2u new_size = window.getSize();
		if ((window_width != new_size.x) || (window_height != new_size.y)) {
			resized_window(new_size);
			sf::FloatRect visibleArea(0, 0, static_cast<float>(new_size.x), static_cast<float>(new_size.y));
			window.setView(sf::View(visibleArea));
		}

	}
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================