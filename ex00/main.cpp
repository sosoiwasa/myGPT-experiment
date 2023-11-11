#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>

std::map<std::string, double> loadExchangeRates(const std::string& filename) {
    std::map<std::string, double> rates;
    std::ifstream file(filename.c_str());
    std::string line, date;
    double rate;

    if (!file) {
        std::cerr << "Error opening exchange rate file." << std::endl;
        return rates;
    }

    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        std::istringstream iss(line);
        getline(iss, date, ',');
        iss >> rate;
        rates[date] = rate;
    }

    return rates;
}

std::string findClosestDate(const std::map<std::string, double>& rates, const std::string& targetDate) {
    std::map<std::string, double>::const_iterator it = rates.begin();
    std::string closestDate = "";

    for (; it != rates.end(); ++it) {
        if (it->first > targetDate) {
            break;
        }
        closestDate = it->first;
    }

    return closestDate;
}

bool isValidDate(const std::string& date) {
    // Simple date format validation: YYYY-MM-DD
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    // Add more checks if needed
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::map<std::string, double> exchangeRates = loadExchangeRates("data.csv");

    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::string line, date;
    double value;
    getline(inFile, line); // Skip the header line

    while (getline(inFile, line)) {
        std::istringstream iss(line);
        getline(iss, date, '|');
        iss.ignore(1); // Ignore whitespace
        if (!(iss >> value)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        date.erase(date.find_last_not_of(" ") + 1); // Trim trailing whitespace

        if (!isValidDate(date) || value <= 0) {
            if (!isValidDate(date)) {
                std::cerr << "Error: bad input => " << line << std::endl;
            } else {
                std::cerr << "Error: not a positive number." << std::endl;
            }
            continue;
        }

        if (value > INT_MAX) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        std::string closestDate = findClosestDate(exchangeRates, date);
        if (!closestDate.empty()) {
            double rate = exchangeRates[closestDate];
            double calculatedValue = value * rate;
            std::cout << date << " => " << value << " = " << calculatedValue << std::endl;
        } else {
            std::cerr << "Error: no matching date found." << std::endl;
        }
    }

    return 0;
}
