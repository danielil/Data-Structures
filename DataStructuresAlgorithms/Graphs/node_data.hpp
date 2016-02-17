/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include <string>

namespace dsa
{
    class NodeData
    {
        friend std::ostream & operator<<( std::ostream &, const NodeData &);

    public:
        NodeData();                    // default constructor, data is set to an empty string
        ~NodeData();

        NodeData(const std::string &);      // data is set equal to parameter
        NodeData(const NodeData &);    // copy constructor
        NodeData& operator=(const NodeData &);

        // set class data from data file
        // returns true if the data is set, false when bad data, i.e., is eof
        bool setData( std::istream&);

        bool operator==(const NodeData &) const;
        bool operator!=(const NodeData &) const;
        bool operator<(const NodeData &) const;
        bool operator>(const NodeData &) const;
        bool operator<=(const NodeData &) const;
        bool operator>=(const NodeData &) const;

    private:
        std::string data;
    };
}
