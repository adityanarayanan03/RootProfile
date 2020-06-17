#include "main.h"

class MovingAverageFilter 
/*
Class for the classic Average Filter.
*/
{
public:
    int boxSize; //Number of elements to average over.
    int iterationNumber = 0; //Number of data points received
    std::vector<double> latestValues; //Vector of the [boxSize] latest values

    MovingAverageFilter(int i) //Constructor. makes sure that latestValues has the right number of elements.
    {
        boxSize = i;
        for (unsigned i = 0; i < boxSize; i++)
        {
            latestValues.push_back(0.0);
        }
    }

    double getFilteredVal(double latestVal)
    {
        double cumVal = 0;
        latestValues[iterationNumber % boxSize] = latestVal; //Changes the value in the correct position.
        iterationNumber += 1; //Move on to the next position
        for (unsigned i = 0; i < latestValues.size(); i++) //Loop over our vector and average it
        {
            cumVal += latestValues[i];
        }
        return cumVal / (latestValues.size()); //Return the averaged result.
    }
};