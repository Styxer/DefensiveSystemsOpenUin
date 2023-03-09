#pragma once

#include <array>
#include <string>

#include <boost/asio.hpp>
#pragma once

//knew about boost::serialization only AFTER i wrote these class
//Overload some operators în * std::istream and std::ostream .Namely, the <<= and >>= operators.

using boost::asio::ip::tcp;
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

template<typename T, size_t N>
 std::ostream& operator <<=(std::ostream& out, std::array<T, N> const& data) {
    out.write(reinterpret_cast<const char*>(data.data()), N * sizeof(T));
    return out;
}

template<typename T, size_t N>
 std::istream& operator >>=(std::istream& in, std::array<T, N>& data) {
    in.read(const_cast<char*>(reinterpret_cast<const char*>(data.data())), N * sizeof(T));
    return in;
}

template<typename T, size_t N>
 std::istream& operator >>(std::istream& in, std::array<T, N>& data) {
    size_t readSize = N * sizeof(T);

    if (in.flags() & std::ios_base::hex) {
        readSize *= 2;
    }
    in.getline(reinterpret_cast<char*>(data.data()), readSize);
    return in;
}

template<typename T, size_t N>
 std::ostream& operator <<(std::ostream& out, std::array<T, N> const& data) {
    for (T item : data) {
        out << item;
    }
    out << std::endl;
    return out;
}

inline std::ostream& operator <<=(std::ostream& out, std::string const& data) {
    out.write(data.c_str(), data.size());
    return out;
}

