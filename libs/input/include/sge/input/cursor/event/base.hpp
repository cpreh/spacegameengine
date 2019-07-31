//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_CURSOR_EVENT_BASE_HPP_INCLUDED
#define SGE_INPUT_CURSOR_EVENT_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace input
{
namespace cursor
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base
:
	public sge::input::event_base
{
	FCPPT_NONCOPYABLE(
		base
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	base(
		sge::input::cursor::shared_ptr
	);

	SGE_INPUT_DETAIL_SYMBOL
	~base()
	override;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::shared_ptr const &
	cursor() const;
private:
	sge::input::cursor::shared_ptr const cursor_;
};

}
}
}
}

#endif
