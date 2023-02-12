#include "car.h"
#include "mainwindow.h"

void car::set_motionPar(double speed, double wspeed, double acc, double wacc)
{
    max_acc = acc;
    max_wacc = wacc;
    max_speed = speed;
    max_wspeed = wspeed;
}
