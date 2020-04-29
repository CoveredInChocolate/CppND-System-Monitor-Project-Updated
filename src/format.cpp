#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
	string returnTime;
	int hrs = seconds / 3600;
	int secsWithoutHours = seconds - (hrs * 3600);
	int mins = secsWithoutHours / 60;
	int secs = secsWithoutHours - (mins * 60);
	returnTime = to_string(hrs) + ":" + to_string(mins) + ":" + to_string(secs);
	if (hrs < 10) {
		returnTime = "0" + returnTime;
	}
	return returnTime;
}