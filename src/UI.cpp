#include "pch.h"
#include "UI.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================



//================================================================================================================================

void UI::set_current_year(const int year) {
	bool set = false;
	
	for (auto& each : years) {
		if (each.year == year) {
			current_year = &each;
			set = true;
		}
	}

	if (!current_year || !set) {
		cn::Year temp_current_year = generate_calendar(year);

		years.push_back(temp_current_year);

		current_year = &years.back();
	}
}

//================================================================================================================================

/*
	//================================================================================================================================

	//Day Selection Menu Drawables ===================================================================================================

	day_selection_menu_background = new cn::Image;

	day_selection_menu_background->setup(day_selection_menu_background_data, sizeof(day_selection_menu_background_data), 0, 0);


	day_selection_menu_month = new cn::Label;
	day_selection_menu_month->setup(nullptr, NULL, 855, 30, "temp/times-new-roman.ttf", 100, sf::Color::Black, 855, 30, "");


	day_selection_menu_back = new cn::TextButton;
	day_selection_menu_back->set_function([&]() {
		loop_selector = false;
		cn::APPLICATION_STATE = START_MENU;
	});


	day_selection_menu_back->setup(day_selection_menu_back_data, sizeof(day_selection_menu_back_data), day_selection_menu_back_hl_data, sizeof(day_selection_menu_back_hl_data), 1550, 30, "temp/times-new-roman.ttf", 100, sf::Color::Black, 1580, 35, "Back");

	day_selection_menu_month->text.setString(current_month->name);

	unsigned int offset = 0;
	if (current_month->days[0].name == "Tuesday") offset = 1;
	if (current_month->days[0].name == "Wednesday") offset = 2;
	if (current_month->days[0].name == "Thursday") offset = 3;
	if (current_month->days[0].name == "Friday") offset = 4;
	if (current_month->days[0].name == "Saturday") offset = 5;
	if (current_month->days[0].name == "Sunday") offset = 6;




	for (unsigned int i = 0; i < current_month->days.size(); i++) {
		int j = i + offset;

		day_selection_menu_days[j].first = new cn::TextButton;
		day_selection_menu_days[j].first->set_function([&, i]() {
			loop_selector = false;
			current_day = &current_month->days[i];
			cn::APPLICATION_STATE = INDIVIDUAL_DAY_MENU;
			});

		float temp_x;
		float temp_y;
		float temp_text_x;
		float temp_text_y;
		//200x150
		//x 44 dx 272
		//y 217 dy 174
		temp_x = (272 * (j % 7)) + 44;
		temp_y = (174 * (j / 7)) + 217;
		temp_text_x = temp_x + 140;
		temp_text_y = temp_y + 1;

		day_selection_menu_days[j].first->setup(day_selection_menu_days_data, sizeof(day_selection_menu_days_data), day_selection_menu_days_hl_data, sizeof(day_selection_menu_days_hl_data), temp_x, temp_y, "temp/times-new-roman.ttf", 50, sf::Color::Black, temp_text_x, temp_text_y, std::to_string(current_month->days[i].date));

		if (current_month->days[i].events.size() > 0) {
			unsigned int number = current_month->days[i].events.size();
			day_selection_menu_days[j].second = new cn::Label;

			day_selection_menu_days[j].second->setup(day_selection_menu_days_date_label_data, sizeof(day_selection_menu_days_date_label_data), 855, 30, "temp/times-new-roman.ttf", 100, sf::Color::Black, 855, 30, std::to_string(number));
		}
		else {
			day_selection_menu_days[j].second = new cn::Label;

			day_selection_menu_days[j].second->setup(nullptr, NULL, 0, 0, "temp/times-new-roman.ttf", 0, sf::Color::Black, 0, 0, "");
		}
	}
	for (const auto& each : day_selection_menu_days) {
		day_selection_menu_in_frame.emplace_back(each.first);
		day_selection_menu_in_frame.emplace_back(each.second);
	}


	else if (setup->event.type == sf::Event::TextEntered) {
		if (setup->event.text.unicode == '\b' && !setup->player_name_temp.empty()) {
			setup->player_name_temp.erase(setup->player_name_temp.size() - 1, 1);
			loader->new_game_name_text.setString(setup->player_name_temp);
		}
		else if (setup->event.text.unicode < 128 && setup->event.text.unicode != '\b') {
			setup->player_name_temp += static_cast<char>(setup->event.text.unicode);
			loader->new_game_name_text.setString(setup->player_name_temp);
		}
	}
*/

//================================================================================================================================

//Public:
void UI::application_loop() {
	core = new Core;
	sf::VideoMode mode = { 1024, 576, 32 };
	core->setup_window(mode, sf::Style::Default);

	manager = new Manager;
	manager->core = core;
	manager->ui = this;
	manager->preload_textures();
	manager->preload_static_drawables();

	deserialize(years);
	
	auto[year, month, day] = get_current_date();
	current_date = { year, month, day };

	set_current_year(year);

	manager->preload_years(years);

	manager->set_month_frame();



	std::thread clock([&]() {
		while (cn::APPLICATION_STATE != EXIT) {
			auto[hour, minute, second] = get_current_time();
			std::string minutes;
			if (minute < 10) {
				minutes.append("0" + std::to_string(minute));
			}
			else {
				minutes.append(std::to_string(minute));
			}
			
			std::string seconds;
			if (second < 10) {
				seconds.append("0" + std::to_string(second));
			}
			else {
				seconds.append(std::to_string(second));
			}
			
			std::string time = std::to_string(hour) + ":" + minutes + ":" + seconds;
			manager->static_time->text.setString(time);
		}
	});



	while (cn::APPLICATION_STATE != EXIT) {
		switch (cn::APPLICATION_STATE) {
			case RUNNING: {
				core->main_loop(manager->preloaded_years, manager->in_frame, manager->in_pop_up_frame, manager->in_scroll_frame);
				break;
			}
			case EXIT: {
				serialize(years);
				break;
			}
		}
	}

	clock.join();
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================