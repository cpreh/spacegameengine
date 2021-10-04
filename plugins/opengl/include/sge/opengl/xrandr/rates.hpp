//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_RATES_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_RATES_HPP_INCLUDED

#include <sge/opengl/xrandr/const_configuration_ref.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/rates_fwd.hpp>
#include <sge/opengl/xrandr/refresh_rate_type.hpp>


namespace sge::opengl::xrandr
{

class rates
{
public:
	rates(
		sge::opengl::xrandr::const_configuration_ref,
		sge::opengl::xrandr::mode_index
	);

	using
	int_type
	=
	sge::opengl::xrandr::refresh_rate_type;

	using
	iterator
	=
	int_type const *;

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

	using
	size_type
	=
	unsigned;

	[[nodiscard]]
	size_type
	size() const;
private:
	int size_;

	int_type const *rates_;
};

}

#endif
