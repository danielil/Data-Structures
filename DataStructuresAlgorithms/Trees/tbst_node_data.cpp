/**
 * @author Daniel Sebastian Iliescu
 *
 * This file contains the methods for nodeData class
 * that implements the data for a node in the TBST.
 */

#include "node.hpp"

#include <iostream>

namespace dsa
{
    /**
     * nodeData()
     *
     * Default constructor
     */
    nodeData::nodeData()
        : tokenFrequency(0)
    {
    }

    /**
     * nodeData(const nodeData& source)
     *
     * Copy constructor
     *
     * @param source Source data to copy.
     */
    nodeData::nodeData(const nodeData& source)
        : tokenFrequency(source.tokenFrequency),
        tokenData(source.tokenData)
    {
    }

    /**
     * nodeData(const string& token)
     *
     * Constructor
     *
     * @param token Input token to copy & store.
     */
    nodeData::nodeData(const std::string& token)
        : tokenFrequency(0)
    {
        setToken(token);
    }

    /**
     * ~nodeData()
     *
     * Destructor
     */
    nodeData::~nodeData()
    {
    }

    /**
     * isValid() const
     *
     * Method checking whether the current data is valid
     *
     * @pre None
     * @post Checks whether data is valid
     * @return True if data is valid; false otherwise
     */
    bool nodeData::isValid() const
    {
        return !tokenData.empty() && (tokenFrequency > 0);
    }

    /**
     * getFrequency() const
     *
     * Method retrieving the token frequency.
     *
     * @pre None
     * @post Returns the current token frequency
     * @return token frequency
     */
    int nodeData::getFrequency() const
    {
        return tokenFrequency;
    }

    /**
     * getToken() const
     *
     * Method retrieving the current token.
     *
     * @pre None
     * @post Returns the current token
     * @return token
     */
    std::string nodeData::getToken() const
    {
        return tokenData;
    }

    /**
     * incrementFrequency()
     *
     * Method incrementing the token frequency (if token is valid)
     *
     * @pre data token should be valid (i.e. not empty)
     * @post token frequency is incremented
     */
    void nodeData::increaseFrequency()
    {
        if (isValid())
        {
            tokenFrequency++;
        }
    }

    /**
     * setToken(const string& token)
     *
     * Method for setting the data token.
     *
     * @param token Input token to set.
     * @pre Input token is valid (i.e. not empty)
     * @post local token data and frequency are set.
     */
    void nodeData::setToken(const std::string& token)
    {
        if (!token.empty())
        {
            tokenData = token;
            tokenFrequency = 1;
        }
    }

    /**
     * compare(const string& token)
     *
     * Method comparing the local token with given input token.
     *
     * @param token Input token to compare against.
     * @pre both data token and input token are valid (i.e. not empty)
     * @post local data is compared against input data
     * @return Comparison result as follows:
     *      < 0 : local token < target data
     *        0 : local token < target data
     *      > 0 : local token < target data
     */
    int nodeData::compare(const std::string& token) const
    {
        return tokenData.compare(token);
    }

    /**
     * operator==(const string& token) const
     *
     * Equality operator
     *
     * @param target The token used as comparison target.
     * @pre Both local and traget data are valid (i.e. not empty).
     * @post The local data is compared against the target data.
     * @return True if the data are matching; false otherwise.
     */
    bool nodeData::operator==(const std::string& token) const
    {
        return (compare(token) == 0);
    }

    /**
     * operator!=(const string& token) const
     *
     * Inequality operator
     *
     * @param target The token used as comparison target.
     * @pre Both local and traget data are valid (i.e. not empty).
     * @post The local data is compared against the target data.
     * @return False if the data are matching; true otherwise.
     */
    bool nodeData::operator!=(const std::string& token) const
    {
        return (compare(token) != 0);
    }

    /**
     * operator<(const string& token) const
     *
     * Less than operator
     *
     * @param target The token used as comparison target.
     * @pre Both local and traget data are valid (i.e. not empty).
     * @post The local data is compared against the target data.
     * @return True if the target data is less than local data;
     * false otherwise.
     */
    bool nodeData::operator<(const std::string& token) const
    {
        return (compare(token) < 0);
    }

    /**
     * operator>(const string& token) const
     *
     * Greater than operator
     *
     * @param target The token used as comparison target.
     * @pre Both local and traget data are valid (i.e. not empty).
     * @post The local data is compared against the target data.
     * @return True if the target data is greater than local data;
     * false otherwise.
     */
    bool nodeData::operator>(const std::string& token) const
    {
        return (compare(token) > 0);
    }

    /**
     * show(ostream& output, bool details) const
     *
     * Helper method for pushing the node data information into an output stream.
     *
     * @param output Output stream
     * @param details Whether to display extended info
     * @pre None
     * @post data is pushed into the stream.
     */
    void nodeData::show( std::ostream& output, bool details) const
    {
        if (details)
        {
            output << "Token: " << tokenData.c_str();
            output << ", Frequency: " << tokenFrequency;
        }
        else
        {
            output << tokenData.c_str();
            output << "[" << tokenFrequency << "]";
        }
    }
}
