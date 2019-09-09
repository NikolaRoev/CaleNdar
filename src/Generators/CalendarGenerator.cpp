#include "pch.h"
#include "CalendarGenerator.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

int day_number(const int& day, const int& month, int year) {
	std::array<int, 12> t = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

	year -= month < 3;
	return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

std::string day_name(const int& index) {
	std::array<std::string, 7> names = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	return names[index];
}

std::string month_name(const int& month_number) {
	std::array<std::string, 12> months = { "January", "February", "March",
											"April", "May", "June",
											"July", "August", "September",
											"October", "November", "December" };

	return (months[month_number]);
}

int number_of_days(const int& month_number, const int& year) {
	// January 
	if (month_number == 0)
		return (31);

	// February 
	if (month_number == 1)
	{
		// If the year is leap then February has 
		// 29 days 
		if (year % 400 == 0 ||
			(year % 4 == 0 && year % 100 != 0))
			return (29);
		else
			return (28);
	}

	// March 
	if (month_number == 2)
		return (31);

	// April 
	if (month_number == 3)
		return (30);

	// May 
	if (month_number == 4)
		return (31);

	// June 
	if (month_number == 5)
		return (30);

	// July 
	if (month_number == 6)
		return (31);

	// August 
	if (month_number == 7)
		return (31);

	// September 
	if (month_number == 8)
		return (30);

	// October 
	if (month_number == 9)
		return (31);

	// November 
	if (month_number == 10)
		return (30);

	// December 
	if (month_number == 11)
		return (31);

	return -1;
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

cn::Year generate_calendar(const int& year) {
	cn::Year out;
	out.year = year;

	int temp_day_number = 0;

	int current = day_number(1, 1, year);

	for (int i = 0; i < 12; i++) {
		int days = number_of_days(i, year);

		cn::Month month;
		month.number = i;
		month.name = month_name(i);

		int k = current;
		for (int j = 1; j <= days; j++) {
			
			cn::Day day = { temp_day_number++, j, day_name(k) };
			month.days.push_back(day);

			if (++k > 6) k = 0;
		}

		current = k;
		out.months[i] = month;
	}

	return out;
}


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================