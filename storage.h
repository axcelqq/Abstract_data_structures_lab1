#ifndef STORAGE_H
#define STORAGE_H

#include "registry.h"

void saveRegistry(const char* filename, Registry& r);
void loadRegistry(const char* filename, Registry& r);

#endif