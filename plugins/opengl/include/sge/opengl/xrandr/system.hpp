//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SYSTEM_HPP_INCLUDED

#include <sge/opengl/xrandr/extension.hpp>
#include <sge/opengl/xrandr/state_unique_ptr.hpp>
#include <sge/opengl/xrandr/system_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		sge::opengl::xrandr::extension const &
	);

	~system();

	sge::opengl::xrandr::state_unique_ptr
	create_state(
		sge::window::object &
	);
private:
	sge::opengl::xrandr::extension const extension_;
};

}
}
}

#endif
