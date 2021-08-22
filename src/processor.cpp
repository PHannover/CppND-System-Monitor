#include <vector>
#include <string>

#include "processor.h"
#include "linux_parser.h"

using std::vector;
using std::string;
using std::stof;

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() { 
    // Names for values:  0:user 1:nice 2:system 3:idle 4:iowait 5:irq 6:softirq 7:steal 8:guest 9:guest_nice 
    vector<string> cpu_utilization_values{LinuxParser::CpuUtilization()};
    float const user{stof(cpu_utilization_values[0])};
    float const nice{stof(cpu_utilization_values[1])};
    float const system{stof(cpu_utilization_values[2])};
    float const idle{stof(cpu_utilization_values[3])};
    float const iowait{stof(cpu_utilization_values[4])};
    float const irq{stof(cpu_utilization_values[5])};
    float const softirq{stof(cpu_utilization_values[6])};
    float const steal{stof(cpu_utilization_values[7])};

    float totalIdle;
    float nonIdle;
    float total;
    float CPU_Percentage;
    
    totalIdle = idle + iowait;
    nonIdle = user + nice + system + irq + softirq + steal;
    total = totalIdle + nonIdle;
    CPU_Percentage = (total - totalIdle)/total;
    return CPU_Percentage;
}