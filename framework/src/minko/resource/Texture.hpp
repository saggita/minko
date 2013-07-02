/*
Copyright (c) 2013 Aerys

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

#include "minko/Common.hpp"

namespace minko
{
	namespace resource
	{
		class Texture
		{
		public:
			typedef std::shared_ptr<Texture> Ptr;

			enum DataFormat
			{
				RGB,
				RGBA
			};

		private:
			std::shared_ptr<render::AbstractContext>	_context;
			const unsigned int							_width;
			const unsigned int							_height;
			std::vector<char>							_data;
			int											_texture;

		public:
			inline static
			Ptr
			create(std::shared_ptr<render::AbstractContext> context,
				   const unsigned int						width,
				   const unsigned int						height)
			{
				return std::shared_ptr<Texture>(new Texture(context, width, height));
			}

			inline static
			Ptr
			create(std::shared_ptr<render::AbstractContext> context,
				   const unsigned int						width,
				   const unsigned int						height,
				   char*									data,
				   DataFormat								format = DataFormat::RGBA)
			{
				auto texture = std::shared_ptr<Texture>(new Texture(context, width, height));

				texture->data(data, format);
				texture->upload();

				return texture;
			}

			inline
			std::shared_ptr<render::AbstractContext>
			context()
			{
				return _context;
			}

			inline
			const unsigned int
			width()
			{
				return _width;
			}

			inline
			const unsigned int
			height()
			{
				return _height;
			}

			void
			data(char* data, DataFormat format = DataFormat::RGBA);

			void
			upload();

		private:
			Texture(std::shared_ptr<render::AbstractContext>	context,
					const unsigned int							width,
					const unsigned int							height);
		};
	}
}
