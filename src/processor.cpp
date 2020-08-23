#include "processor.h"
#include "linux_parser.h"

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
	long active = LinuxParser::ActiveJiffies();
	long total = LinuxParser::Jiffies();
	float activeFloat = active;
	float totalFloat = total;
	float percentageUsed = activeFloat/totalFloat;
	return percentageUsed;
}
