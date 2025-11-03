//
// Created by r1nge on 10/29/25.
//

#include "NKCoordinatesConverter.h"

#include "NKWindow.h"


double NKCoordinatesConverter::ScreenToWorldX(double x, double cameraX) {
    return cameraX + (x - SCREEN_WIDTH / 2);
}

double NKCoordinatesConverter::ScreenToWorldY(double y, double cameraY) {
    return cameraY - (y + SCREEN_HEIGHT / 2);
}

double NKCoordinatesConverter::WorldToScreenX(double x, double cameraX) {
    return (x + SCREEN_WIDTH / 2) - cameraX;
}

double NKCoordinatesConverter::WorldToScreenY(double y, double cameraY) {
    return (y - SCREEN_HEIGHT / 2) - cameraY;
}