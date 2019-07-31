//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_SDLINPUT_FOCUS_OBJECT_HPP_INCLUDED

#include <sge/input/focus/object.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sdlinput
{
namespace focus
{

class object
:
	public
		sge::input::focus::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::window::object &
	);

	~object()
	override;

	sge::window::object &
	window() const
	override;
private:
	sge::window::object &window_;
};

}
}
}

#endif
