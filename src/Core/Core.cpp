#include "pch.h"
#include "Core.h"
#include "..\Globals.h"



//Private:
void Core::set_delta_values() {
	cn::DELTA_X = 1 - (((native_width - static_cast<float>(window_width)) / (native_width / 100.0f)) / 100.0f);
	cn::DELTA_Y = 1 - (((native_height - static_cast<float>(window_height)) / (native_height / 100.0f)) / 100.0f);
}

void Core::resized_window(const std::unordered_map<int, cn::YearDrawables>& preloaded_years) {
	sf::Vector2u new_size = window.getSize();
	
	sf::FloatRect visibleArea(0, 0, static_cast<float>(new_size.x), static_cast<float>(new_size.y));
	window.setView(sf::View(visibleArea));
	
	window_width = new_size.x;
	window_height = new_size.y;

	float old_delta_x = 1 / cn::DELTA_X;
	float old_delta_y = 1 / cn::DELTA_Y;

	set_delta_values();

	preloaded_years.begin()->second.months_menu.background->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
	preloaded_years.begin()->second.months_menu.time->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
	preloaded_years.begin()->second.months_menu.today->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);

	preloaded_years.begin()->second.events_menu[0].pop_up_mask->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
	preloaded_years.begin()->second.events_menu[0].pop_up_background->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
	preloaded_years.begin()->second.events_menu[0].mask->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);

	for (auto& each : preloaded_years) {
		each.second.months_menu.arrow_left->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
		each.second.months_menu.year->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
		each.second.months_menu.arrow_right->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
		for (auto m_b : each.second.months_menu.month_buttons) {
			m_b->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
		}

		for (auto& d_m : each.second.days_menu) {
			d_m.month_name->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			d_m.back->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			for (auto d_b : d_m.day_buttons) {
				if(d_b) d_b->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			}
		}

		for (auto& e_m : each.second.events_menu) {
			if (e_m.day_name) e_m.day_name->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			if (e_m.add_event) e_m.add_event->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			if (e_m.back) e_m.back->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			if (e_m.new_save_event) e_m.new_save_event->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			if (e_m.new_start_time) e_m.new_start_time->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			if (e_m.new_end_time) e_m.new_end_time->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			if (e_m.new_delete_event) e_m.new_delete_event->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			if (e_m.new_event_title) e_m.new_event_title->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			if (e_m.new_event_description) e_m.new_event_description->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			for (auto& e : e_m.events) {
				e.second.event_button->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
				e.second.delete_event->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
				e.second.event_description->resize(cn::DELTA_X * old_delta_x, cn::DELTA_Y * old_delta_y);
			}
		}
	}
}

//================================================================================================================================

//Public:
void Core::setup_window(const sf::VideoMode mode, const uint32_t style) {
	window.create(mode, "CaleNdar", style);

	//sf::Image icon;
	//window.setIcon(64, 64, icon.getPixelsPtr());

	window_width = mode.width;
	window_height = mode.height;

	set_delta_values();
}

void Core::main_loop(const std::unordered_map<int, cn::YearDrawables>& preloaded_years, const std::vector<cn::Drawable*>& in_frame, const std::vector<cn::Drawable*>& in_scroll_frame, std::vector<cn::Drawable*>& in_pop_up_frame, bool& reset) {
	
	bool ready_to_scroll = true;

	while (window.isOpen()) {
		if (in_pop_up_frame.size()) {
			for (auto each : in_scroll_frame) {
				if (each && !reset) each->draw(window);
			}
			
			for (auto each : in_frame) {
				if (each && !reset) each->draw(window);
			}

			for (auto each : in_pop_up_frame) {
				if (each && !reset) each->draw(window, event, mouse);
			}
		}
		else if (in_scroll_frame.size()) {
			for (auto each : in_scroll_frame) {
				if (each && !reset) {
					float y1 = 150 * cn::DELTA_Y;
					float y2 = 1080 * cn::DELTA_Y;
					if ((each->image_y_position >= y1) || (each->image_y_position < y2)) {
						each->draw(window, event, mouse);
					}
				}
			}

			for (auto each : in_frame) {
				if (each && !reset) each->draw(window, event, mouse);
			}
		}
		else {
			for (auto each : in_frame) {
				if (reset) break;
				if (each && !reset) each->draw(window, event, mouse);
			}
		}

		reset = false;
		window.display();

		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
		}


		if (event.type == sf::Event::Resized) {
			resized_window(preloaded_years);
		}

		if (in_pop_up_frame.size()) {
			sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
			sf::FloatRect pop_up_sprite_size = {360.0f * cn::DELTA_X, 192.0f * cn::DELTA_Y, 1200.0f * cn::DELTA_X, 700.0f * cn::DELTA_Y };
			if (!pop_up_sprite_size.contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y))) {
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					window.waitEvent(event);
					if (event.type == sf::Event::MouseButtonReleased) {
						in_pop_up_frame = {};
					}
				}
			}
		}

		if ((event.type == sf::Event::MouseWheelScrolled) && in_scroll_frame.size() && ready_to_scroll) {
			for (auto each : in_scroll_frame) {
				if (each) each->scroll(event.mouseWheelScroll.delta);
			}
			ready_to_scroll = false;
		}
		if ((event.type != sf::Event::MouseWheelScrolled) && in_scroll_frame.size()) {
			ready_to_scroll = true;
		}
	}
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================