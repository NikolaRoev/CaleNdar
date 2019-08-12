#include "pch.h"
#include "Serializer.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

void serialize_string(std::ofstream& os, std::string& string) {
	size_t len = string.length();
	os.write((char*)& len, sizeof(len));

	os.write(&string[0], len);
}

void serialize_events(std::ofstream& os, std::vector<cn::Event>& events) {
	size_t len = events.size();
	os.write((char*)& len, sizeof(len));

	for (unsigned int i = 0; i < len; ++i) {
		os.write((char*)& events[i].start_time, sizeof(int));
		os.write((char*)& events[i].end_time, sizeof(int));
		serialize_string(os, events[i].name);
		serialize_string(os, events[i].description);
	}
}

void serialize_days(std::ofstream& os, std::vector<cn::SavedDay>& days) {
	size_t len = days.size();
	os.write((char*)& len, sizeof(len));

	for (unsigned int i = 0; i < len; ++i) {
		os.write((char*)& days[i].date, sizeof(int));
		serialize_string(os, days[i].name);
		serialize_events(os, days[i].events);
	}
}

void serialize_months(std::ofstream& os, std::array<cn::SavedMonth, 12> & months) {
	size_t len = months.size();
	os.write((char*)& len, sizeof(len));

	for (unsigned int i = 0; i < len; ++i) {
		serialize_string(os, months[i].name);
		serialize_days(os, months[i].days);
	}
}

void serialize(std::vector<cn::SavedYear>& save) {
	std::ofstream os("save.bin", std::ios::binary);
	
	size_t len = save.size();
	os.write((char*)& len, sizeof(len));

	for (unsigned int i = 0; i < len; ++i) {
		os.write((char*)& save[i].year, sizeof(int));
		serialize_months(os, save[i].months);
	}

	os.flush();
	os.close();
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

void deserialize_string(std::ifstream& is, std::string& string) {
	size_t len;
	is.read((char*)& len, sizeof(len));
	string.reserve(len);

	is.read(&string[0], len);
}

void deserialize_events(std::ifstream& is, std::vector<cn::Event>& events) {
	size_t len;
	is.read((char*)& len, sizeof(len));
	events.resize(len);

	for (unsigned int i = 0; i < len; ++i) {
		is.read((char*)& events[i].start_time, sizeof(int));
		is.read((char*)& events[i].end_time, sizeof(int));
		deserialize_string(is, events[i].name);
		deserialize_string(is, events[i].description);
	}
}

void deserialize_days(std::ifstream& is, std::vector<cn::SavedDay>& days) {
	size_t len;
	is.read((char*)& len, sizeof(len));
	days.resize(len);

	for (unsigned int i = 0; i < len; ++i) {
		is.read((char*)& days[i].date, sizeof(int));
		deserialize_string(is, days[i].name);
		deserialize_events(is, days[i].events);
	}
}

void deserialize_months(std::ifstream& is, std::array<cn::SavedMonth, 12> & months) {
	size_t len;
	is.read((char*)& len, sizeof(len));

	for (unsigned int i = 0; i < len; ++i) {
		deserialize_string(is, months[i].name);
		deserialize_days(is, months[i].days);
	}
}

void deserialize(std::vector<cn::SavedYear>& save) {
	std::ifstream is("save.bin", std::ios::binary);

	size_t len;
	is.read((char*)& len, sizeof(len));
	save.resize(len);

	for (unsigned int i = 0; i < len; ++i) {
		is.read((char*)& save[i].year, sizeof(int));
		deserialize_months(is, save[i].months);
	}

	is.close();
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================