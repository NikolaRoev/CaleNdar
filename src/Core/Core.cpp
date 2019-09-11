#include "pch.h"
#include "Core.h"
#include "..\Globals.h"



//================================================================================================================================

void Core::set_delta_values() {
	cn::DELTA_X = 1 - (((native_width - static_cast<float>(window_width)) / (native_width / 100.0f)) / 100.0f);
	cn::DELTA_Y = 1 - (((native_height - static_cast<float>(window_height)) / (native_height / 100.0f)) / 100.0f);
}

//================================================================================================================================

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

void Core::setup_window(const sf::VideoMode mode, const uint32_t style) {
	window.create(mode, "CaleNdar", style);

	const char imageData[] =
	{
		'\x89', '\x50', '\x4e', '\x47', '\x0d', '\x0a', '\x1a', '\x0a', '\x00', '\x00', '\x00', '\x0d', '\x49', '\x48', '\x44', '\x52', '\x00', '\x00', '\x00', '\x20',
		'\x00', '\x00', '\x00', '\x20', '\x08', '\x06', '\x00', '\x00', '\x00', '\x73', '\x7a', '\x7a', '\xf4', '\x00', '\x00', '\x00', '\x09', '\x70', '\x48', '\x59',
		'\x73', '\x00', '\x00', '\x2e', '\x23', '\x00', '\x00', '\x2e', '\x23', '\x01', '\x78', '\xa5', '\x3f', '\x76', '\x00', '\x00', '\x06', '\xca', '\x69', '\x54',
		'\x58', '\x74', '\x58', '\x4d', '\x4c', '\x3a', '\x63', '\x6f', '\x6d', '\x2e', '\x61', '\x64', '\x6f', '\x62', '\x65', '\x2e', '\x78', '\x6d', '\x70', '\x00',
		'\x00', '\x00', '\x00', '\x00', '\x3c', '\x3f', '\x78', '\x70', '\x61', '\x63', '\x6b', '\x65', '\x74', '\x20', '\x62', '\x65', '\x67', '\x69', '\x6e', '\x3d',
		'\x22', '\xef', '\xbb', '\xbf', '\x22', '\x20', '\x69', '\x64', '\x3d', '\x22', '\x57', '\x35', '\x4d', '\x30', '\x4d', '\x70', '\x43', '\x65', '\x68', '\x69',
		'\x48', '\x7a', '\x72', '\x65', '\x53', '\x7a', '\x4e', '\x54', '\x63', '\x7a', '\x6b', '\x63', '\x39', '\x64', '\x22', '\x3f', '\x3e', '\x20', '\x3c', '\x78',
		'\x3a', '\x78', '\x6d', '\x70', '\x6d', '\x65', '\x74', '\x61', '\x20', '\x78', '\x6d', '\x6c', '\x6e', '\x73', '\x3a', '\x78', '\x3d', '\x22', '\x61', '\x64',
		'\x6f', '\x62', '\x65', '\x3a', '\x6e', '\x73', '\x3a', '\x6d', '\x65', '\x74', '\x61', '\x2f', '\x22', '\x20', '\x78', '\x3a', '\x78', '\x6d', '\x70', '\x74',
		'\x6b', '\x3d', '\x22', '\x41', '\x64', '\x6f', '\x62', '\x65', '\x20', '\x58', '\x4d', '\x50', '\x20', '\x43', '\x6f', '\x72', '\x65', '\x20', '\x35', '\x2e',
		'\x36', '\x2d', '\x63', '\x31', '\x34', '\x35', '\x20', '\x37', '\x39', '\x2e', '\x31', '\x36', '\x33', '\x34', '\x39', '\x39', '\x2c', '\x20', '\x32', '\x30',
		'\x31', '\x38', '\x2f', '\x30', '\x38', '\x2f', '\x31', '\x33', '\x2d', '\x31', '\x36', '\x3a', '\x34', '\x30', '\x3a', '\x32', '\x32', '\x20', '\x20', '\x20',
		'\x20', '\x20', '\x20', '\x20', '\x20', '\x22', '\x3e', '\x20', '\x3c', '\x72', '\x64', '\x66', '\x3a', '\x52', '\x44', '\x46', '\x20', '\x78', '\x6d', '\x6c',
		'\x6e', '\x73', '\x3a', '\x72', '\x64', '\x66', '\x3d', '\x22', '\x68', '\x74', '\x74', '\x70', '\x3a', '\x2f', '\x2f', '\x77', '\x77', '\x77', '\x2e', '\x77',
		'\x33', '\x2e', '\x6f', '\x72', '\x67', '\x2f', '\x31', '\x39', '\x39', '\x39', '\x2f', '\x30', '\x32', '\x2f', '\x32', '\x32', '\x2d', '\x72', '\x64', '\x66',
		'\x2d', '\x73', '\x79', '\x6e', '\x74', '\x61', '\x78', '\x2d', '\x6e', '\x73', '\x23', '\x22', '\x3e', '\x20', '\x3c', '\x72', '\x64', '\x66', '\x3a', '\x44',
		'\x65', '\x73', '\x63', '\x72', '\x69', '\x70', '\x74', '\x69', '\x6f', '\x6e', '\x20', '\x72', '\x64', '\x66', '\x3a', '\x61', '\x62', '\x6f', '\x75', '\x74',
		'\x3d', '\x22', '\x22', '\x20', '\x78', '\x6d', '\x6c', '\x6e', '\x73', '\x3a', '\x78', '\x6d', '\x70', '\x3d', '\x22', '\x68', '\x74', '\x74', '\x70', '\x3a',
		'\x2f', '\x2f', '\x6e', '\x73', '\x2e', '\x61', '\x64', '\x6f', '\x62', '\x65', '\x2e', '\x63', '\x6f', '\x6d', '\x2f', '\x78', '\x61', '\x70', '\x2f', '\x31',
		'\x2e', '\x30', '\x2f', '\x22', '\x20', '\x78', '\x6d', '\x6c', '\x6e', '\x73', '\x3a', '\x78', '\x6d', '\x70', '\x4d', '\x4d', '\x3d', '\x22', '\x68', '\x74',
		'\x74', '\x70', '\x3a', '\x2f', '\x2f', '\x6e', '\x73', '\x2e', '\x61', '\x64', '\x6f', '\x62', '\x65', '\x2e', '\x63', '\x6f', '\x6d', '\x2f', '\x78', '\x61',
		'\x70', '\x2f', '\x31', '\x2e', '\x30', '\x2f', '\x6d', '\x6d', '\x2f', '\x22', '\x20', '\x78', '\x6d', '\x6c', '\x6e', '\x73', '\x3a', '\x73', '\x74', '\x45',
		'\x76', '\x74', '\x3d', '\x22', '\x68', '\x74', '\x74', '\x70', '\x3a', '\x2f', '\x2f', '\x6e', '\x73', '\x2e', '\x61', '\x64', '\x6f', '\x62', '\x65', '\x2e',
		'\x63', '\x6f', '\x6d', '\x2f', '\x78', '\x61', '\x70', '\x2f', '\x31', '\x2e', '\x30', '\x2f', '\x73', '\x54', '\x79', '\x70', '\x65', '\x2f', '\x52', '\x65',
		'\x73', '\x6f', '\x75', '\x72', '\x63', '\x65', '\x45', '\x76', '\x65', '\x6e', '\x74', '\x23', '\x22', '\x20', '\x78', '\x6d', '\x6c', '\x6e', '\x73', '\x3a',
		'\x64', '\x63', '\x3d', '\x22', '\x68', '\x74', '\x74', '\x70', '\x3a', '\x2f', '\x2f', '\x70', '\x75', '\x72', '\x6c', '\x2e', '\x6f', '\x72', '\x67', '\x2f',
		'\x64', '\x63', '\x2f', '\x65', '\x6c', '\x65', '\x6d', '\x65', '\x6e', '\x74', '\x73', '\x2f', '\x31', '\x2e', '\x31', '\x2f', '\x22', '\x20', '\x78', '\x6d',
		'\x6c', '\x6e', '\x73', '\x3a', '\x70', '\x68', '\x6f', '\x74', '\x6f', '\x73', '\x68', '\x6f', '\x70', '\x3d', '\x22', '\x68', '\x74', '\x74', '\x70', '\x3a',
		'\x2f', '\x2f', '\x6e', '\x73', '\x2e', '\x61', '\x64', '\x6f', '\x62', '\x65', '\x2e', '\x63', '\x6f', '\x6d', '\x2f', '\x70', '\x68', '\x6f', '\x74', '\x6f',
		'\x73', '\x68', '\x6f', '\x70', '\x2f', '\x31', '\x2e', '\x30', '\x2f', '\x22', '\x20', '\x78', '\x6d', '\x70', '\x3a', '\x43', '\x72', '\x65', '\x61', '\x74',
		'\x6f', '\x72', '\x54', '\x6f', '\x6f', '\x6c', '\x3d', '\x22', '\x41', '\x64', '\x6f', '\x62', '\x65', '\x20', '\x50', '\x68', '\x6f', '\x74', '\x6f', '\x73',
		'\x68', '\x6f', '\x70', '\x20', '\x43', '\x43', '\x20', '\x32', '\x30', '\x31', '\x39', '\x20', '\x28', '\x57', '\x69', '\x6e', '\x64', '\x6f', '\x77', '\x73',
		'\x29', '\x22', '\x20', '\x78', '\x6d', '\x70', '\x3a', '\x43', '\x72', '\x65', '\x61', '\x74', '\x65', '\x44', '\x61', '\x74', '\x65', '\x3d', '\x22', '\x32',
		'\x30', '\x31', '\x39', '\x2d', '\x30', '\x39', '\x2d', '\x31', '\x31', '\x54', '\x31', '\x35', '\x3a', '\x31', '\x33', '\x3a', '\x31', '\x37', '\x2b', '\x30',
		'\x33', '\x3a', '\x30', '\x30', '\x22', '\x20', '\x78', '\x6d', '\x70', '\x3a', '\x4d', '\x65', '\x74', '\x61', '\x64', '\x61', '\x74', '\x61', '\x44', '\x61',
		'\x74', '\x65', '\x3d', '\x22', '\x32', '\x30', '\x31', '\x39', '\x2d', '\x30', '\x39', '\x2d', '\x31', '\x31', '\x54', '\x31', '\x35', '\x3a', '\x31', '\x35',
		'\x3a', '\x35', '\x39', '\x2b', '\x30', '\x33', '\x3a', '\x30', '\x30', '\x22', '\x20', '\x78', '\x6d', '\x70', '\x3a', '\x4d', '\x6f', '\x64', '\x69', '\x66',
		'\x79', '\x44', '\x61', '\x74', '\x65', '\x3d', '\x22', '\x32', '\x30', '\x31', '\x39', '\x2d', '\x30', '\x39', '\x2d', '\x31', '\x31', '\x54', '\x31', '\x35',
		'\x3a', '\x31', '\x35', '\x3a', '\x35', '\x39', '\x2b', '\x30', '\x33', '\x3a', '\x30', '\x30', '\x22', '\x20', '\x78', '\x6d', '\x70', '\x4d', '\x4d', '\x3a',
		'\x49', '\x6e', '\x73', '\x74', '\x61', '\x6e', '\x63', '\x65', '\x49', '\x44', '\x3d', '\x22', '\x78', '\x6d', '\x70', '\x2e', '\x69', '\x69', '\x64', '\x3a',
		'\x31', '\x39', '\x38', '\x32', '\x61', '\x37', '\x65', '\x61', '\x2d', '\x39', '\x66', '\x30', '\x32', '\x2d', '\x32', '\x39', '\x34', '\x37', '\x2d', '\x62',
		'\x66', '\x30', '\x38', '\x2d', '\x65', '\x33', '\x37', '\x63', '\x66', '\x35', '\x32', '\x36', '\x36', '\x32', '\x36', '\x32', '\x22', '\x20', '\x78', '\x6d',
		'\x70', '\x4d', '\x4d', '\x3a', '\x44', '\x6f', '\x63', '\x75', '\x6d', '\x65', '\x6e', '\x74', '\x49', '\x44', '\x3d', '\x22', '\x61', '\x64', '\x6f', '\x62',
		'\x65', '\x3a', '\x64', '\x6f', '\x63', '\x69', '\x64', '\x3a', '\x70', '\x68', '\x6f', '\x74', '\x6f', '\x73', '\x68', '\x6f', '\x70', '\x3a', '\x36', '\x65',
		'\x31', '\x61', '\x38', '\x39', '\x38', '\x66', '\x2d', '\x35', '\x66', '\x37', '\x35', '\x2d', '\x38', '\x64', '\x34', '\x66', '\x2d', '\x38', '\x37', '\x30',
		'\x65', '\x2d', '\x38', '\x38', '\x34', '\x62', '\x65', '\x36', '\x64', '\x30', '\x37', '\x38', '\x39', '\x31', '\x22', '\x20', '\x78', '\x6d', '\x70', '\x4d',
		'\x4d', '\x3a', '\x4f', '\x72', '\x69', '\x67', '\x69', '\x6e', '\x61', '\x6c', '\x44', '\x6f', '\x63', '\x75', '\x6d', '\x65', '\x6e', '\x74', '\x49', '\x44',
		'\x3d', '\x22', '\x78', '\x6d', '\x70', '\x2e', '\x64', '\x69', '\x64', '\x3a', '\x34', '\x39', '\x37', '\x32', '\x37', '\x31', '\x33', '\x38', '\x2d', '\x31',
		'\x35', '\x62', '\x66', '\x2d', '\x32', '\x64', '\x34', '\x32', '\x2d', '\x38', '\x32', '\x35', '\x65', '\x2d', '\x62', '\x62', '\x61', '\x37', '\x39', '\x31',
		'\x62', '\x36', '\x34', '\x34', '\x32', '\x30', '\x22', '\x20', '\x64', '\x63', '\x3a', '\x66', '\x6f', '\x72', '\x6d', '\x61', '\x74', '\x3d', '\x22', '\x69',
		'\x6d', '\x61', '\x67', '\x65', '\x2f', '\x70', '\x6e', '\x67', '\x22', '\x20', '\x70', '\x68', '\x6f', '\x74', '\x6f', '\x73', '\x68', '\x6f', '\x70', '\x3a',
		'\x43', '\x6f', '\x6c', '\x6f', '\x72', '\x4d', '\x6f', '\x64', '\x65', '\x3d', '\x22', '\x33', '\x22', '\x20', '\x70', '\x68', '\x6f', '\x74', '\x6f', '\x73',
		'\x68', '\x6f', '\x70', '\x3a', '\x49', '\x43', '\x43', '\x50', '\x72', '\x6f', '\x66', '\x69', '\x6c', '\x65', '\x3d', '\x22', '\x73', '\x52', '\x47', '\x42',
		'\x20', '\x49', '\x45', '\x43', '\x36', '\x31', '\x39', '\x36', '\x36', '\x2d', '\x32', '\x2e', '\x31', '\x22', '\x3e', '\x20', '\x3c', '\x78', '\x6d', '\x70',
		'\x4d', '\x4d', '\x3a', '\x48', '\x69', '\x73', '\x74', '\x6f', '\x72', '\x79', '\x3e', '\x20', '\x3c', '\x72', '\x64', '\x66', '\x3a', '\x53', '\x65', '\x71',
		'\x3e', '\x20', '\x3c', '\x72', '\x64', '\x66', '\x3a', '\x6c', '\x69', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x61', '\x63', '\x74', '\x69',
		'\x6f', '\x6e', '\x3d', '\x22', '\x63', '\x72', '\x65', '\x61', '\x74', '\x65', '\x64', '\x22', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x69',
		'\x6e', '\x73', '\x74', '\x61', '\x6e', '\x63', '\x65', '\x49', '\x44', '\x3d', '\x22', '\x78', '\x6d', '\x70', '\x2e', '\x69', '\x69', '\x64', '\x3a', '\x34',
		'\x39', '\x37', '\x32', '\x37', '\x31', '\x33', '\x38', '\x2d', '\x31', '\x35', '\x62', '\x66', '\x2d', '\x32', '\x64', '\x34', '\x32', '\x2d', '\x38', '\x32',
		'\x35', '\x65', '\x2d', '\x62', '\x62', '\x61', '\x37', '\x39', '\x31', '\x62', '\x36', '\x34', '\x34', '\x32', '\x30', '\x22', '\x20', '\x73', '\x74', '\x45',
		'\x76', '\x74', '\x3a', '\x77', '\x68', '\x65', '\x6e', '\x3d', '\x22', '\x32', '\x30', '\x31', '\x39', '\x2d', '\x30', '\x39', '\x2d', '\x31', '\x31', '\x54',
		'\x31', '\x35', '\x3a', '\x31', '\x33', '\x3a', '\x31', '\x37', '\x2b', '\x30', '\x33', '\x3a', '\x30', '\x30', '\x22', '\x20', '\x73', '\x74', '\x45', '\x76',
		'\x74', '\x3a', '\x73', '\x6f', '\x66', '\x74', '\x77', '\x61', '\x72', '\x65', '\x41', '\x67', '\x65', '\x6e', '\x74', '\x3d', '\x22', '\x41', '\x64', '\x6f',
		'\x62', '\x65', '\x20', '\x50', '\x68', '\x6f', '\x74', '\x6f', '\x73', '\x68', '\x6f', '\x70', '\x20', '\x43', '\x43', '\x20', '\x32', '\x30', '\x31', '\x39',
		'\x20', '\x28', '\x57', '\x69', '\x6e', '\x64', '\x6f', '\x77', '\x73', '\x29', '\x22', '\x2f', '\x3e', '\x20', '\x3c', '\x72', '\x64', '\x66', '\x3a', '\x6c',
		'\x69', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x61', '\x63', '\x74', '\x69', '\x6f', '\x6e', '\x3d', '\x22', '\x73', '\x61', '\x76', '\x65',
		'\x64', '\x22', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x69', '\x6e', '\x73', '\x74', '\x61', '\x6e', '\x63', '\x65', '\x49', '\x44', '\x3d',
		'\x22', '\x78', '\x6d', '\x70', '\x2e', '\x69', '\x69', '\x64', '\x3a', '\x30', '\x30', '\x31', '\x61', '\x66', '\x65', '\x30', '\x65', '\x2d', '\x65', '\x64',
		'\x39', '\x39', '\x2d', '\x32', '\x63', '\x34', '\x34', '\x2d', '\x38', '\x35', '\x61', '\x62', '\x2d', '\x61', '\x62', '\x66', '\x31', '\x39', '\x38', '\x66',
		'\x66', '\x39', '\x32', '\x34', '\x65', '\x22', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x77', '\x68', '\x65', '\x6e', '\x3d', '\x22', '\x32',
		'\x30', '\x31', '\x39', '\x2d', '\x30', '\x39', '\x2d', '\x31', '\x31', '\x54', '\x31', '\x35', '\x3a', '\x31', '\x33', '\x3a', '\x31', '\x37', '\x2b', '\x30',
		'\x33', '\x3a', '\x30', '\x30', '\x22', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x73', '\x6f', '\x66', '\x74', '\x77', '\x61', '\x72', '\x65',
		'\x41', '\x67', '\x65', '\x6e', '\x74', '\x3d', '\x22', '\x41', '\x64', '\x6f', '\x62', '\x65', '\x20', '\x50', '\x68', '\x6f', '\x74', '\x6f', '\x73', '\x68',
		'\x6f', '\x70', '\x20', '\x43', '\x43', '\x20', '\x32', '\x30', '\x31', '\x39', '\x20', '\x28', '\x57', '\x69', '\x6e', '\x64', '\x6f', '\x77', '\x73', '\x29',
		'\x22', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x63', '\x68', '\x61', '\x6e', '\x67', '\x65', '\x64', '\x3d', '\x22', '\x2f', '\x22', '\x2f',
		'\x3e', '\x20', '\x3c', '\x72', '\x64', '\x66', '\x3a', '\x6c', '\x69', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x61', '\x63', '\x74', '\x69',
		'\x6f', '\x6e', '\x3d', '\x22', '\x73', '\x61', '\x76', '\x65', '\x64', '\x22', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x69', '\x6e', '\x73',
		'\x74', '\x61', '\x6e', '\x63', '\x65', '\x49', '\x44', '\x3d', '\x22', '\x78', '\x6d', '\x70', '\x2e', '\x69', '\x69', '\x64', '\x3a', '\x31', '\x39', '\x38',
		'\x32', '\x61', '\x37', '\x65', '\x61', '\x2d', '\x39', '\x66', '\x30', '\x32', '\x2d', '\x32', '\x39', '\x34', '\x37', '\x2d', '\x62', '\x66', '\x30', '\x38',
		'\x2d', '\x65', '\x33', '\x37', '\x63', '\x66', '\x35', '\x32', '\x36', '\x36', '\x32', '\x36', '\x32', '\x22', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74',
		'\x3a', '\x77', '\x68', '\x65', '\x6e', '\x3d', '\x22', '\x32', '\x30', '\x31', '\x39', '\x2d', '\x30', '\x39', '\x2d', '\x31', '\x31', '\x54', '\x31', '\x35',
		'\x3a', '\x31', '\x35', '\x3a', '\x35', '\x39', '\x2b', '\x30', '\x33', '\x3a', '\x30', '\x30', '\x22', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a',
		'\x73', '\x6f', '\x66', '\x74', '\x77', '\x61', '\x72', '\x65', '\x41', '\x67', '\x65', '\x6e', '\x74', '\x3d', '\x22', '\x41', '\x64', '\x6f', '\x62', '\x65',
		'\x20', '\x50', '\x68', '\x6f', '\x74', '\x6f', '\x73', '\x68', '\x6f', '\x70', '\x20', '\x43', '\x43', '\x20', '\x32', '\x30', '\x31', '\x39', '\x20', '\x28',
		'\x57', '\x69', '\x6e', '\x64', '\x6f', '\x77', '\x73', '\x29', '\x22', '\x20', '\x73', '\x74', '\x45', '\x76', '\x74', '\x3a', '\x63', '\x68', '\x61', '\x6e',
		'\x67', '\x65', '\x64', '\x3d', '\x22', '\x2f', '\x22', '\x2f', '\x3e', '\x20', '\x3c', '\x2f', '\x72', '\x64', '\x66', '\x3a', '\x53', '\x65', '\x71', '\x3e',
		'\x20', '\x3c', '\x2f', '\x78', '\x6d', '\x70', '\x4d', '\x4d', '\x3a', '\x48', '\x69', '\x73', '\x74', '\x6f', '\x72', '\x79', '\x3e', '\x20', '\x3c', '\x2f',
		'\x72', '\x64', '\x66', '\x3a', '\x44', '\x65', '\x73', '\x63', '\x72', '\x69', '\x70', '\x74', '\x69', '\x6f', '\x6e', '\x3e', '\x20', '\x3c', '\x2f', '\x72',
		'\x64', '\x66', '\x3a', '\x52', '\x44', '\x46', '\x3e', '\x20', '\x3c', '\x2f', '\x78', '\x3a', '\x78', '\x6d', '\x70', '\x6d', '\x65', '\x74', '\x61', '\x3e',
		'\x20', '\x3c', '\x3f', '\x78', '\x70', '\x61', '\x63', '\x6b', '\x65', '\x74', '\x20', '\x65', '\x6e', '\x64', '\x3d', '\x22', '\x72', '\x22', '\x3f', '\x3e',
		'\xea', '\x73', '\xcb', '\x8f', '\x00', '\x00', '\x00', '\xa1', '\x49', '\x44', '\x41', '\x54', '\x58', '\xc3', '\xed', '\x96', '\x4b', '\x0e', '\xc0', '\x20',
		'\x08', '\x44', '\xb9', '\xff', '\xa5', '\xa7', '\x4b', '\x93', '\xca', '\x2f', '\x14', '\x14', '\x53', '\x4d', '\x5c', '\x98', '\x8c', '\xfa', '\x04', '\x19',
		'\x25', '\x22', '\xc2', '\xe6', '\x7e', '\x01', '\xc6', '\x00', '\x00', '\x69', '\x0d', '\x40', '\x4a', '\xd7', '\x22', '\x50', '\xde', '\x5c', '\x00', '\x59',
		'\x27', '\x65', '\x4e', '\x6e', '\x03', '\x54', '\x6d', '\xee', '\x4e', '\xc1', '\x9b', '\xb6', '\x22', '\x0a', '\xb7', '\x0c', '\xdb', '\x02', '\x64', '\x97',
		'\x9a', '\x29', '\x9b', '\x00', '\x56', '\x54', '\x00', '\x73', '\x11', '\x87', '\x0b', '\x32', '\x25', '\xc2', '\x7a', '\x84', '\x1a', '\x4e', '\xe7', '\x3a',
		'\x47', '\x00', '\x4c', '\x42', '\x06', '\x20', '\xac', '\x11', '\xef', '\x40', '\x05', '\x80', '\x35', '\x47', '\x12', '\x86', '\x52', '\xe0', '\xd5', '\xb4',
		'\x06', '\x30', '\xff', '\x03', '\x5f', '\x35', '\x61', '\x80', '\x0c', '\x48', '\xd1', '\x07', '\xb6', '\x1b', '\x91', '\x95', '\x3b', '\xe5', '\x3d', '\xcf',
		'\xf1', '\x81', '\x8e', '\x00', '\x21', '\x1f', '\xf0', '\x1a', '\xda', '\x11', '\x00', '\x6b', '\xdf', '\x82', '\x4e', '\x00', '\xfb', '\x8c', '\xc8', '\x63',
		'\x42', '\xce', '\xc5', '\x43', '\x00', '\xff', '\xfc', '\x94', '\x3e', '\x64', '\xb2', '\xa4', '\x94', '\x4b', '\x89', '\x14', '\xb5', '\x00', '\x00', '\x00',
		'\x00', '\x49', '\x45', '\x4e', '\x44', '\xae', '\x42', '\x60', '\x82', '\xff',
	};
	sf::Image icon;
	icon.loadFromMemory(imageData, sizeof(imageData));
	window.setIcon(32, 32, icon.getPixelsPtr());

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