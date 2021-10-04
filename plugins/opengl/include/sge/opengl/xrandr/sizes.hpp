//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_SIZES_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SIZES_HPP_INCLUDED

#include <sge/opengl/xrandr/const_configuration_ref.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/sizes_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::xrandr
{

class sizes
{
public:
	explicit
	sizes(
		sge::opengl::xrandr::const_configuration_ref
	);

	using
	iterator
	=
	XRRScreenSize const *;

	using
	const_iterator
	=
	iterator;

	[[nodiscard]]
	iterator
	begin() const;

	[[nodiscard]]
	iterator
	end() const;

	[[nodiscard]]
	XRRScreenSize const &
	operator[](
		sge::opengl::xrandr::mode_index
	) const;

	[[nodiscard]]
	sge::opengl::xrandr::mode_index
	size() const;
private:
	int size_;

	XRRScreenSize const *sizes_;
};

}

#endif
