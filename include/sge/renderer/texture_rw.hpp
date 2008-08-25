#ifndef SGE_RENDERER_TEXTURE_RW_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_RW_HPP_INCLUDED

#include "texture.hpp"
#include "../export.hpp"
#include <boost/optional.hpp>
#include <boost/scoped_ptr.hpp>

namespace sge
{
namespace renderer
{
class SGE_CLASS_SYMBOL texture_rw : public texture
{
	public:
	SGE_SYMBOL texture_rw(texture_ptr read,texture_ptr write);
	SGE_SYMBOL dim_type const dim() const;
	SGE_SYMBOL image_view const lock(lock_rect const &, lock_flag_t);
	SGE_SYMBOL const_image_view const lock(lock_rect const &) const;
	SGE_SYMBOL void unlock() const;
	resource_flag_t flags() const { return resource_flags::dynamic; }
	private:
	mutable texture_ptr read,write;

	struct lock_data
	{
		lock_rect area;
		boost::optional<image_view> view;

		lock_data(lock_rect const &area,boost::optional<image_view> const view = boost::none)
			: area(area),view(view) {}
	};

	mutable boost::scoped_ptr<lock_data> locked;
};
}
}

#endif
