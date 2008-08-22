#ifndef SGE_RENDERER_TEXTURE_SOFTWARE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_SOFTWARE_HPP_INCLUDED

#include "texture.hpp"
#include "color_format.hpp"
#include "../raw_vector.hpp"
#include <boost/scoped_ptr.hpp>

namespace sge
{
namespace renderer
{
class texture_software : public texture
{
public:
	texture_software(dim_type const &,color_format::type);
	dim_type const dim() const { return dim_; }
	image_view const lock(lock_rect const &,lock_flag_t);
	const_image_view const lock(lock_rect const &) const;
	void unlock() const;
	resource_flag_t flags() const { return resource_flags::dynamic; }
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
