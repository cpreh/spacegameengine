//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_SIZES_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SIZES_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/sizes_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class sizes
{
public:
	explicit
	sizes(
		sge::opengl::xrandr::configuration const &
	);

	typedef
	XRRScreenSize const *
	iterator;

	typedef
	iterator
	const_iterator;

	iterator
	begin() const;

	iterator
	end() const;

	XRRScreenSize const &
	operator[](
		sge::opengl::xrandr::mode_index
	) const;

	sge::opengl::xrandr::mode_index
	size() const;
private:
	int size_;

	XRRScreenSize const *sizes_;
};

}
}
}

#endif
