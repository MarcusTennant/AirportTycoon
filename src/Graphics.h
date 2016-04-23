#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Inventory.h"
#include "Building.h"

void graphics_setupDisplay();
void graphics_destroyDisplay();
void graphics_display(building_st* buildArr, int selX, int selY, inventory_st* inventory);

#endif //GRAPHICS_H_
