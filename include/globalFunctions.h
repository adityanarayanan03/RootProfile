#include "main.h"

void plotterPrint(std::vector<double> elements){
    /*
    Takes vector of elements to print to plotter
    {x_data, y1, y2, etc.}
    */
    printf("%s", "{");
    for (unsigned i=0; i<elements.size(); i++){
        printf("%f", elements.at(i));
        if (i != elements.size() -1){
            printf("%s", ",");
        }
    }
    printf("%s \n", "}");
}

void arcade(MotorGroup left, MotorGroup right, double joyVert, double joyHoriz){
    left.moveVoltage(12000*(joyVert + joyHoriz));
    right.moveVoltage(12000*(joyVert - joyHoriz));
}