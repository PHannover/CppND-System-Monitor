#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::stoi;

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
  string key;
  string value;
  string kB;
  float MemTotal{};
  float MemFree{};
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value >> kB) {
        if (key == "MemTotal:") {
          MemTotal = std::stof(value);
        }
        else if (key == "MemFree:") {
          MemFree = std::stof(value);
        }
      }
      if (MemTotal != 0 && MemFree != 0) break;
    }
  }
  return (MemTotal - MemFree) / MemTotal;

}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  string string_uptime, string_idletime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> string_uptime >> string_idletime;
  }
  return stol(string_uptime);
}

/* // TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; } */

// DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string value;
  vector<string> cpu_utilization_values{};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> value){
      cpu_utilization_values.push_back(value);
    }
    cpu_utilization_values.erase(cpu_utilization_values.begin());
  }
  return cpu_utilization_values;
}


// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") { 
          return std::stoi(value);        }
      }
    }
  }
  return 0;
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {  
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") { 
          return std::stoi(value); }
      }
    }
  }
  return 0;
  }

// DONE: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
}

// DONE: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmSize:") {
        value = to_string(stof(value)/1000);
        return value;
      }
    }
  }
  return 0;
}

// DONE: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        return value;
      }
    }
  }
  return 0;
  }

// DONE: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string Uid{LinuxParser::Uid(pid)};
  string line;
  string value;
  string x;
  string key;

  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> value >> x >> key) {
        if (key == Uid) {
          return value;
        }
      }
    }
  }
return string{};
}

// DONE: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid[[maybe_unused]]) {
  string line;
  long int uptime;
  string value;
  vector<string> values;

  std::ifstream process_filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (process_filestream.is_open()) {
    std::getline(process_filestream, line);
    std::istringstream linestream(line);
    while(linestream >> value){
      values.push_back(value);
    }
    uptime = stol(values[21])/sysconf(_SC_CLK_TCK);
  }  
  return uptime;
}

// DONE: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::ProcessCpuUtilization(int pid){
  string line;
  float uptime;
  string value;
  vector<string> values;
  const long int hertz{sysconf(_SC_CLK_TCK)};
  float total_time;
  float starttime;
  float seconds;
  float cpu_usage;
  std::ifstream uptime_filestream(kProcDirectory + kUptimeFilename);
  if (uptime_filestream.is_open()) {
    std::getline(uptime_filestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  std::ifstream process_filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (process_filestream.is_open()) {
    std::getline(process_filestream, line);
    std::istringstream linestream(line);
    while(linestream >> value){
      values.push_back(value);
    }
    total_time = stol(values[13]) + stol(values[14]) + stol(values[15]) + stol(values[16]);
    starttime = stol(values[21]);
    seconds = uptime - (starttime / hertz);
    cpu_usage = ((total_time / hertz) / seconds);
  }
  
  return cpu_usage;
}