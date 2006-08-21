#ifndef SGE_TEXTURE_HELPER_HPP_INCLUDED
#define SGE_TEXTURE_HELPER_HPP_INCLUDED

#include "../main/types.hpp"
#include "../main/shared_ptr.hpp"
#include "../math/rect.hpp"
#include "../renderer/texture.hpp"

namespace sge
{

template<typename Texture> basic_rect<space_unit> to_coordinate_rect(const lock_rect& r, const shared_ptr<Texture> tex)
{
	return basic_rect<space_unit>(space_unit(r.left) / tex->width(), space_unit(r.top) / tex->height(),
	                              space_unit(r.right) / tex->width(), space_unit(r.bottom) / tex->height());
}

}

#endif
