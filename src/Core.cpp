#include "pch.h"
#include "Core.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	//================================================================================================================================

	void Image::resize(const double& DELTA_X, const double& DELTA_Y) {
		sprite.scale(static_cast<float>(DELTA_X), static_cast<float>(DELTA_Y));
		position = sprite.getGlobalBounds();
	}

	void Image::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		window.draw(sprite);
	}

	void Image::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void Image::set_image(const char* data, std::size_t size, const float& x, const float& y) {
		texture.loadFromMemory(data, size);
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
	}

	//================================================================================================================================

	void Label::resize(const double& DELTA_X, const double& DELTA_Y) {
		sprite.scale(static_cast<float>(DELTA_X), static_cast<float>(DELTA_Y));
		position = sprite.getGlobalBounds();

		text.scale(static_cast<float>(DELTA_X), static_cast<float>(DELTA_Y));
		text_position = text.getGlobalBounds();
	}

	void Label::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		window.draw(sprite);
		window.draw(text);
	}

	void Label::draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	}

	void Label::set_image(const char* data, std::size_t size, const float& x, const float& y) {
		texture.loadFromMemory(data, size);
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
	}

	void Label::set_font(const std::string& path, const unsigned int& text_size, const sf::Color color, const float& x, const float& y, const std::string& _text) {
		font.loadFromFile(path);
		text.setFont(font);
		text.setCharacterSize(text_size);
		text.setFillColor(color);
		text.setPosition(x, y);

		text.setString(_text);
	}

	//================================================================================================================================

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

void Core::add_drawable(cn::Drawable& image, const char* data, std::size_t size, const float& x, const float& y) {
	image.set_image(data, size, x, y);

	image.resize(DELTA_X, DELTA_Y);

	drawables.push_back(&image);
}

void Core::add_drawable(cn::Drawable& image, const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) {
	image.set_image(data, size, x, y);

	image.set_hl(data_hl, size_hl, x, y);

	image.resize(DELTA_X, DELTA_Y);

	drawables.push_back(&image);
}

void Core::add_drawable(cn::Drawable& image, const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) {
	image.set_image(data, size, x, y);

	image.set_font(path, text_size, color, text_x, text_y, _text);

	image.resize(DELTA_X, DELTA_Y);

	drawables.push_back(&image);
}

void Core::add_drawable(cn::Drawable& image, const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) {
	image.set_image(data, size, x, y);

	image.set_hl(data_hl, size_hl, x, y);

	image.set_font(path, text_size, color, text_x, text_y, _text);

	image.resize(DELTA_X, DELTA_Y);

	drawables.push_back(&image);
}

void Core::main_loop(std::vector<cn::Drawable*>& in_frame) {
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

void Core::pop_up_loop(std::vector<cn::Drawable*>& in_frame_background, std::vector<cn::Drawable*>& in_frame_foreground, sf::FloatRect& constraints) {
	while (window.isOpen()) {
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
		}

		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		if (constraints.contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
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