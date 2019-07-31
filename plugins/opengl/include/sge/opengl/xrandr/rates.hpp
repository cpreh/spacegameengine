//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_RATES_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_RATES_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/rates_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class rates
{
public:
	rates(
		sge::opengl::xrandr::configuration const &,
		sge::opengl::xrandr::mode_index
	);

	typedef
	short const *
	iterator;

	typedef
	iterator
	const_iterator;

	iterator
	begin() const;

	iterator
	end() const;

	typedef
	unsigned
	size_type;

	size_type
	size() const;
private:
	int size_;

	short const *rates_;
};

}
}
}

#endif
