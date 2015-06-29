/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once
#include <iostream>

/**
 * nodeData
 *
 * Class implementing the data for a node in Threaded Binary Search Tree.
 */
class nodeData
{
public:
    nodeData();
    nodeData(const nodeData& source);
    nodeData(const std::string& token);
    ~nodeData();

    // Properties
    bool isValid() const;
    int getFrequency() const;
    std::string getToken() const;

    // Operations
    void increaseFrequency();
    void setToken(const std::string& token);

    // Comparison
    int compare(const std::string& token) const;

    // Operators
    bool operator==(const std::string& token) const;
    bool operator!=(const std::string& token) const;
    bool operator<(const std::string& token) const;
    bool operator>(const std::string& token) const;

    // Display/Log methods
    void show(std::ostream& output, bool details) const;

private:
    int tokenFrequency;     // token frequency
    std::string tokenData;  // token data
};
