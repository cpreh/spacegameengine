//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_EXCEPTION_HPP_INCLUDED
#define SGE_GUI_EXCEPTION_HPP_INCLUDED

#include <sge/core/exception.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge::gui
{

/**
\brief The base class for every gui exception

\ingroup sge_gui
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL exception
:
	public sge::core::exception
{
public:
	SGE_GUI_DETAIL_SYMBOL
	explicit
	exception(
		fcppt::string &&
	);

	SGE_GUI_DETAIL_SYMBOL
	exception(
		exception &&
	)
	noexcept;

	SGE_GUI_DETAIL_SYMBOL
	exception(
		exception const &
	);

	SGE_GUI_DETAIL_SYMBOL
	exception &
	operator=(
		exception &&
	)
	noexcept;

	SGE_GUI_DETAIL_SYMBOL
	exception &
	operator=(
		exception const &
	);

	SGE_GUI_DETAIL_SYMBOL
	~exception() noexcept
	override;
};

}

#endif
