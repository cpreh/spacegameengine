#ifndef SGE_RENDERER_TEXTURE_SOFTWARE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_SOFTWARE_HPP_INCLUDED

#include "texture.hpp"
#include "color_format.hpp"
#include "../raw_vector.hpp"
#include "../export.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <boost/scoped_ptr.hpp>

namespace sge
{
namespace renderer
{
class SGE_CLASS_SYMBOL texture_software : public texture
{
public:
	SGE_SYMBOL texture_software(dim_type const &,color_format::type);
	SGE_SYMBOL ~texture_software();
	SGE_SYMBOL dim_type const dim() const;
	SGE_SYMBOL image_view const lock(lock_rect const &,lock_flag_t);
	SGE_SYMBOL const_image_view const lock(lock_rect const &) const;
	SGE_SYMBOL void unlock() const;
	SGE_SYMBOL resource_flag_t flags() const;
private:
	typedef raw_vector<unsigned char> internal_vector;

	dim_type dim_;
	color_format::type cf;
	internal_vector raw_bytes;
	// has to be mutable for unlock
	mutable bool locked;
	
	internal_vector::size_type byte_count() const;
	void resize(dim_type const &);
};
}
}

#endif
