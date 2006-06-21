#ifndef SGE_RENDER_TARGET_HPP_INCLUDED
#define SGE_RENDER_TARGET_HPP_INCLUDED

#include "../main/shared_ptr.hpp"
#include "./texture.hpp"

namespace sge
{
	template<typename BitDepth>
	class basic_render_target : public basic_texture_base<BitDepth> {
	public:
		typedef basic_texture_base<BitDepth> base;
		typedef typename base::size_type size_type;
		virtual size_type width() const = 0;
		virtual size_type height() const = 0;
		virtual size_type size() const = 0;
	};
	typedef basic_render_target<BitDepth32> render_target;
	typedef shared_ptr<render_target> render_target_ptr;
}

#endif
