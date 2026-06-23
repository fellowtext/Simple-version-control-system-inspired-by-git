#include <iostream>
#include <string>
#include <vector>
#include <sstream> // Required for parsing input lines
#include "file_system.hpp"


int main() {
    file_system Engine;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "exit") {
            break;
        } else if (command == "CREATE" || command == "READ" || command == "HISTORY") {
            std::string filename, extra;
            if (!(ss >> filename)) {
                std::cout << "Error: Filename is missing for " << command << " command." << std::endl;
                continue;
            }
            // YOUR FIRST RULE: Check for extra words
            if (ss >> extra) {
                std::cout << "Warning: Filename contains extra words. Using first word '" << filename << "'." << std::endl;
            }

            if (command == "CREATE") Engine.handle_create(filename);
            else if (command == "READ") Engine.handle_read(filename);
            else Engine.handle_history(filename);

        } else if (command == "INSERT" || command == "UPDATE" || command == "SNAPSHOT") {
            std::string filename, argument;
            if (!(ss >> filename)) {
                std::cout << "Error: Filename is missing for " << command << " command." << std::endl;
                continue;
            }
            std::getline(ss, argument);

            if (argument.empty()) {
                std::cout << "Error: Content or message is missing for " << command << " command." << std::endl;
                continue;
            }

            if (command == "INSERT") Engine.handle_insert(filename, argument);
            else if (command == "UPDATE") Engine.handle_update(filename, argument);
            else if (command == "SNAPSHOT") Engine.handle_snapshot(filename, argument);

        } else if (command == "ROLLBACK") {
            std::string filename, extra;
            if (!(ss >> filename)) {
                std::cout << "Error: Filename is missing for ROLLBACK command." << std::endl;
                continue;
            }
            int versionID;
            if (ss >> versionID) { // Check if an integer follows
                // YOUR SECOND RULE: Check for extra input after the ID
                if (ss >> extra) {
                    std::cout << "Error: Unexpected arguments provided for ROLLBACK command." << std::endl;
                    continue;
                }
                Engine.handle_rollback(filename, versionID);
            } else {
                Engine.handle_rollback(filename,-1);
            }
        } else if (command == "RECENT_FILES" || command == "BIGGEST_TREES") {
            int num = -1; // Use -1 to indicate no number was provided
            std::string extra;
            
            // Try to read a number. If it succeeds, check for extra input.
            if (ss >> num) {
                if (ss >> extra) {
                    std::cout << "Error: Unexpected arguments provided for " << command << " command." << std::endl;
                    continue;
                }
            } else { // No number was provided, check if there was other garbage text
                ss.clear(); // Clear the fail state from trying to read a number
                if (ss >> extra) {
                    std::cout << "Error: Invalid or unexpected arguments for " << command << " command." << std::endl;
                    continue;
                }
                 // A very large number to represent 'all' as per assignment, can be changed.
                num = 1; 
            }

            if (command == "RECENT_FILES") Engine.handle_recent_files(num);
            else Engine.handle_biggest_trees(num);
        
        } else {
            std::cout << "Error: Unknown command '" << command << "'" << std::endl;
        }
    }
    return 0;
}