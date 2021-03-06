#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h" //Added so LinuxParser:: works

using std::set;
using std::size_t;
using std::string;
using std::vector;

// Populating processes_
System::System() {
	vector<int> procPids = LinuxParser::Pids();
		for (unsigned int i = 0; i < procPids.size(); i++) {
			//std::cout << "procPids[" << i << "]: " << procPids[i] << "\n";
			processes_.push_back(Process(procPids[i]));
		}
}

// DONE: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// DONE: Return a container composed of the system's processes
// Added sort()
vector<Process>& System::Processes() {
	sort(processes_.begin(), processes_.end());
	return processes_;
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() {
	return LinuxParser::Kernel();
}

// DONE: Return the system's memory utilization
float System::MemoryUtilization() {
	return LinuxParser::MemoryUtilization();
}

// DONE: Return the operating system name
std::string System::OperatingSystem() {
	return LinuxParser::OperatingSystem();
}

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() {
	return LinuxParser::RunningProcesses();
}

// DONE: Return the total number of processes on the system
int System::TotalProcesses() {
	return LinuxParser::TotalProcesses();
}

// DONE: Return the number of seconds since the system started running
long int System::UpTime() {
	return LinuxParser::UpTime();
}
