#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "libs/rapidxml.hpp"
#include <fstream>
#include <vector>


std::string parseXML(const std::string& filename) {
    // Read the XML file into a vector
    std::ifstream file(filename);
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0'); // Null-terminate the buffer

    // Parse the buffer using the xml_document
    rapidxml::xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    // Find the nmaprun node
    rapidxml::xml_node<> *nmaprun_node = doc.first_node("nmaprun");
    if (nmaprun_node) {
        // Get the version attribute
        rapidxml::xml_attribute<> *version_attr = nmaprun_node->first_attribute("version");
        if (version_attr) {
            std::cout << "Nmap version: " << version_attr->value() << std::endl;
            return version_attr->value();
        } else {
            std::cout << "Version attribute not found." << std::endl;
            return "";
        }
    } else {
        std::cout << "Nmaprun node not found." << std::endl;
        return "";
    }
}


std::string executeNmap(const std::string& flags) {
    std::string tempFile = "nmap_output.txt";
    std::string command = "nmap " + flags + " > " + tempFile;

    // Print the command to be executed
    std::cout << "Executing command: " << command << std::endl;

    // Execute Nmap command
    int result = system(command.c_str());

    // Check for execution errors
    if (result != 0) {
        std::cerr << "Error: Nmap command failed to execute." << std::endl;
        return "";
    }

    // Read the output from the file
    std::ifstream file(tempFile);
    std::string output;
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            output += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return "";
    }

    // Optionally, remove the temporary file
    remove(tempFile.c_str());

    // Return the output
    return output;
}


int main(int argc, char* argv[]) {
    // Concatenate all command-line arguments into a single string for flags
    std::string flags;
    for (int i = 1; i < argc; ++i) {
        flags += argv[i];
        if (i < argc - 1) {
            flags += " ";// Add space between flags
        }
    }
    flags = flags + " -oX nmoutput.xml";

    // Execute Nmap with the concatenated flags
    std::string nmapOutput = executeNmap(flags);

    // Print the Nmap output
    std::cout << "Nmap Output:\n" << nmapOutput;
    // generic loading output
    std::cout << "searching";
    std::cout << "...";
    std::cout << "...";
    std::cout << "...\n\n";

    std::string tempFile2 = "searchsploitResults.txt";

    //parse xml for port version
    std::string port_version = parseXML("nmoutput.xml");
    std::cout << "parsing xml...\n";
    std::cout << port_version << "\n";
    std::string searchSearchsploit = "searchsploit -m " + port_version;
    system(searchSearchsploit.c_str());

    // search searchsploit
    // Read the output from the file
    std::ifstream file(tempFile2);
    std::string output;
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            output += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return -1;
    }
    return 0;
}