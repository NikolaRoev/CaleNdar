#pragma once
#include "pch.h"



//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	struct Event {
		int start_time{ 0 };
		int end_time{ 0 };

		std::string name;
		std::string description;
	};

	struct Day {
		int date{ 0 };
		std::string name;

		std::vector<Event> events;
	};

	struct Month {
		std::string name;

		std::vector<Day> days;
	};

	struct Year {
		int year{ 0 };

		std::array<Month, 12> months;
	};

}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================



//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	//================================================================================================================================

	struct Drawable {

		float image_x_position{ 0.f };
		float image_y_position{ 0.f };

		float text_x_position{ 0.f };
		float text_y_position{ 0.f };

		//Image.
		virtual void setup(const char* data, std::size_t size, const float& x, const float& y) = 0;

		//Button.
		virtual void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) = 0;

		//Label.
		virtual void setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) = 0;

		//Text button.
		virtual void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) = 0;

		virtual void resize(const float& resize_delta_x, const float& resize_delta_y) = 0;

		virtual void draw(sf::RenderWindow& window) = 0;

		virtual void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) = 0;

		virtual void set_function(std::function<void()> _function) = 0;
	};

	//================================================================================================================================

	struct Image : public Drawable {
		sf::Texture texture;
		sf::Sprite sprite;


		void setup(const char* data, std::size_t size, const float& x, const float& y) override;

		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}

		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void draw(sf::RenderWindow& window) override;

		void set_function(std::function<void()> _function) override {}
	};

	//================================================================================================================================

	struct Button : public Drawable {
		sf::Texture texture;
		sf::Sprite sprite;


		sf::Texture hl_texture;
		sf::Sprite hl_sprite;

		std::function<void()> function;


		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) override;

		void setup(const char* data, std::size_t size, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}

		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void set_function(std::function<void()> _function) override;
	};

	//================================================================================================================================

	struct Label : public Drawable {
		sf::Texture texture;
		sf::Sprite sprite;


		sf::Font font;
		sf::Text text;


		void setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override;

		void setup(const char* data, std::size_t size, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}


		virtual void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		virtual void draw(sf::RenderWindow& window) override;

		virtual void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		virtual void set_function(std::function<void()> _function) override {}
	};

	//================================================================================================================================

	struct TextButton : public Label {
		sf::Texture hl_texture;
		sf::Sprite hl_sprite;

		std::function<void()> function;


		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override;

		void setup(const char* data, std::size_t size, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}


		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void set_function(std::function<void()> _function) override;
	};

	//================================================================================================================================

}