#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

class WheelController {
private:
    // Constants
    const double PI = 3.14159265358979323846;
    const double SLIPPING_THRESHOLD = 0.02;  // 2% threshold for detecting slipping

public:
    // Function to process encoder readings and detect abnormal behavior
    void processEncoderReadings(const std::string& filename) {
        // Read encoder readings from the provided file
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        // Process each line in the file
        std::string line;
        while (std::getline(file, line, '\n')) {
            // Parse the line into individual readings
            std::vector<int> readings = parseEncoderReadings(line);

            // Check for abnormal behavior in one wheel
            if (hasAbnormalBehavior(readings)) {
                // Compensate for slipping effect
                compensateSlipping(readings);

                // Print or log the corrected readings
                printReadings(readings);
            }
        }

        file.close();
    }

private:
    // Function to parse encoder readings from a comma-separated line
    std::vector<int> parseEncoderReadings(const std::string& line) {
        std::vector<int> readings;
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(',')) != std::string::npos) {
            token = line.substr(0, pos);
            readings.push_back(std::stoi(token));
            line.erase(0, pos + 1);
        }
        readings.push_back(std::stoi(line));
        return readings;
    }

    // Function to check for abnormal behavior in one wheel
    bool hasAbnormalBehavior(const std::vector<int>& readings) {
        // Compare encoder readings of the erroneous wheel and the parallel wheel
        int erroneousWheel = readings[2];  // Assuming the third wheel is the erroneous one
        int parallelWheel = readings[3];   // Parallel wheel to the erroneous one

        // Calculate the difference percentage
        double differencePercentage = std::abs((erroneousWheel - parallelWheel) / static_cast<double>(parallelWheel));

        // Check if the difference exceeds the threshold
        return (differencePercentage > SLIPPING_THRESHOLD);
    }

    // Function to compensate for slipping effect
    void compensateSlipping(std::vector<int>& readings) {
        // Assuming slipping only affects one wheel, adjust the erroneous wheel's reading
        // You can implement a more sophisticated slipping compensation algorithm here
        readings[2] = readings[3];  // Set the erroneous wheel's reading to match the parallel wheel
    }

    // Function to print or log the corrected encoder readings
    void printReadings(const std::vector<int>& readings) {
        std::cout << "Corrected Encoder Readings: ";
        for (int reading : readings) {
            std::cout << reading << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    WheelController controller;

    // Replace 'sample_readings.csv' with the actual filename provided
    controller.processEncoderReadings("sample_readings.csv");

    return 0;
}
