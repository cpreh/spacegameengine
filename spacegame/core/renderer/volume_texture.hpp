#ifndef SGE_VOLUME_TEXTURE_HPP_INCLUDED
#define SGE_VOLUME_TEXTURE_HPP_INCLUDED

#include "../math/box.hpp"
#include "./texture_base.hpp"

namespace sge
{
	typedef box<texture_base::size_type> lock_box;

	template<typename BitDepth>
	class basic_volume_texture : public basic_texture_base<BitDepth32> {
	public:
		typedef basic_texture_base<BitDepth32> base;
		typedef typename base::size_type size_type;
		typedef typename base::const_pointer const_pointer;
		virtual size_type get_width() const = 0;
		virtual size_type get_height() const = 0;
		virtual size_type get_depth() const = 0;
		virtual void set_data(const_pointer p, const lock_box* b = 0) = 0;
	};
	typedef basic_volume_texture<BitDepth32> volume_texture;
	typedef shared_ptr<volume_texture> volume_texture_ptr;
}

#endif
