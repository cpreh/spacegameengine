//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_EXCEPTION_HPP_INCLUDED
#define SGE_CONSOLE_EXCEPTION_HPP_INCLUDED

#include <sge/console/detail/symbol.hpp>
#include <sge/core/exception.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/font/string.hpp>


namespace sge::console
{

class SGE_CORE_DETAIL_CLASS_SYMBOL exception
:
	public sge::core::exception
{
public:
	SGE_CONSOLE_DETAIL_SYMBOL
	explicit
	exception(
		sge::font::string &&
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	exception(
		exception &&
	)
	noexcept;

	SGE_CONSOLE_DETAIL_SYMBOL
	exception(
		exception const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	exception &
	operator=(
		exception &&
	)
	noexcept;

	SGE_CONSOLE_DETAIL_SYMBOL
	exception &
	operator=(
		exception const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	~exception() noexcept
	override;

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::font::string const &
	console_string() const;
private:
	sge::font::string console_string_;
};

}

#endif
