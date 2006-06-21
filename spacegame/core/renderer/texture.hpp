#ifndef SGE_TEXTURE_HPP_INCLUDED
#define SGE_TEXTURE_HPP_INCLUDED

#include "./texture_base.hpp"

namespace sge
{
	template<typename BitDepth>
	class basic_texture : public basic_texture_base<BitDepth> {
	public:
		typedef basic_texture_base<BitDepth> base;
		typedef typename base::size_type size_type;
		typedef typename base::const_pointer const_pointer;
		virtual size_type width() const = 0;
		virtual size_type height() const = 0;
		virtual void set_data(const_pointer p, const lock_rect* r = 0) = 0;
	};
	typedef basic_texture<BitDepth32> texture;
	typedef shared_ptr<texture> texture_ptr;
}

#endif
