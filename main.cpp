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

    // Arrays to store the rates of each wheel
    float wheel1rates[10] = {0};
    float wheel2rates[10] = {0};
    float wheel3rates[10] = {0};
    float wheel4rates[10] = {0};
    // Pointer to the current index of the arrays
    int pointer = 0;

    // Variables to store the rate of each wheel with respect to current frame
    float wheel1rate = 0;
    float wheel2rate = 0;
    float wheel3rate = 0;
    float wheel4rate = 0;

    // Averages of each wheel
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

        // Calculate the rate of each wheel with respect to current frame
        wheel1rate = tire1Rotation / time;
        wheel2rate = tire2Rotation / time;
        wheel3rate = tire3Rotation / time;
        wheel4rate = tire4Rotation / time;

        // Update the arrays with the value related to current readings
        wheel1rates[pointer] = wheel1rate;
        wheel2rates[pointer] = wheel2rate;
        wheel3rates[pointer] = wheel3rate;
        wheel4rates[pointer] = wheel4rate;

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
                // Compensated instentanius values are stored in wheel1rate, wheel2rate, wheel3rate, wheel4rate. But the values related to original readings are stored in arrays. Therefore, when we compare the averages of the wheels, getting values from the arrays makes no error after compensation.
                
                // Inside wheels: wheel1 and wheel3
                if ( ( abs(wheel1average - wheel3average) / std::min(wheel1average,wheel3average) ) > threshold) {
                    std::cout << "! Slip detected on inside wheels. \n\t- Wheel 1 average: " << wheel1average << "\n\t- Wheel 3 average: " << wheel3average << std::endl;

                    // Compensate for slipping effect 
                    // Assuming slipping only affects one wheel, adjust the erroneous wheel's reading
                    // To eleminate the slipping, errorneous wheel's reading is set to the reading of the other wheel
                    if (wheel1rate > wheel3rate) {
                        wheel1rate = wheel3rate;
                    } else {
                        wheel3rate = wheel1rate;
                    }
                }
                if ( ( abs(wheel2average - wheel4average) / std::min(wheel2average,wheel4average) ) > threshold) {
                    std::cout << "! Slip detected on outside wheels. \n\t- Wheel 2 average: " << wheel2average << "\n\t- Wheel 4 average: " << wheel4average << std::endl;

                    // Compensate for slipping effect 
                    // Assuming slipping only affects one wheel, adjust the erroneous wheel's reading
                    // To eleminate the slipping, errorneous wheel's reading is set to the reading of the other wheel
                    if (wheel2rate > wheel4rate) {
                        wheel2rate = wheel4rate;
                    } else {
                        wheel4rate = wheel2rate;
                    }
                }
        } else {
            std::cout << "Initializing... : Waiting for the arrays to be filled with values." << std::endl;
        }

        // Write the comma-separated values to the output file
        outputFile << wheel1rate << "," << wheel2rate << "," << wheel3rate << "," << wheel4rate << std::endl;

        frame++;
    }

    // Close the output file
    outputFile.close();
    
    return 0;
}
