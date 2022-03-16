#include "StatsView.h"

#include <iostream>

unsigned int StatsView::GetID()
{
    return ID;
}

void StatsView::Update()
{
    std::cout << "Hi, im the StatsView! This is a update.\n";
}
