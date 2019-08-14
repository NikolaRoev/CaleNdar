#include "pch.h"
#include "UI.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

void UI::start_menu_loop() {

}

void UI::day_selection_menu_loop() {

}

void UI::individual_day_loop() {

}

//================================================================================================================================

//Public:
void UI::application_loop() {
	deserialize(years);
	
	cn::current_date temp_date = get_current_date();
	current_date = { temp_date.month, temp_date.day };

	for (auto& each : years) {
		if (each.year == temp_date.year) {
			current_year = &each;
		}
	}

	if (!current_year) {
		cn::Year temp_current_year = generate_calendar(temp_date.year);

		years.push_back(temp_current_year);

		current_year = &years.back();
	}
	
	bool open = true;
	while (open) {
		switch (cn::APPLICATION_STATE) {
			case START_MENU: {
				start_menu_loop();
				break;
			}
			case DAY_SELECTION_MENU: {
				day_selection_menu_loop();
				break;
			}
			case INDIVIDUAL_DAY_MENU: {
				individual_day_loop();
				break;
			}
			case EXIT: {
				serialize(years);
				open = false;
				break;
			}
		}
	}
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================