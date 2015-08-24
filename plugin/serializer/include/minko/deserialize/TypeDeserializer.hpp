/*
Copyright (c) 2014 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "minko/SerializerCommon.hpp"

namespace minko
{
    namespace deserialize
    {
        class TypeDeserializer
        {
        private:

            template <typename T, typename ST = T>
            static void
            read(std::stringstream& stream, T& value)
            {
                stream.read(reinterpret_cast<char*>(&value), sizeof (ST));
            }

        public:
            static
            float
            deserializeFloat(const std::string& serializedValue)
            {
                return deserializeVector<float>(serializedValue)[0];
            }

            template <typename T, typename ST = T>
            static
            std::vector<T>
            deserializeVector(const std::string& serializedValue)
            {
                std::stringstream   stream;
                std::vector<T>      result(serializedValue.size() / sizeof(ST));
                uint                i = 0;

                stream << serializedValue;

                while (i < result.size())
                    read<T, ST>(stream, result[i++]);

                return result;
            }

            static
            Any
            deserializeVector4(const std::tuple<uint, std::string&>& serializedVector);

            static
            Any
            deserializeVector3(const std::tuple<uint, std::string&>& serializedVector);

            static
            Any
            deserializeVector2(const std::tuple<uint, std::string&>& serializedVector);

            static
            Any
            deserializeMatrix4x4(const std::tuple<uint, std::string&>& serializedMatrix);

            static
            Any
            deserializeBlending(const std::tuple<uint, std::string&>& seriliazedBlending);

            static
            Any
            deserializeTriangleCulling(const std::tuple<uint, std::string&>& seriliazedTriangleCulling);

            static
            Any
            deserializeTextureId(const std::tuple<uint, std::string&>& seriliazedTextureId);

            static
            Any
            deserializeString(const std::tuple<uint, std::string&>& serialized);
        };
    }
}
