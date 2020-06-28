#include "processor.h"

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
	long active = LinuxParser::ActiveJiffies();
	long total = LinuxParser::Jiffies();
	float percentageUsed = active/total;
	return percentageUsed;
}
