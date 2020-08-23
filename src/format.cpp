#include <string>

#include "format.h"

using std::string;
using std::to_string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
	string returnTime;
	int hrs = seconds / 3600;
	int secsWithoutHours = seconds - (hrs * 3600);
	int mins = secsWithoutHours / 60;
	int secs = secsWithoutHours - (mins * 60);
	string hrsText, minsText, secsText;
	secsText = to_string(secs);
	minsText = to_string(mins);
	hrsText = to_string(hrs);
	if (secs < 10) {
		secsText = "0" + secsText;
	}
	if (mins < 10) {
		minsText = "0" + minsText;
	}
	if (hrs < 10) {
		hrsText = "0" + hrsText;
	}
	returnTime = hrsText + ":" + minsText + ":" + secsText;
	return returnTime;
}
