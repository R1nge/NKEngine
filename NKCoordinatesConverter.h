//
// Created by r1nge on 10/29/25.
//

#ifndef NKENGINE_NKCOORDINATESCONVERTER_H
#define NKENGINE_NKCOORDINATESCONVERTER_H


class NKCoordinatesConverter {
public:
    double ScreenToWorldX(double x, double cameraX);

    double ScreenToWorldY(double y, double cameraY);

    double WorldToScreenX(double x, double cameraX);

    double WorldToScreenY(double y, double cameraY);
};


#endif //NKENGINE_NKCOORDINATESCONVERTER_H
