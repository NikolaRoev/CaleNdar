#pragma once
#include "pch.h"

#include "Globals.h"

#include "Generators\CalendarGenerator.h"
#include "Generators\Serializer.h"
#include "Generators\CurrentTime.h"

#include "Core\Core.h"

#include "Structures/Structures.h"

#include "ResourceManager/ResourceManager.h"

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

class UI {
private:

	//================================================================================================================================

	Core* core{ nullptr };

	bool loop_selector{ true };

	//================================================================================================================================

	std::vector<cn::Year> years;

	//================================================================================================================================

	cn::Year* current_year{ nullptr };
	cn::Month* current_month{ nullptr };
	cn::Day* current_day{ nullptr };
	cn::Event* current_event{ nullptr };

	std::array<int, 3> current_date; //Year, Month, Day.

	//================================================================================================================================

	std::vector<cn::Drawable*> start_menu_in_frame;
	
	std::vector<cn::Drawable*> day_selection_menu_in_frame;
	
	std::vector<cn::Drawable*> individual_day_menu_in_frame;


	std::vector<cn::Drawable*> pop_up_frame;

	//================================================================================================================================

	//Start Menu Drawables ===========================================================================================================

	cn::Image* start_menu_background;
	cn::Label* start_menu_time;
	cn::Button* start_menu_arrow_left;
	cn::Label* start_menu_year;
	cn::Button* start_menu_arrow_right;
	cn::TextButton* start_menu_today;
	std::array<cn::TextButton*, 12> start_menu_month_buttons;

	//================================================================================================================================

	//Day Selection Menu Drawables ===================================================================================================

	cn::Image* day_selection_menu_background;

	cn::Label* day_selection_menu_month;
	cn::TextButton* day_selection_menu_back;
	
	cn::Label* day_selection_menu_monday;
	cn::Label* day_selection_menu_tuesday;
	cn::Label* day_selection_menu_wednesday;
	cn::Label* day_selection_menu_thursday;
	cn::Label* day_selection_menu_friday;
	cn::Label* day_selection_menu_saturday;
	cn::Label* day_selection_menu_sunday;

	std::array<std::pair<cn::TextButton*, cn::Label*>, 35> day_selection_menu_days;

	//================================================================================================================================

	//Individual Day Menu Drawables ==================================================================================================




	//================================================================================================================================

	//================================================================================================================================

	void set_current_year(const int year);

	void set_drawables();

	//================================================================================================================================

	void start_menu_loop(); //temp comment just do what is done in entry point by setting everything in this menu,
							//and just add the movement and stuff in the button funtions and shit
	void day_selection_menu_loop();

	void individual_day_loop();

	//================================================================================================================================

public:
	void application_loop(); // temp comment just add a switch statement for each menu loop
};

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

