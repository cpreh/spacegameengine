#include "canvas/log.hpp"
#include <sge/gui/canvas.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/log.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/text.hpp>
#include <boost/gil/image.hpp>

sge::gui::canvas::object::object(image &texture_)
	: texture_(texture_),
	  view_(boost::gil::view(texture_))
{
}

sge::gui::canvas::object::~object()
{}

sge::gui::dim const sge::gui::canvas::object::size() const
{
	return dim(
		static_cast<unit>(texture_.width()),
		static_cast<unit>(texture_.height()));
}

sge::gui::rect const sge::gui::canvas::object::area() const
{
	return rect(
		point::null(),
		size());
}

sge::gui::image_view &sge::gui::canvas::object::view()
{
	return view_;
}

sge::gui::const_image_view const
sge::gui::canvas::object::view() const
{
	return renderer::make_const_image_view(view_);
}
