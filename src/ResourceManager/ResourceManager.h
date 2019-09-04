#pragma once
#include "pch.h"
#include "..\Structures\Structures.h"
#include "..\Core\Core.h"
#include "..\UI.h"

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {

	//================================================================================================================================

	struct EventDate {
		int year;
		int month;
		int day;

		int start_time;
	};

	//================================================================================================================================

	struct EventSorter {
		bool operator()(const EventDate& left, const EventDate& right) const {
			if (left.year < right.year) {
				return left.year < right.year;
			}
			else if (left.month < right.month) {
				return left.month < right.month;
			}
			else if (left.day < right.day) {
				return left.day < right.day;
			}
			else {
				return left.start_time < right.start_time;
			}
		}
	};

	//================================================================================================================================

	struct MonthSelectionMenu {
		Image* background;
		Label* time;
		Button* arrow_left;
		Label* year;
		Button* arrow_right;
		TextButton* today;
		std::array<TextButton*, 12> month_buttons;
	};

	//================================================================================================================================

	struct DaySelectionMenu {

	};

	//================================================================================================================================

	struct EventSelectionMenu {

	};

	//================================================================================================================================

	struct IndividualEvent {

	};

	//================================================================================================================================

	struct YearDrawables {
		MonthSelectionMenu* months_menu;
		std::array<DaySelectionMenu*, 12> days_menu;
		std::array<EventSelectionMenu*, 366> events_menu;
		
		std::map<EventDate, IndividualEvent*, EventSorter> events;
	};

	//================================================================================================================================

}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

class Manager {
private:
	//One use:

	cn::Image* static_background;

	cn::Label* static_year;

	cn::Image* static_pop_up_mask;
	cn::Image* static_pop_up_background;

	sf::Font static_font;

	//End.


	//Month Menu:

	sf::Texture background_texture;       //used in day and event menu

	sf::Texture arrow_left_texture;
	sf::Texture arrow_left_hl_texture;

	sf::Texture arrow_right_texture;
	sf::Texture arrow_right_hl_texture;

	sf::Texture today_button_texture;
	sf::Texture today_button_hl_texture;  //used in back button

	sf::Texture month_button_texture;
	sf::Texture month_button_hl_texture;

	//End.


	//Day Menu:

	sf::Texture back_button_texture;

	sf::Texture day_button_texture;
	sf::Texture day_button_hl_texture;

	sf::Texture event_marker_texture;    //used as save and delete button hl

	//End.


	//Event Menu:

	sf::Texture add_event_button_texture;
	sf::Texture add_event_button_hl_texture;

	sf::Texture event_button_texture;
	sf::Texture event_button_hl_texture;


	sf::Texture pop_up_mask_texture;
	sf::Texture pop_up_background_texture;

	sf::Texture save_event_button_texture;
	sf::Texture delete_event_button_texture;

	sf::Texture start_end_time_entry_texture;
	sf::Texture start_end_time_entry_hl_texture;

	sf::Texture title_entry_texture;
	sf::Texture title_entry_hl_texture;

	sf::Texture description_entry_texture;
	sf::Texture description_entry_hl_texture;

	//End>

public:
	Core* core;

	UI* ui;

	std::unordered_map<int, cn::YearDrawables> preloaded_years;



	cn::Label* static_time;

	std::vector<cn::Drawable*> month_menu_frame;
	std::vector<cn::Drawable*> day_menu_frame;
	std::vector<cn::Drawable*> event_menu_frame;
	std::vector<cn::Drawable*> pop_up_frame;



	void preload_textures();

	void preload_static_drawables();

	void preload_years(const std::vector<cn::Year>& years);


	void add_year(const int _year);

	void add_event(const cn::Event _event, const cn::EventDate _date);


	void set_month_frame();

	void set_day_frame();

	void set_event_frame();

	void set_pop_up_frame();

};

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================