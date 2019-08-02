#include "pch.h"
#include "Core.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	void Image::resize(const double& DELTA_X, const double& DELTA_Y) {
		
		sprite.scale(static_cast<float>(DELTA_X), static_cast<float>(DELTA_Y));
		position = sprite.getGlobalBounds();
	}

	void Image::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		window.draw(sprite);
	}

	void Image::set_hl(const char* data_hl, std::size_t size_hl, const float& x, const float& y, const double& DELTA_X, const double& DELTA_Y) {}

}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

//Private:
void Core::set_delta_values() {
	DELTA_X = 1 - (((native_width - static_cast<double>(window_width)) / (native_width / 100.0)) / 100.0);
	DELTA_Y = 1 - (((native_height - static_cast<double>(window_height)) / (native_height / 100.0)) / 100.0);
}

void Core::resized_window(sf::Vector2u& new_size) {
	window_width = new_size.x;
	window_height = new_size.y;

	double old_delta_x = 1/DELTA_X;
	double old_delta_y = 1/DELTA_Y;

	set_delta_values();

	for (auto& each : drawables) {
		each->resize(DELTA_X*old_delta_x, DELTA_Y*old_delta_y);
	}
}

//================================================================================================================================
//================================================================================================================================
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

void Core::add_drawable(cn::Image& image, const char* data, std::size_t size, const float& x, const float& y) {
	image.texture.loadFromMemory(data, size);
	image.sprite.setTexture(image.texture);
	image.sprite.setPosition(x, y);

	image.resize(DELTA_X, DELTA_Y);

	drawables.push_back(&image);
}

void Core::add_drawable(cn::Image& image, const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) {
	image.texture.loadFromMemory(data, size);
	image.sprite.setTexture(image.texture);
	image.sprite.setPosition(x, y);
	image.set_hl(data_hl, size_hl, x, y, DELTA_X, DELTA_Y);

	image.resize(DELTA_X, DELTA_Y);

	drawables.push_back(&image);
}

void Core::main_loop(std::vector<cn::Image*>& in_frame) {
	while (window.isOpen()) {
		for (auto& each : in_frame) {
			each->draw(window, event, mouse);
		}
		window.display();


		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
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