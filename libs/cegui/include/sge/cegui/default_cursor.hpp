//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_DEFAULT_CURSOR_HPP_INCLUDED
#define SGE_CEGUI_DEFAULT_CURSOR_HPP_INCLUDED

#include <sge/cegui/syringe_fwd.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace cegui
{

class default_cursor
{
	FCPPT_NONCOPYABLE(
		default_cursor
	);
public:
	SGE_CEGUI_DETAIL_SYMBOL
	explicit
	default_cursor(
		sge::cegui::syringe &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	~default_cursor();

	SGE_CEGUI_DETAIL_SYMBOL
	void
	process_event(
		sge::input::event_base const &
	);
private:
	sge::cegui::syringe &syringe_;
};

}
}

#endif
