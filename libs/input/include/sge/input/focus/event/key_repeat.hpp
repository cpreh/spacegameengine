//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_FOCUS_EVENT_KEY_REPEAT_HPP_INCLUDED
#define SGE_INPUT_FOCUS_EVENT_KEY_REPEAT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/input/focus/event/key_repeat_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace input
{
namespace focus
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL key_repeat
:
	public sge::input::focus::event::base
{
	FCPPT_NONMOVABLE(
		key_repeat
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	key_repeat(
		sge::input::focus::shared_ptr,
		sge::input::focus::key const &
	);

	SGE_INPUT_DETAIL_SYMBOL
	~key_repeat()
	override;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::focus::key const &
	key() const;
private:
	sge::input::focus::key const key_;
};

}
}
}
}

#endif
