#pragma once
#include "pch.h"

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

#define EXIT 0
#define START_MENU 1
#define DAY_SELECTION_MENU 2
#define INDIVIDUAL_DAY_MENU 3

//================================================================================================================================

namespace cn {
	inline int APPLICATION_STATE{ START_MENU };
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	//================================================================================================================================

	inline float DELTA_X;
	inline float DELTA_Y;

	//================================================================================================================================

	struct Drawable {

		virtual void resize(const float& resize_delta_x, const float& resize_delta_y) = 0;

		virtual void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) = 0;

		virtual void draw(sf::RenderWindow& window) = 0;

		virtual void set_image(const char* data, std::size_t size, const float& x, const float& y) = 0;

		virtual void set_hl(const char* data_hl, std::size_t size_hl, const float& x, const float& y) = 0;

		virtual void set_font(const std::string& path, const unsigned int& text_size, const sf::Color color, const float& x, const float& y, const std::string& _text) = 0;
	};

	//================================================================================================================================

	struct Image : public Drawable {
		sf::Texture texture;
		sf::Sprite sprite;

		sf::FloatRect position;

		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void draw(sf::RenderWindow& window) override;

		void set_image(const char* data, std::size_t size, const float& x, const float& y) override;

		void set_hl(const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {}

		void set_font(const std::string& path, const unsigned int& text_size, const sf::Color color, const float& x, const float& y, const std::string& _text) override {}
	};

	//================================================================================================================================

	struct Button : public Drawable {
		sf::Texture texture;
		sf::Sprite sprite;

		sf::FloatRect position;
		
		sf::Texture hl_texture;
		sf::Sprite hl_sprite;


		std::function<void()> function;

		Button(std::function<void()> _function) : function(_function) {}


		void resize(const float& resize_delta_x, const float& resize_delta_y) override {
			sprite.scale(resize_delta_x, resize_delta_y);
			hl_sprite.scale(resize_delta_x, resize_delta_y);

			position = sprite.getGlobalBounds();
		}


		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override {
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

		void draw(sf::RenderWindow& window) override {
			window.draw(sprite);
		}

		void set_image(const char* data, std::size_t size, const float& x, const float& y) override {
			texture.loadFromMemory(data, size);
			sprite.setTexture(texture);
			sprite.setPosition(x*DELTA_X, y*DELTA_Y);
		}

		void set_hl(const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {
			hl_texture.loadFromMemory(data_hl, size_hl);
			hl_sprite.setTexture(hl_texture);
			hl_sprite.setPosition(x*DELTA_X, y*DELTA_Y);
		}

		void set_font(const std::string& path, const unsigned int& text_size, const sf::Color color, const float& x, const float& y, const std::string& _text) override {}
	};

	//================================================================================================================================

	struct Label : public Drawable {
		sf::Texture texture;
		sf::Sprite sprite;

		sf::FloatRect position;
		
		sf::Font font;
		sf::Text text;

		sf::FloatRect text_position;

		virtual void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		virtual void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		virtual void draw(sf::RenderWindow& window) override;

		virtual void set_image(const char* data, std::size_t size, const float& x, const float& y) override;

		virtual void set_hl(const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {}

		virtual void set_font(const std::string& path, const unsigned int& text_size, const sf::Color color, const float& x, const float& y, const std::string& _text) override;
	};

	//================================================================================================================================

	struct TextButton : public Label {
		sf::Texture hl_texture;
		sf::Sprite hl_sprite;
		
		
		std::function<void()> function;

		TextButton(std::function<void()> _function) : function(_function) {}


		void resize(const float& resize_delta_x, const float& resize_delta_y) override {
			sprite.scale(resize_delta_x, resize_delta_y);
			hl_sprite.scale(resize_delta_x, resize_delta_y);

			position = sprite.getGlobalBounds();

			text.scale(resize_delta_x, resize_delta_y);
			text_position = text.getGlobalBounds();
		}

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override {
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

		void draw(sf::RenderWindow& window) override {
			window.draw(sprite);
			window.draw(text);
		}

		void set_image(const char* data, std::size_t size, const float& x, const float& y) override {
			texture.loadFromMemory(data, size);
			sprite.setTexture(texture);
			sprite.setPosition(x*DELTA_X, y*DELTA_Y);
		}

		void set_hl(const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {
			hl_texture.loadFromMemory(data_hl, size_hl);
			hl_sprite.setTexture(hl_texture);
			hl_sprite.setPosition(x*DELTA_X, y*DELTA_Y);
		}

		void set_font(const std::string& path, const unsigned int& text_size, const sf::Color color, const float& x, const float& y, const std::string& _text) override {
			font.loadFromFile(path);
			text.setFont(font);
			text.setCharacterSize(text_size);
			text.setFillColor(color);
			text.setPosition(x*DELTA_X, y*DELTA_Y);

			text.setString(_text);
		}
	};

	//================================================================================================================================

}

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

	//Call this when you want to add an image to be drawn.
	void add_drawable(cn::Drawable& image, const char* data, std::size_t size, const float& x, const float& y);
	//Button.
	void add_drawable(cn::Drawable& image, const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y);
	//Label.
	void add_drawable(cn::Drawable& image, const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text);
	//TextButton.
	void add_drawable(cn::Drawable& image, const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text);

	//This is our application.
	void main_loop(std::vector<cn::Drawable*>& in_frame);
	//This is our pop-up loop.
	void pop_up_loop(std::vector<cn::Drawable*>& in_frame_background, std::vector<cn::Drawable*>& in_frame_foreground, sf::FloatRect& constraints);
};

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================
