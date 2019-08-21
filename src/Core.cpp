#include "pch.h"
#include "Core.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	//================================================================================================================================

	void Image::setup(const char* data, std::size_t size, const float& x, const float& y) {
		image_x_position = x;
		image_y_position = y;

		texture.loadFromMemory(data, size);
		sprite.setTexture(texture);
		sprite.setPosition(x * DELTA_X, y * DELTA_Y);
		sprite.scale(DELTA_X, DELTA_Y);
		position = sprite.getGlobalBounds();
	}

	void Image::resize(const float& resize_delta_x, const float& resize_delta_y) {
		sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);
		
		sprite.scale(resize_delta_x, resize_delta_y);
		position = sprite.getGlobalBounds();
	}

	void Image::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void Image::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		window.draw(sprite);
	}

	//================================================================================================================================

	Button::Button(std::function<void()> _function) : function(_function) {}

	void Button::setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) {
		image_x_position = x;
		image_y_position = y;
		
		texture.loadFromMemory(data, size);
		sprite.setTexture(texture);
		sprite.setPosition(x * DELTA_X, y * DELTA_Y);

		hl_texture.loadFromMemory(data_hl, size_hl);
		hl_sprite.setTexture(hl_texture);
		hl_sprite.setPosition(x * DELTA_X, y * DELTA_Y);

		sprite.scale(DELTA_X, DELTA_Y);
		hl_sprite.scale(DELTA_X, DELTA_Y);
		position = sprite.getGlobalBounds();
	}

	void Button::resize(const float& resize_delta_x, const float& resize_delta_y) {
		sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);
		hl_sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);
		
		sprite.scale(resize_delta_x, resize_delta_y);
		hl_sprite.scale(resize_delta_x, resize_delta_y);

		position = sprite.getGlobalBounds();
	}

	void Button::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void Button::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		window.draw(sprite);

		if (position.contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				while (position.contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
					window.waitEvent(event);
					if (event.type == sf::Event::MouseButtonReleased) {
						function();
					}
					mouse_position = sf::Mouse::getPosition(window);
				}
			}
			window.draw(hl_sprite);
		}

		//add right click here with a new function and a new constructor
	}

	//================================================================================================================================

	void Label::setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) {
		image_x_position = x;
		image_y_position = y;
		
		text_x_position = text_x;
		text_y_position = text_y;
		
		texture.loadFromMemory(data, size);
		sprite.setTexture(texture);
		sprite.setPosition(x * DELTA_X, y * DELTA_Y);

		font.loadFromFile(path); //change this when you serialize the font file.
		text.setFont(font);
		text.setCharacterSize(text_size);
		text.setFillColor(color);
		text.setPosition(x * DELTA_X, y * DELTA_Y);

		text.setString(_text);

		sprite.scale(DELTA_X, DELTA_Y);
		position = sprite.getGlobalBounds();

		text.scale(DELTA_X, DELTA_Y);
		text_position = text.getGlobalBounds();
	}

	void Label::resize(const float& resize_delta_x, const float& resize_delta_y) {
		sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);
		
		sprite.scale(resize_delta_x, resize_delta_y);
		position = sprite.getGlobalBounds();

		text.setPosition(text_x_position * DELTA_X, text_y_position * DELTA_Y);

		text.scale(resize_delta_x, resize_delta_y);
		text_position = text.getGlobalBounds();
	}

	void Label::draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	}

	void Label::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		window.draw(sprite);
		window.draw(text);
	}

	//================================================================================================================================

	TextButton::TextButton(std::function<void()> _function) : function(_function) {}

	void TextButton::setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) {
		image_x_position = x;
		image_y_position = y;

		text_x_position = text_x;
		text_y_position = text_y;
		
		texture.loadFromMemory(data, size);
		sprite.setTexture(texture);
		sprite.setPosition(x * DELTA_X, y * DELTA_Y);

		hl_texture.loadFromMemory(data_hl, size_hl);
		hl_sprite.setTexture(hl_texture);
		hl_sprite.setPosition(x * DELTA_X, y * DELTA_Y);

		font.loadFromFile(path);
		text.setFont(font);
		text.setCharacterSize(text_size);
		text.setFillColor(color);
		text.setPosition(x * DELTA_X, y * DELTA_Y);

		text.setString(_text);

		sprite.scale(DELTA_X, DELTA_Y);
		hl_sprite.scale(DELTA_X, DELTA_Y);

		position = sprite.getGlobalBounds();

		text.scale(DELTA_X, DELTA_Y);
		text_position = text.getGlobalBounds();
	}

	void TextButton::resize(const float& resize_delta_x, const float& resize_delta_y) {
		sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);
		hl_sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);
		
		sprite.scale(resize_delta_x, resize_delta_y);
		hl_sprite.scale(resize_delta_x, resize_delta_y);

		position = sprite.getGlobalBounds();

		text.setPosition(text_x_position * DELTA_X, text_y_position * DELTA_Y);

		text.scale(resize_delta_x, resize_delta_y);
		text_position = text.getGlobalBounds();
	}

	void TextButton::draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	}

	void TextButton::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		window.draw(sprite);
		window.draw(text);

		if (position.contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				while (position.contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
					window.waitEvent(event);
					if (event.type == sf::Event::MouseButtonReleased) {
						function();
					}
					mouse_position = sf::Mouse::getPosition(window);
				}
			}
			window.draw(hl_sprite);
		}
	}

	//================================================================================================================================

}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

//Private:
void Core::set_delta_values() {
	cn::DELTA_X = 1 - (((native_width - static_cast<float>(window_width)) / (native_width / 100.0f)) / 100.0f);
	cn::DELTA_Y = 1 - (((native_height - static_cast<float>(window_height)) / (native_height / 100.0f)) / 100.0f);
}

void Core::resized_window(sf::Vector2u& new_size) {
	window_width = new_size.x;
	window_height = new_size.y;

	float old_delta_x = 1/cn::DELTA_X;
	float old_delta_y = 1/cn::DELTA_Y;

	set_delta_values();

	for (auto& each : drawables) {
		each->resize(cn::DELTA_X*old_delta_x, cn::DELTA_Y*old_delta_y);
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
			each->draw(window, event, mouse);
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