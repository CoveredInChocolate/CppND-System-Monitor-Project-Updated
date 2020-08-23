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
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// DONE: Skipping the bonus
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
	// Total used memory = (MemTotal - MemFree)/MemTotal
	return (memKB[0] - memKB[1])/memKB[0];
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
	// Only need to return the active time
  long returnActiveTime = activeTime;
	return returnActiveTime;
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
long LinuxParser::ActiveJiffies(int pid) {
  /*
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

    //#14 utime - CPU time spent in user code, measured in clock ticks
    //#15 stime - CPU time spent in kernel code, measured in clock ticks
    //#16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
    //#17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)
    //#22 starttime - Time when the process started, measured in clock ticks


  // 14,15,16,17
  int utime = stoi(v14);
  int stime = stoi(v15);
  int cutime = stoi(v16);
  int cstime = stoi(v17);
  int starttime = stoi(v22);

  int total_time = total_time + cutime + cstime;
  int seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));
  cpu_usage = 100 * ((total_time / Hertz) / seconds)

	return returnValue;
  */
  return 0;
}

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
vector<string> LinuxParser::CpuUtilization() {
  return {"12", "15", "10", "5"};
}

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

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
	string processID = to_string(pid);
	string filePath = "/proc/" + processID + "/status";
	string line;
	bool needToSearch = true;
	string lineName;
	float memoryUsageKB = 0;
	int memoryUsageMB;
	std::ifstream stream(filePath);
	if (stream.is_open()) {
		while (needToSearch) {
			std::getline(stream, line);
			std::istringstream linestream(line);
			linestream >> lineName >> memoryUsageKB;
			//std::cout << lineName << "\n";
			if (lineName.compare("VmSize:") == 0) {
				needToSearch = false;
			}
		}
	}
	// Rounding to integer. Cutting away the decimals
	memoryUsageMB = memoryUsageKB / 1024;
	return to_string(memoryUsageMB);
}

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

// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string line, uname, uid;
	string userIdToFind = LinuxParser::Uid(pid);
	string filename = "/etc/passwd";
	bool lineNotFound = true;
  std::ifstream stream(filename);
	if (stream.is_open()) {
		while (std::getline(stream, line) && lineNotFound) {
  			std::istringstream linestream(line);
				vector<int> colons = {0, 0, 0, 0, 0, 0};
				int colonNumber = 0;
				for (unsigned int i = 0; i < line.size(); i++) {
					if (line[i] == ':') {
						colons[colonNumber] = i;
						colonNumber = colonNumber + 1;
					}
				}
				uname = line.substr(0, colons[0]);
				uid = line.substr(colons[1]+1, colons[2] - colons[1] - 1);

				if (uid == userIdToFind) {
					lineNotFound = false;
				}
      }
    }
  return uname;
}

// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  long SystemUptime = LinuxParser::UpTime();
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
	//long returnValue = std::stol(v22);
	// Correcting from clock ticks to seconds (neither times look correct)
	long returnValue = SystemUptime - std::stol(v22)/sysconf(_SC_CLK_TCK);
	return returnValue;
}
