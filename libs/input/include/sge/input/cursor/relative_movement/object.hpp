//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_CURSOR_RELATIVE_MOVEMENT_OBJECT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_RELATIVE_MOVEMENT_OBJECT_HPP_INCLUDED

#include <sge/input/processor_ref.hpp>
#include <sge/input/cursor/relative_movement/object_fwd.hpp>
#include <sge/input/cursor/relative_movement/detail/object_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_decl.hpp>


namespace sge
{
namespace input
{
namespace cursor
{
namespace relative_movement
{

class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	object(
		sge::input::processor_ref
	);

	SGE_INPUT_DETAIL_SYMBOL
	~object();
private:
	using
	impl
	=
	fcppt::unique_ptr<
		sge::input::cursor::relative_movement::detail::object
	>;

	impl const impl_;
};

}
}
}
}

#endif
