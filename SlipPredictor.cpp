#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class SlipPredictor {
public:
    void calculateTireVelocities(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << filePath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::vector<double> tireSpeeds = parseCSVLine(line);
            if (tireSpeeds.size() != 4) {
                std::cout << "Invalid data format: " << line << std::endl;
                continue;
            }

            double velocity = calculateVelocity(tireSpeeds);
            std::cout << "Tire velocities: ";
            for (double speed : tireSpeeds) {
                std::cout << speed << " ";
            }
            std::cout << "=> Velocity: " << velocity << std::endl;
        }

        file.close();
    }

private:
    std::vector<double> parseCSVLine(const std::string& line) {
        std::vector<double> values;
        std::stringstream ss(line);
        std::string value;
        while (std::getline(ss, value, ',')) {
            values.push_back(std::stod(value));
        }
        return values;
    }

    double calculateVelocity(const std::vector<double>& tireSpeeds) {
        double sum = 0.0;
        for (double speed : tireSpeeds) {
            sum += speed;
        }
        return sum / tireSpeeds.size();
    }
};

int main() {
    SlipPredictor predictor;
    predictor.calculateTireVelocities("data.csv");

    return 0;
}
