//
// Created by r1nge on 10/29/25.
//

#include "NKCoordinatesConverter.h"

#include "NKWindow.h"


double NKCoordinatesConverter::ScreenToWorldX(double x) {
    return x - SCREEN_WIDTH / 2;
}

double NKCoordinatesConverter::ScreenToWorldY(double y) {
    return y + SCREEN_HEIGHT / 2;
}
