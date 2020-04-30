#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
	string line;
	string memType;
	// Initializing an empty vector
	vector<float> memKB = { 0, 0 };
	std::ifstream stream(kProcDirectory + kMeminfoFilename);
	if (stream.is_open()) {
		// Only reading the first four lines
		for (int i = 0; i < 2; i++) {
			std::getline(stream, line);
			std::istringstream linestream(line);
			linestream >> memType >> memKB[i];
			//std::cout << memKB[i] << "\n";
		}
	}
	// Using the following formula:
	// Total used memory = MemTotal - MemFree
	return memKB[0] - memKB[1];
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
	string line;
	float activeTime = 0.0;
	float idleTime = 0.0;
	std::ifstream stream(kProcDirectory + kUptimeFilename);
	if (stream.is_open()) {
		std::getline(stream, line);
		std::istringstream linestream(line);
		linestream >> activeTime >> idleTime;
		//std::cout << activeTime << "\n";
		//std::cout << idleTime << "\n";
	}
	// Adding floats and returning long which rounds them nicely
	return activeTime + idleTime;
}

// DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
	string line;
	string cpuType;
	// Initializing vector
	vector<long> cpujf = { 0, 0, 0, 0, 0, 0, 0 };
	std::ifstream stream(kProcDirectory + kStatFilename);
	if (stream.is_open()) {
		std::getline(stream, line);
		std::istringstream linestream(line);
		linestream >> cpuType >> cpujf[0] >> cpujf[1] >> cpujf[2] >> cpujf[3] >> cpujf[4] >> cpujf[5] >> cpujf[6];
		//std::cout << cpujf[0] << "\n";
		//std::cout << cpujf[1] << "\n";
	}
	// Adding the values from the first seven columns
	return cpujf[0] + cpujf[1] + cpujf[2] + cpujf[3] + cpujf[4] + cpujf[5] + cpujf[6];
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
	string line;
	string cpuType;
	// Initializing vector
	vector<long> cpujf = { 0, 0, 0, 0, 0, 0, 0 };
	std::ifstream stream(kProcDirectory + kStatFilename);
	if (stream.is_open()) {
		std::getline(stream, line);
		std::istringstream linestream(line);
		linestream >> cpuType >> cpujf[0] >> cpujf[1] >> cpujf[2] >> cpujf[3] >> cpujf[4] >> cpujf[5] >> cpujf[6];
		//std::cout << cpujf[0] << "\n";
		//std::cout << cpujf[1] << "\n";
	}
	// Adding the values for all columns except 'Idle' and 'iowait'
	return cpujf[0] + cpujf[1] + cpujf[2] + cpujf[5] + cpujf[6];
}

// DONE: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
	string line;
	string cpuType;
	// Initializing vector
	vector<long> cpujf = { 0, 0, 0, 0, 0, 0, 0 };
	std::ifstream stream(kProcDirectory + kStatFilename);
	if (stream.is_open()) {
		std::getline(stream, line);
		std::istringstream linestream(line);
		linestream >> cpuType >> cpujf[0] >> cpujf[1] >> cpujf[2] >> cpujf[3] >> cpujf[4] >> cpujf[5] >> cpujf[6];
		//std::cout << cpujf[0] << "\n";
		//std::cout << cpujf[1] << "\n";
	}
	// Adding the values for 'Idle' and 'iowait'
	return cpujf[3] + cpujf[4];
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
	string line;
	string lineName;
	int numberProcesses = 0;
	bool lineNotFound = true;
	std::ifstream stream(kProcDirectory + kStatFilename);
	if (stream.is_open()) {
		while (std::getline(stream, line) && lineNotFound) {
			std::istringstream linestream(line);
			linestream >> lineName >> numberProcesses;
			//std::cout << lineName << "\n";
			if (lineName.compare("processes") == 0) {
				lineNotFound = false;
			}
		}
	}
	return numberProcesses;
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
	string line;
	string lineName;
	int numberProcesses = 0;
	bool lineNotFound = true;
	std::ifstream stream(kProcDirectory + kStatFilename);
	if (stream.is_open()) {
		while (std::getline(stream, line) && lineNotFound) {
			std::istringstream linestream(line);
			linestream >> lineName >> numberProcesses;
			//std::cout << lineName << "\n";
			if (lineName.compare("procs_running") == 0) {
				lineNotFound = false;
			}
		}
	}
	return numberProcesses;
}

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
	string processID = to_string(pid);
	string filePath = "/proc/" + processID + "/cmdline";
	string line;
	std::ifstream stream(filePath);
	if (stream.is_open()) {
		std::getline(stream, line);
	}
	return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
	string processID = to_string(pid);
	string filePath = "/proc/" + processID + "/status";
	string line;
	bool needToSearch = true;
	string lineName, userid;
	std::ifstream stream(filePath);
	if (stream.is_open()) {
		while (needToSearch) {
			std::getline(stream, line);
			std::istringstream linestream(line);
			linestream >> lineName >> userid;
			//std::cout << lineName << "\n";
			if (lineName.compare("Uid:") == 0) {
				needToSearch = false;
			}
		}
	}
	return userid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
	string processID = to_string(pid);
	string filePath = "/proc/" + processID + "/stat";
	string line;
	// If it looks stupid, but works, then it is not stupid! :-)
	string v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22;
	std::ifstream stream(filePath);
	if (stream.is_open()) {
		std::getline(stream, line);
		std::istringstream linestream(line);
		linestream >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7 >> v8 >> v9 >> v10 >> v11 >> v12 >> v13 >> v14 >> v15 >> v16 >> v17 >> v18 >> v19 >> v20 >> v21 >> v22;
	}
	long returnValue = std::stol(v22);
	return returnValue;
}
