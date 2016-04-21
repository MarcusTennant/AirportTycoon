#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Inventory.h"
#include "Building.h"

void graphics_setupDisplay();
void graphics_destroyDisplay();
void graphics_display(building_st* buildArr, int buildSel, inventory_st* inventory, int key);

#endif //GRAPHICS_H_
