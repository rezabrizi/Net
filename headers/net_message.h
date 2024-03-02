
#pragma once

#include "net_common.h"

namespace net
{

    template <typename T>
    struct message_header
    {
        T id{};
        uint32_t size = 0;
    };

    template <typename T>
    struct message
    {

        message_header<T> header{};
        std::vector<uint8_t> body;

        size_t size() const
        {
            return body.size();
        }


        friend std::ostream& operator << (std::ostream& os, const message<T>& msg)
        {
            os << "ID: " << int(msg.header.id) << msg.header.size;
            return os;
        }

        template<typename DataType>
        friend message<T>& operator << (message<T>& msg, const DataType& data)
        {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into the vector");

            size_t i = msg.body.size();

            msg.body.resize(i + sizeof (DataType));

            std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

            msg.header.size = msg.size();

            return msg;
        }

        template<typename DataType>
        friend message<T>& operator >> (message& msg, DataType& data)
        {

            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into the vector");

            size_t i = msg.body.size() - sizeof(DataType);

            std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

            msg.body.resize(i);

            msg.header.size = msg.size();

            return msg;
        }

        friend message<T>& operator << (message<T>& msg, const std::string& data)
        {

            size_t length = data.size();

            size_t new_body_size = msg.body.size() + length;

            msg.body.resize(new_body_size);

            std::copy(data.begin(), data.end(), msg.body.end() - length);

            msg.header.size = msg.size();

            msg << length;

            return msg;
        }

        friend message<T>& operator >> (message<T>& msg, std::string& data)
        {
            size_t length;

            msg >> length;

            data.clear();

            data.reserve(length);

            for (size_t i =0; i < length; i++)
            {
                char c = static_cast<char>(msg.body[msg.body.size() - length + i]);
                data += c;
            }

            msg.body.resize(msg.body.size() - length);

            msg.header.size = msg.size();

            return msg;
        }
    };

    template<typename T>
    class connection;

    template <typename T>
    struct owned_message
    {
        std::shared_ptr<connection<T>> remote = nullptr;
        message<T> msg;

        friend std::ostream& operator<< (std::ostream& os, const owned_message<T>& msg)
        {
            os << msg.msg;
            return os;
        }
    };
}
