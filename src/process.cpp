#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h" //Added so LinuxParser:: works

using std::string;
using std::to_string;
using std::vector;

// Adding a constructor
Process::Process(int pid):pid_(pid){}

// DONE: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// DONE: Return the command that generated this process
string Process::Command() {
  string cmd = LinuxParser::Command(Pid());
  return cmd;
}

// DONE: Return this process's memory utilization
string Process::Ram() {
  string memUsage = LinuxParser::Ram(Pid());
  return memUsage;
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  // Need to call User with id in User-function
  // string userID = LinuxParser::Uid(Pid());
  string username = LinuxParser::User(Pid());
  return username;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  long timeSeconds = LinuxParser::UpTime(Pid());
  return timeSeconds;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a) const {
bool Process::operator<(Process a) {
  int pid1 = Pid();
  int pid2 = a.Pid();
  int v1 = std::stoi(LinuxParser::Ram(pid1));
  int v2 = std::stoi(LinuxParser::Ram(pid2));
  return v1 > v2;
}
