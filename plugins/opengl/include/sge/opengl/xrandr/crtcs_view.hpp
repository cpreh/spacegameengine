//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_CRTCS_VIEW_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_CRTCS_VIEW_HPP_INCLUDED

#include <sge/opengl/xrandr/screen_resources_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class crtcs_view
{
public:
	explicit
	crtcs_view(
		sge::opengl::xrandr::screen_resources const &
	);

	typedef
	RRCrtc const *
	const_iterator;

	const_iterator
	begin() const;

	const_iterator
	end() const;
private:
	fcppt::reference<
		sge::opengl::xrandr::screen_resources const
	> resources_;
};

}
}
}

#endif
