#include <sge/gui/image.hpp>
#include <sge/gui/image_view.hpp>
#include <boost/gil/image.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/gui/unit.hpp>

sge::gui::image::image()
: 
	impl_()
{
}

sge::gui::image::image(
	dim const &d)
: 
	impl_(
		static_cast<impl_type::coord_t>(d.w()),
		static_cast<impl_type::coord_t>(d.h()))
{
}

sge::gui::dim const sge::gui::image::size() const
{
	return 
		dim(
			static_cast<unit>(
				impl_.width()),
			static_cast<unit>(
				impl_.height()));
}

sge::gui::image_view sge::gui::image::view()
{
	return image_view(
		impl_);
}

sge::gui::const_image_view const sge::gui::image::const_view() const
{
	return const_image_view(
		impl_);
}

void sge::gui::image::resize(
	dim const &d)
{
	impl_.recreate(
		static_cast<impl_type::coord_t>(
			d.w()),
		static_cast<impl_type::coord_t>(
			d.h()));
}
