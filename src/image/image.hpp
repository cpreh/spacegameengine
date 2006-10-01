#ifndef SGE_IMAGE_HPP_INCLUDED
#define SGE_IMAGE_HPP_INCLUDED

#include <boost/utility.hpp>
#include "../shared_ptr.hpp"
#include "../renderer/renderer_types.hpp"

namespace sge
{
	class image : boost::noncopyable {
	public:
		typedef unsigned size_type;
		typedef color value_type;
		typedef color* pointer;
		typedef const color* const_pointer;
		virtual const_pointer data() const = 0;
		virtual size_type width() const = 0;
		virtual size_type height() const = 0;
		virtual void resize(size_type width, size_type height) = 0;
		virtual ~image(){}
	};
	typedef shared_ptr<image> image_ptr;

}

#endif
