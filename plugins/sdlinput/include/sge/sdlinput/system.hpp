//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_SYSTEM_HPP_INCLUDED
#define SGE_SDLINPUT_SYSTEM_HPP_INCLUDED

#include <sge/input/capabilities_field_fwd.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/sdl/system/init.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sdlinput
{

class system
:
	public sge::input::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system();

	~system()
	override;
private:
	sge::input::processor_unique_ptr
	create_processor(
		sge::window::object &
	)
	override;

	sge::input::capabilities_field
	capabilities() const
	override;

	awl::backends::sdl::system::init const init_;
};

}
}

#endif
