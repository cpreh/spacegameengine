//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_EXTENSION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_EXTENSION_HPP_INCLUDED

#include <sge/opengl/xrandr/extension_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class extension
{
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		event_base_type
	);

	explicit
	extension(
		event_base_type
	);

	[[nodiscard]]
	event_base_type
	event_base() const;
private:
	event_base_type event_base_;
};

}
}
}

#endif
