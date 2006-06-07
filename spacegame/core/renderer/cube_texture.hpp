#ifndef SGE_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_CUBE_TEXTURE_HPP_INCLUDED

#include "./texture_base.hpp"
#include <boost/array.hpp>

namespace sge
{
	enum cube_side {
		CS_Front,
		CS_Back,
		CS_Left,
		CS_Right,
		CS_Top,
		CS_Bottom
	};

	template<typename BitDepth>
	class basic_cube_texture : public basic_texture_base<BitDepth> {
	public:
		typedef basic_texture_base<BitDepth> base;
		typedef typename base::const_pointer const_pointer;
		virtual void set_data(cube_side side, const_pointer p, const lock_rect* r = 0) = 0;
	};
	typedef basic_cube_texture<BitDepth32> cube_texture;
	typedef shared_ptr<cube_texture> cube_texture_ptr;
	typedef boost::array<cube_texture::const_pointer,6> cube_side_src_array;
}

#endif
