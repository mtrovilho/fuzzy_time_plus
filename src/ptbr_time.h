#pragma once

#include "string.h"

void ptbr_time_2lines(int hours, int minutes, char* str_hour, char* str_minute);
void ptbr_time_3lines(int hours, int minutes, char* str_hour, char* str_minute1, char* str_minute2);
void fuzzy_time(int hours, int minutes, char* str_line1, char* str_line2, char* str_line3);
