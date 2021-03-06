#pragma once
#include "pch.h"
#include "..\Structures\Structures.h"
#include "..\Core\Core.h"
#include "..\UI.h"



//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

class UI;

class Manager {
private:
	//One use:

	cn::Image* static_background{ nullptr };
	cn::Image* static_pop_up_mask{ nullptr };
	cn::Image* static_pop_up_background{ nullptr };
	cn::Button* static_today_button{ nullptr };
	cn::Image* static_event_menu_mask{ nullptr };

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

	sf::Texture event_menu_mask_texture;

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

	//End.

public:
	Core* core{ nullptr };

	UI* ui{ nullptr };

	std::unordered_map<int, cn::YearDrawables> preloaded_years{};



	cn::Label* static_time{ nullptr };

	std::vector<cn::Drawable*> in_frame{};
	std::vector<cn::Drawable*> in_pop_up_frame{};
	std::vector<cn::Drawable*> in_scroll_frame{};



	void preload_textures();

	void preload_static_drawables();

	void preload_years();


	void add_event(cn::Event& _event, std::map<int, cn::IndividualEvent>& _events);

	void sort_events();


	void set_month_frame();

	void set_day_frame();

	void set_event_frame();

	void set_pop_up_frame_new_event();

	void set_pop_up_frame_existing_event();
};

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================