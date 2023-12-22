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
    float tire1rates[10] = {0};
    std::cout << "Tire 1 rates: " << tire1rates[0] << std::endl;
    std::cout << "Tire 1 rates: " << tire1rates[9] << std::endl;

    tire1rates[9] = 1.0;
    std::cout << "Tire 1 rates: " << tire1rates[9] << std::endl;

    std::ifstream file("readings.csv");
    std::string line;       // A line in the file

    if (!getline(file, line)) {
        std::cerr << "Error reading the file or file is empty." << std::endl;
        return 1;  // Exit with an error code
    }

    while (getline(file, line))
    {
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

    }
    
    return 0;
}
