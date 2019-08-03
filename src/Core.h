#pragma once
#include "pch.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	//================================================================================================================================

	struct Image {
		sf::Texture texture;
		sf::Sprite sprite;

		sf::FloatRect position;

		virtual void resize(const double& DELTA_X, const double& DELTA_Y);

		virtual void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse);

		virtual void set_hl(const char* data_hl, std::size_t size_hl, const float& x, const float& y, const double& DELTA_X, const double& DELTA_Y);

		virtual void set_font(const std::string& path, const unsigned int& text_size, const sf::Color color, const float& x, const float& y, const double& DELTA_X, const double& DELTA_Y, const std::string& _text);
	};

	//================================================================================================================================

	template <typename Function, typename... Args>
	struct Button : public Image {
		sf::Texture hl_texture;
		sf::Sprite hl_sprite;

		using ReturnType = std::invoke_result_t<Function, Args...>;
		std::function<ReturnType()> function;


		Button(Function _function, Args... args) : function(std::bind(_function, std::forward<Args>(args)...)) {}


		auto on_click() {
			return function();
		}


		void resize(const double& DELTA_X, const double& DELTA_Y) override {
			sprite.scale(static_cast<float>(DELTA_X), static_cast<float>(DELTA_Y));
			hl_sprite.scale(static_cast<float>(DELTA_X), static_cast<float>(DELTA_Y));

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
							on_click();
						}
						mouse_position = sf::Mouse::getPosition(window);
					}
				}
				window.draw(hl_sprite);
			}
		}


		void set_hl(const char* data_hl, std::size_t size_hl, const float& x, const float& y, const double& DELTA_X, const double& DELTA_Y) override {
			hl_texture.loadFromMemory(data_hl, size_hl);
			hl_sprite.setTexture(hl_texture);
			hl_sprite.setPosition(x, y);
		}
	};

	//================================================================================================================================

	struct Label : public Image {
		sf::Font font;
		sf::Text text;

		sf::FloatRect text_position;

		void resize(const double& DELTA_X, const double& DELTA_Y) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void set_font(const std::string& path, const unsigned int& text_size, const sf::Color color, const float& x, const float& y, const double& DELTA_X, const double& DELTA_Y, const std::string& _text) override;
	};

	//================================================================================================================================

	template <typename Function, typename... Args>
	struct TextButton : public Label {
		sf::Texture hl_texture;
		sf::Sprite hl_sprite;
		
		using ReturnType = std::invoke_result_t<Function, Args...>;
		std::function<ReturnType()> function;


		TextButton(Function _function, Args... args) : function(std::bind(_function, std::forward<Args>(args)...)) {}


		auto on_click() {
			return function();
		}

		void resize(const double& DELTA_X, const double& DELTA_Y) override {
			sprite.scale(static_cast<float>(DELTA_X), static_cast<float>(DELTA_Y));
			hl_sprite.scale(static_cast<float>(DELTA_X), static_cast<float>(DELTA_Y));

			position = sprite.getGlobalBounds();

			text.scale(static_cast<float>(DELTA_X), static_cast<float>(DELTA_Y));
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
							on_click();
						}
						mouse_position = sf::Mouse::getPosition(window);
					}
				}
				window.draw(hl_sprite);
			}
		}

		void set_hl(const char* data_hl, std::size_t size_hl, const float& x, const float& y, const double& DELTA_X, const double& DELTA_Y) override {
			hl_texture.loadFromMemory(data_hl, size_hl);
			hl_sprite.setTexture(hl_texture);
			hl_sprite.setPosition(x, y);
		}

		void set_font(const std::string& path, const unsigned int& text_size, const sf::Color color, const float& x, const float& y, const double& DELTA_X, const double& DELTA_Y, const std::string& _text) override {
			font.loadFromFile(path);
			text.setFont(font);
			text.setCharacterSize(text_size);
			text.setFillColor(color);
			text.setPosition(x, y);

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
	double native_width{1920};
	double native_height{1080};

	unsigned int window_width{0};
	unsigned int window_height{0};

	double DELTA_X{1.0f};
	double DELTA_Y{1.0f};

	std::vector<cn::Image*> drawables;

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
	void add_drawable(cn::Image& image, const char* data, std::size_t size, const float& x, const float& y);
	//Button.
	void add_drawable(cn::Image& image, const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y);
	//Label.
	void add_drawable(cn::Image& image, const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text);
	//TextButton.
	void add_drawable(cn::Image& image, const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text);

	//This is our application.
	void main_loop(std::vector<cn::Image*>& in_frame);
};

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================
