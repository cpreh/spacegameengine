#include <sge/gui/image.hpp>
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

sge::gui::image::impl_type &sge::gui::image::impl()
{
	return impl_;
}

sge::gui::image::impl_type const &sge::gui::image::impl() const
{
	return impl_;
}

sge::gui::dim const sge::gui::image::size() const
{
	return 
		dim(
			static_cast<unit>(
				impl().width()),
			static_cast<unit>(
				impl().height()));
}

sge::gui::image_view const sge::gui::image::view()
{
	return 
		boost::gil::view(
			impl());
}

sge::gui::const_image_view const sge::gui::image::const_view() const
{
	return 
		boost::gil::const_view(
			impl());
}

void sge::gui::image::resize(
	dim const &d)
{
	impl().recreate(
		static_cast<impl_type::coord_t>(
			d.w())
		static_cast<impl_type::coord_t>(
			d.h()));
}
