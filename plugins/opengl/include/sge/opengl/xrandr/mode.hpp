//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_MODE_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_MODE_HPP_INCLUDED

#include <sge/opengl/xrandr/mode_fwd.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/rotation.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class mode
{
public:
	mode(
		sge::opengl::xrandr::mode_index,
		sge::opengl::xrandr::rotation,
		sge::opengl::xrandr::refresh_rate
	);

	sge::opengl::xrandr::mode_index
	index() const;

	sge::opengl::xrandr::rotation
	rotation() const;

	sge::opengl::xrandr::refresh_rate
	rate() const;
private:
	sge::opengl::xrandr::mode_index index_;

	sge::opengl::xrandr::rotation rotation_;

	sge::opengl::xrandr::refresh_rate rate_;
};

}
}
}

#endif
