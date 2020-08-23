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
  string userID = LinuxParser::Uid(Pid());
  // Need to call User with id
  string username = "TOFIX";
  return username;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  int v1 = std::stoi(Ram());
  int v2 = std::stoi(a.Ram());
  return v1 > v2;
}
