#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>

// class SlipPredictor {

// private:
//     double calculateVelocity(const std::vector<double>& tireSpeeds) {
//         double sum = 0.0;
//         for (double speed : tireSpeeds) {
//             sum += speed;
//         }
//         return sum / tireSpeeds.size();
//     }
// };

int main() {
    int frame= 1;    // Frame number

    float wheel1rates[10] = {0};
    float wheel2rates[10] = {0};
    float wheel3rates[10] = {0};
    float wheel4rates[10] = {0};
    int pointer = 0;
    float wheel1average = 0;
    float wheel2average = 0;
    float wheel3average = 0;
    float wheel4average = 0;

    float threshold = 0.05;  // Threshold for difference for inside and outside wheels

    std::ifstream file("readings.csv");
    std::string line;       // A line in readings the file

    // Open the output file
    std::ofstream outputFile("output.csv");
    
    if (!getline(file, line)) {
        std::cerr << "Error reading the file or file is empty." << std::endl;
        return 1;  // Exit with an error code
    }

    while (getline(file, line))
    {
        std::cout << "\n" << "Processing timeframe: " << frame << std::endl;

        /*
        Each line is a string. 
        In each line, there are 5 values separated by commas.
        First 4 values represent the number of rotations of each tire.
        Last value represents the time since the last reading.
        We need to convert those values to floats.
        */
        std::vector<float> values;  // Store the converted values

        std::istringstream iss(line);
        std::string token;

        while (getline(iss, token, ','))
        {
            float value = std::stof(token);
            values.push_back(value);
        }

        // Access the converted values
        float time = values[0];
        float tire1Rotation = values[1];
        float tire2Rotation = values[2];
        float tire3Rotation = values[3];
        float tire4Rotation = values[4];

        // Process the converted values as needed
        // Print the converted values
        // std::cout << "Tire 1 rate: " << tire1Rotation / time << std::endl;
        // std::cout << "Tire 2 rate: " << tire2Rotation / time << std::endl;
        // std::cout << "Tire 3 rate: " << tire3Rotation / time << std::endl;
        // std::cout << "Tire 4 rate: " << tire4Rotation / time << std::endl;
        // std::cout << std::endl;


        // Update the arrays with the value related to current readings
        wheel1rates[pointer] = tire1Rotation / time;
        wheel2rates[pointer] = tire2Rotation / time;
        wheel3rates[pointer] = tire3Rotation / time;
        wheel4rates[pointer] = tire4Rotation / time;

        // Increment the pointer
        if (pointer == 9) {
            pointer = 0;
        }
        else {
            pointer++;
        }

        // TEST: Print the arrays
        std::cout << "Wheel 1 rates: ";
        for (int i = 0; i < 10; i++) {
            std::cout << wheel1rates[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Wheel 2 rates: ";
        for (int i = 0; i < 10; i++) {
            std::cout << wheel2rates[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Wheel 3 rates: ";
        for (int i = 0; i < 10; i++) {
            std::cout << wheel3rates[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Wheel 4 rates: ";
        for (int i = 0; i < 10; i++) {
            std::cout << wheel4rates[i] << " ";
        }
        std::cout << std::endl;

        // In the beginging, the arrays are filled with zero. 
        // We need to calculate the average of each wheel after the arrays are filled with values.
        if (!(wheel1rates[9] == 0 && wheel2rates[9] == 0 && wheel3rates[9] == 0 && wheel4rates[9] == 0)) {
            // Calculate the average of each wheel
            for (int i = 0; i < 10; i++) {
                wheel1average += wheel1rates[i];
                wheel2average += wheel2rates[i];
                wheel3average += wheel3rates[i];
                wheel4average += wheel4rates[i];
                }
                wheel1average /= 10;    // Divide by 10 to get the average
                wheel2average /= 10;
                wheel3average /= 10;
                wheel4average /= 10;
                
                /* 
                Assumed that,
                    wheel1 - front left
                    wheel2 - front right
                    wheel3 - rear left
                    wheel4 - rear right
                */
               
                // Compare the averages of inside wheels and outside wheels
                // Inside wheels: wheel1 and wheel3
                if ( ( abs(wheel1average - wheel3average) / std::min(wheel1average,wheel3average) ) > threshold) {
                    std::cout << "! Slip detected on inside wheels. \n\t- Wheel 1 average: " << wheel1average << "\n\t- Wheel 3 average: " << wheel3average << std::endl;
                }
                if ( ( abs(wheel2average - wheel4average) / std::min(wheel2average,wheel4average) ) > threshold) {
                    std::cout << "! Slip detected on outside wheels. \n\t- Wheel 2 average: " << wheel2average << "\n\t- Wheel 4 average: " << wheel4average << std::endl;
                }
        } else {
            std::cout << "Initializing... : Waiting for the arrays to be filled with values." << std::endl;
        }

        // Write the comma-separated values to the output file
        outputFile << wheel1average << "," << wheel2average << "," << wheel3average << "," << wheel4average << std::endl;

        

        frame++;
    }

    // Close the output file
    outputFile.close();
    
    return 0;
}
