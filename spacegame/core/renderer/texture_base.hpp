#ifndef SGE_TEXTURE_BASE_HPP_INCLUDED
#define SGE_TEXTURE_BASE_HPP_INCLUDED

#include <cstddef>
#include "../main/shared_ptr.hpp"
#include "../math/rect.hpp"
#include "./renderer_types.hpp"
#include "../main/types.hpp"

namespace sge
{
	template<unsigned Depth> struct BitDepth;
	template<> struct BitDepth<16> { typedef int16 color; };
	template<> struct BitDepth<32> { typedef sge::color color; };
	typedef BitDepth<16> BitDepth16;
	typedef BitDepth<32> BitDepth32;
	
	template<typename BitDepth>
	class basic_texture_base {
	public:
		typedef std::size_t              size_type;
		typedef std::ptrdiff_t           difference_type;
		typedef typename BitDepth::color value_type;
		typedef value_type*              pointer;
		typedef const value_type*        const_pointer;
		virtual ~basic_texture_base() {}
		virtual size_type size() const = 0;
		virtual resource_flag_t flags() const = 0;
	};
	typedef basic_texture_base<BitDepth32> texture_base;
	typedef shared_ptr<texture_base> texture_base_ptr;
	typedef basic_rect<texture_base::size_type> lock_rect;
}

#endif
