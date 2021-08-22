#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <linux_parser.h>

using std::string;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                                
  string User();                            
  string Command();                         
  float CpuUtilization();                   
  string Ram();                             
  long int UpTime();                        
  bool operator<(Process const& a) const;   

  // TODO: Declare any necessary private members
 private:
 int pid_{};
 float cpu_utilization_{};
 long int ram_{};
};

#endif