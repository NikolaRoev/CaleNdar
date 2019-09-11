#include "pch.h"
#include "Structures.h"
#include "..\Globals.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	//================================================================================================================================

	void Image::setup(sf::Texture& texture, const float& x, const float& y) {
		image_x_position = x;
		image_y_position = y;

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

	void Button::setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y) {
		image_x_position = x;
		image_y_position = y;

		sprite.setTexture(texture);
		sprite.setPosition(x * DELTA_X, y * DELTA_Y);

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

	void Label::setup(sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) {
		text_x_position = text_x;
		text_y_position = text_y;

		text.setFont(font);
		text.setCharacterSize(text_size);
		text.setFillColor(color);
		text.setPosition(text_x * DELTA_X, text_y * DELTA_Y);

		text.setString(_text);

		text.scale(DELTA_X, DELTA_Y);
	}

	void Label::resize(const float& resize_delta_x, const float& resize_delta_y) {
		if (dynamic) {
			auto sizer = text.getGlobalBounds();
			text.setPosition((960 * cn::DELTA_X - sizer.width / 2), 0);
			text_x_position = 960 * cn::DELTA_X - sizer.width / 2;

			text.scale(resize_delta_x, resize_delta_y);
		}
		else {
			text.setPosition(text_x_position * DELTA_X, text_y_position * DELTA_Y);

			text.scale(resize_delta_x, resize_delta_y);
		}
	}

	void Label::draw(sf::RenderWindow& window) {
		window.draw(text);
	}

	void Label::draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) {
		window.draw(text);
	}

	//================================================================================================================================

	void TextButton::setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y, sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) {
		image_x_position = x;
		image_y_position = y;

		text_x_position = text_x;
		text_y_position = text_y;

		sprite.setTexture(texture);
		sprite.setPosition(x * DELTA_X, y * DELTA_Y);

		hl_sprite.setTexture(hl_texture);
		hl_sprite.setPosition(x * DELTA_X, y * DELTA_Y);


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

	void TextButton::scroll(const float direction) {
		image_y_position += (100*cn::DELTA_Y) * direction;
		text_y_position += (100 * cn::DELTA_Y) * direction;

		sprite.move(0, (100 * cn::DELTA_Y) * direction);
		hl_sprite.move(0, (100 * cn::DELTA_Y) * direction);
		text.move(0, (100 * cn::DELTA_Y) * direction);
	}

	//================================================================================================================================

}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================