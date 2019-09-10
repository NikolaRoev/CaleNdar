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

void UI::application_loop() {
	core = new Core;
	sf::VideoMode mode = { 1024, 576, 32 };
	core->setup_window(mode, sf::Style::Default);

	manager = new Manager;
	manager->core = core;
	manager->ui = this;

	deserialize(years);
	
	auto[year, month, day] = get_current_date();
	current_date = { year, month, day };

	set_current_year(year);
	cn::Event test0 = { 0, 1, "test0", "TEST0" };
	cn::Event test1 = { 1, 1, "test1", "TEST1" };
	cn::Event test2 = { 2, 1, "test2", "TEST2" };
	cn::Event test3 = { 3, 1, "test3", "TEST3" };
	cn::Event test4 = { 4, 1, "test4", "TEST4" };

	years[0].months[0].days[0].events = { test0, test1, test2, test3, test4 };

	manager->preload_textures();
	manager->preload_static_drawables();
	manager->preload_years();

	manager->set_month_frame();



	std::thread clock([&]() {
		while (core->window.isOpen()) {
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


	core->main_loop(manager->preloaded_years, manager->in_frame, manager->in_scroll_frame, manager->in_pop_up_frame, reset);


	clock.join();
	serialize(years);
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================