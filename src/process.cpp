#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// Process constructor
 Process::Process(int pid): pid_(pid), cpu_utilization_(LinuxParser::ProcessCpuUtilization(pid)){}

// DONE: Return this process's ID
int Process::Pid() { return pid_;}

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { 
    cpu_utilization_ = LinuxParser::ProcessCpuUtilization(pid_);
    return cpu_utilization_; }

// DONE: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// DONE: Return this process's memory utilization
string Process::Ram() { 
    string ram{LinuxParser::Ram(pid_)};
    ram_ = std::stoi(ram);
    ram = std::to_string(ram_);
    return ram; }

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {

    return cpu_utilization_ < a.cpu_utilization_; 
}