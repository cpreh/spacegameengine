//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SYSTEM_HPP_INCLUDED

#include <sge/opengl/xrandr/extension.hpp>
#include <sge/opengl/xrandr/state_unique_ptr.hpp>
#include <sge/opengl/xrandr/system_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class system
{
	FCPPT_NONMOVABLE(
		system
	);
public:
	explicit
	system(
		sge::opengl::xrandr::extension const &
	);

	~system(); // NOLINT(performance-trivially-destructible)

	[[nodiscard]]
	sge::opengl::xrandr::state_unique_ptr
	create_state(
		sge::window::object_ref
	);
private:
	sge::opengl::xrandr::extension const extension_;
};

}
}
}

#endif
