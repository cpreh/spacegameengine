//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_WINDOW_HPP_INCLUDED

#include <sge/systems/window_fwd.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/detail/symbol.hpp>


namespace sge::systems
{

class window
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	window(
		sge::systems::window_source &&
	);

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::window
	dont_show() &&;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::window
	dont_quit() &&;

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::window
	hide_cursor() &&;

	[[nodiscard]]
	sge::systems::window_source const &
	source() const;

	[[nodiscard]]
	bool
	show() const;

	[[nodiscard]]
	bool
	quit() const;
private:
	sge::systems::window_source source_;

	bool show_;

	bool quit_;
};

}

#endif
