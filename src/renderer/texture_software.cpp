#include <sge/renderer/texture_software.hpp>
#include <sge/renderer/color_format_stride.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/make_image_view.hpp>
#include <sge/renderer/image_view_factory.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/assert.hpp>
#include <sge/iostream.hpp>

// utility functions
sge::renderer::texture_software::internal_vector::size_type sge::renderer::texture_software::byte_count() const
{
	return static_cast<internal_vector::size_type>(
				dim().w()*dim().h()*renderer::color_format_stride(cf));
}

void sge::renderer::texture_software::resize(dim_type const &new_dim)
{
	dim_ = new_dim;
	raw_bytes.resize(byte_count());
}

sge::renderer::texture_software::texture_software(dim_type const &new_dim,color_format::type const cf)
	: cf(cf),locked(false)
{
	resize(new_dim);
}

sge::renderer::image_view const sge::renderer::texture_software::lock(lock_rect const &lr,lock_flag_t const)
{
	SGE_ASSERT_MESSAGE(!locked,SGE_TEXT("already locked software texture"));
	locked = true;
	return subimage_view(make_image_view(&raw_bytes[0],dim(),cf),lr);
}

sge::renderer::const_image_view const sge::renderer::texture_software::lock(lock_rect const &lr) const
{
	return subimage_view(make_image_view(&raw_bytes[0],dim(),cf),lr);
}

void sge::renderer::texture_software::unlock() const
{
	SGE_ASSERT_MESSAGE(
		locked,
		SGE_TEXT("software texture was not locked, though you tried to unlock"));

	locked = false;
}
