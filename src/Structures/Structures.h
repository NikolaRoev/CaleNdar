#pragma once
#include "pch.h"



//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	struct Event {
		int start_time{ 0 };
		int end_time{ -1 };

		std::string name;
		std::string description;
	};

	struct Day {
		int number{ 0 };
		int date{ 0 };
		std::string name;

		std::vector<Event> events{};
	};

	struct Month {
		int number{ 0 };
		std::string name;

		std::vector<Day> days{};
	};

	struct Year {
		int year{ 0 };

		std::array<Month, 12> months{};
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
		virtual void setup(sf::Texture& texture, const float& x, const float& y) = 0;

		//Button.
		virtual void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y) = 0;

		//Label.
		virtual void setup(sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) = 0;

		//Text button.
		virtual void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y, sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) = 0;

		virtual void resize(const float& resize_delta_x, const float& resize_delta_y) = 0;

		virtual void draw(sf::RenderWindow& window) = 0;

		virtual void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) = 0;

		virtual void set_function(std::function<void()> _function) = 0;
	};

	//================================================================================================================================

	struct Image : public Drawable {
		sf::Sprite sprite;


		void setup(sf::Texture& texture, const float& x, const float& y) override;

		void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y) override {}
		void setup(sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}
		void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y, sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}

		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void draw(sf::RenderWindow& window) override;

		void set_function(std::function<void()> _function) override {}
	};

	//================================================================================================================================

	struct Button : public Drawable {
		sf::Sprite sprite;

		sf::Sprite hl_sprite;

		std::function<void()> function;


		void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y) override;

		void setup(sf::Texture& texture, const float& x, const float& y) override {}
		void setup(sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}
		void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y, sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}

		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void set_function(std::function<void()> _function) override;
	};

	//================================================================================================================================

	struct Label : public Drawable {
		

		sf::Text text;


		void setup(sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override;

		void setup(sf::Texture& texture, const float& x, const float& y) override {}
		void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y) override {}
		void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y, sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}


		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void set_function(std::function<void()> _function) override {}
	};

	//================================================================================================================================

	struct TextButton : public Drawable {
		sf::Sprite sprite;
		
		sf::Sprite hl_sprite;

		sf::Text text;

		std::function<void()> function;


		void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y, sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override;

		void setup(sf::Texture& texture, const float& x, const float& y) override {}
		void setup(sf::Texture& texture, sf::Texture& hl_texture, const float& x, const float& y) override {}
		void setup(sf::Font& font, const unsigned int& text_size, const sf::Color color, const float& text_x, const float& text_y, const std::string& _text) override {}


		void resize(const float& resize_delta_x, const float& resize_delta_y) override;

		void draw(sf::RenderWindow& window) override;

		void draw(sf::RenderWindow& window, sf::Event& event, sf::Mouse& mouse) override;

		void set_function(std::function<void()> _function) override;
	};

	//================================================================================================================================

}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================



//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	struct IndividualEvent {
		TextButton* event_button;

		Image* pop_up_mask{ nullptr };
		Image* pop_up_background{ nullptr };

		Button* save_event{ nullptr };
		TextButton* start_time{ nullptr };
		TextButton* end_time{ nullptr };
		Button* delete_event{ nullptr };
		TextButton* event_title{ nullptr };
		TextButton* event_description{ nullptr };

		Event placeholder_event;
	};

	struct MonthSelectionMenu {
		Image* background{ nullptr };
		Label* time{ nullptr };
		Button* arrow_left{ nullptr };
		Label* year{ nullptr };
		Button* arrow_right{ nullptr };
		Button* today{ nullptr };
		std::array<TextButton*, 12> month_buttons{ nullptr };
	};

	struct DaySelectionMenu {
		Image* background{ nullptr };
		Label* time{ nullptr };
		Label* month_name{ nullptr };
		Button* back{ nullptr };
		std::array<TextButton*, 42> day_buttons{ nullptr };
	};

	struct EventSelectionMenu {
		Image* background{ nullptr };
		Label* time{ nullptr };
		Label* day_name{ nullptr };
		Button* add_event{ nullptr };
		Button* back{ nullptr };

		//For new Event:
		Image* pop_up_mask{ nullptr };
		Image* pop_up_background{ nullptr };

		Button* new_save_event{ nullptr };
		TextButton* new_start_time{ nullptr };
		TextButton* new_end_time{ nullptr };
		Button* new_delete_event{ nullptr };
		TextButton* new_event_title{ nullptr };
		TextButton* new_event_description{ nullptr };

		Event holder_for_new_event;
		//End.

		std::map<int, IndividualEvent> events{}; //The key is the start time.
	};

	struct YearDrawables {
		MonthSelectionMenu months_menu{};
		std::array<DaySelectionMenu, 12> days_menu{};
		std::array<EventSelectionMenu, 366> events_menu{};
	};

}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================