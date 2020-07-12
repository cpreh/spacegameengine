//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_CALLBACK_PARAMETERS_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_PARAMETERS_HPP_INCLUDED

#include <sge/console/long_description.hpp>
#include <sge/console/short_description.hpp>
#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/detail/symbol.hpp>
#include <sge/font/string.hpp>


namespace sge
{
namespace console
{
namespace callback
{

class parameters
{
public:
	SGE_CONSOLE_DETAIL_SYMBOL
	parameters(
		sge::console::callback::function &&,
		sge::console::callback::name &&
	);

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::callback::parameters
	short_description(
		sge::font::string &&
	) &&;

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::callback::parameters
	long_description(
		sge::font::string &&
	) &&;

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::callback::function &
	function();

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::callback::function const &
	function() const;

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::font::string &
	name();

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::font::string const &
	name() const;

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::short_description &
	short_description();

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::short_description const &
	short_description() const;

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::long_description &
	long_description();

	[[nodiscard]]
	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::long_description const &
	long_description() const;
private:
	sge::console::callback::function function_;

	sge::font::string name_;

	sge::console::short_description short_description_;

	sge::console::long_description long_description_;
};

}
}
}

#endif
