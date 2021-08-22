#include <string>

#include "format.h"

using std::string;
using std::to_string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function

string Format::ElapsedTime(long int total_seconds) { 
    string output;
    int hours;
    int minutes;
    int seconds;
    hours = total_seconds/3600;
    total_seconds = total_seconds % 3600;
    minutes = total_seconds/60;
    seconds = total_seconds %60;

    if(hours<10) output = "0" + to_string(hours);
    else output = to_string(hours);
    if(minutes<10) output = output + ":0" + to_string(minutes);
    else output = output + ":" + to_string(minutes);
    if(seconds<10) output = output + ":0" + to_string(seconds);
    else output = output + ":" + to_string(seconds);

    return output; 
}