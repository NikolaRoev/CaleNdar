#pragma once
#include "pch.h"

#ifdef _DEBUG
	#define LOG(x) {\
	std::cout << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " << (x) << '\n';\
	}
#else
	#define LOG(x)
#endif

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
	};

	//================================================================================================================================

	struct Image : public Drawable {
		sf::Texture texture;
		sf::Sprite sprite;

		sf::FloatRect position;

		void setup(const char* data, std::size_t size, const float& x, const float& y) override;

		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}

		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void draw(sf::RenderWindow& window) override;
	};

	//================================================================================================================================

	struct Button : public Drawable {
		sf::Texture texture;
		sf::Sprite sprite;

		sf::FloatRect position;
		
		sf::Texture hl_texture;
		sf::Sprite hl_sprite;

		std::function<void()> function;


		Button(std::function<void()> _function);


		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) override;

		void setup(const char* data, std::size_t size, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}

		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;
	};

	//================================================================================================================================

	struct Label : public Drawable {
		sf::Texture texture;
		sf::Sprite sprite;

		sf::FloatRect position;
		
		sf::Font font;
		sf::Text text;

		sf::FloatRect text_position;

		void setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override;

		void setup(const char* data, std::size_t size, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}


		virtual void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		virtual void draw(sf::RenderWindow& window) override;

		virtual void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;
	};

	//================================================================================================================================

	struct TextButton : public Label {
		sf::Texture hl_texture;
		sf::Sprite hl_sprite;
		
		std::function<void()> function;


		TextButton(std::function<void()> _function);


		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override;

		void setup(const char* data, std::size_t size, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const char* data_hl, std::size_t size_hl, const float& x, const float& y) override {}
		void setup(const char* data, std::size_t size, const float& x, const float& y, const std::string& path, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}


		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;
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


	//Call this when you want to add a drawable.
	void add_drawable(cn::Drawable& image);
	

	//This is our application.
	void main_loop(std::vector<cn::Drawable*>& in_frame, bool& loop_selector);
	//This is our pop-up loop.
	void pop_up_loop(std::vector<cn::Drawable*>& in_frame_background, std::vector<cn::Drawable*>& in_frame_foreground, sf::FloatRect& constraints, bool& loop_selector);
};

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================
