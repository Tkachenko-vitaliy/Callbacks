#pragma once

#include <stdio.h>

typedef void(*ptr_callback) (int eventID, void* pContextData);  // (1) 

void setup(ptr_callback pPtrCallback, void* pContextData);
void run();
