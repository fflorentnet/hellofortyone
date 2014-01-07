#ifndef ANNEAU_H
#define ANNEAU_H

#include <stdlib.h>
#include <stdio.h>

#include "global.h"

#define TAILLEANNEAU 16

void checkAnneau();
void* cycleAnneau(void* data);
void initAnneau();

#endif
