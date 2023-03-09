#include <string>
#include <boost/crc.hpp>

uint32_t crc32_buf(const std::string& my_string) {
    boost::crc_32_type result;
    result.process_bytes(my_string.data(), my_string.length());
    return result.checksum();
}
