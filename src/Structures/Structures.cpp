#include "pch.h"
#include "Structures.h"
#include "..\Globals.h"


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
	}

	void Image::resize(const float& resize_delta_x, const float& resize_delta_y) {
		sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);

		sprite.scale(resize_delta_x, resize_delta_y);
	}

	void Image::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void Image::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		window.draw(sprite);
	}

	//================================================================================================================================

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
	}

	void Button::resize(const float& resize_delta_x, const float& resize_delta_y) {
		sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);
		hl_sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);

		sprite.scale(resize_delta_x, resize_delta_y);
		hl_sprite.scale(resize_delta_x, resize_delta_y);

	}

	void Button::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void Button::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		window.draw(sprite);

		if (sprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				while (sprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
					window.waitEvent(event);
					if (event.type == sf::Event::MouseButtonReleased) {
						function();
					}
					mouse_position = sf::Mouse::getPosition(window);
					break;
				}
			}
			window.draw(hl_sprite);
		}
	}

	void Button::set_function(std::function<void()> _function) {
		function = _function;
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

		text.scale(DELTA_X, DELTA_Y);
	}

	void Label::resize(const float& resize_delta_x, const float& resize_delta_y) {
		sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);

		sprite.scale(resize_delta_x, resize_delta_y);

		text.setPosition(text_x_position * DELTA_X, text_y_position * DELTA_Y);

		text.scale(resize_delta_x, resize_delta_y);
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
		text.setPosition(text_x * DELTA_X, text_y * DELTA_Y);

		text.setString(_text);

		sprite.scale(DELTA_X, DELTA_Y);
		hl_sprite.scale(DELTA_X, DELTA_Y);


		text.scale(DELTA_X, DELTA_Y);
	}

	void TextButton::resize(const float& resize_delta_x, const float& resize_delta_y) {
		sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);
		hl_sprite.setPosition(image_x_position * DELTA_X, image_y_position * DELTA_Y);

		sprite.scale(resize_delta_x, resize_delta_y);
		hl_sprite.scale(resize_delta_x, resize_delta_y);


		text.setPosition(text_x_position * DELTA_X, text_y_position * DELTA_Y);

		text.scale(resize_delta_x, resize_delta_y);
	}

	void TextButton::draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	}

	void TextButton::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		window.draw(sprite);
		window.draw(text);

		if (sprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				while (sprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
					window.waitEvent(event);
					if (event.type == sf::Event::MouseButtonReleased) {
						function();
					}
					mouse_position = sf::Mouse::getPosition(window);
					break;
				}
			}
			window.draw(hl_sprite);
		}
	}

	void TextButton::set_function(std::function<void()> _function) {
		function = _function;
	}

	//================================================================================================================================

}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================