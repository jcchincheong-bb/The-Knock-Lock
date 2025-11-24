#pragma once

int loadPatternFromNVS(unsigned long targetPattern[]);
void savePatternToNVS(unsigned long intervals[], int count);
bool checkKnockPattern(unsigned long recordedIntervals[], int count);
