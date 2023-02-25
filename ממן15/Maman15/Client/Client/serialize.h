#pragma once
#include <sstream>
#include <array>
#include <string>
#include <memory>

#include <boost/asio.hpp>

#include "Request.h"

#pragma once


using namespace boost;

template<typename T>
 std::ostream& operator <<=(std::ostream& out, T const& data) {
    out.write(reinterpret_cast<const char*>(&data), sizeof(T));
    return out;
}

template<typename T>
 std::istream& operator >>=(std::istream& in, T& data) {
    in.read(reinterpret_cast<char*>(&data), sizeof(T));
    return in;
}

template<typename A, size_t N>
 std::ostream& operator <<=(std::ostream& out, std::array<A, N> const& data) {
    out.write(reinterpret_cast<const char*>(data.data()), N * sizeof(A));
    return out;
}

template<typename A, size_t N>
 std::istream& operator >>=(std::istream& in, std::array<A, N>& data) {
    in.read(const_cast<char*>(reinterpret_cast<const char*>(data.data())), N * sizeof(A));
    return in;
}

template<typename A, size_t N>
 std::istream& operator >>(std::istream& in, std::array<A, N>& data) {
    size_t read_size = N * sizeof(A);

    if (in.flags() & std::ios_base::hex) {
        read_size *= 2;
    }
    in.getline(reinterpret_cast<char*>(data.data()), read_size);
    return in;
}

template<typename A, size_t N>
 std::ostream& operator <<(std::ostream& out, std::array<A, N> const& data) {
    for (A item : data) {
        out << item;
    }
    out << std::endl;
    return out;
}

inline std::ostream& operator<<=(std::ostream& out, std::string const& data) {
    out.write(data.c_str(), data.size());
    return out;
}
