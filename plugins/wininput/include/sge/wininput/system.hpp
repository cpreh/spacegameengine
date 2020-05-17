//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WININPUT_SYSTEM_HPP_INCLUDED
#define SGE_WININPUT_SYSTEM_HPP_INCLUDED

#include <sge/input/capabilities_field_fwd.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace sge
{
namespace wininput
{

class system
:
	public sge::input::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		fcppt::log::context_reference
	);

	~system()
	override;
private:
	sge::input::processor_unique_ptr
	create_processor(
		sge::window::object_ref
	)
	override;

	sge::input::capabilities_field
	capabilities() const
	override;

	fcppt::log::object log_;
};

}
}

#endif
