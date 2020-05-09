//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_LIBRARY_SYMBOL_NOT_FOUND_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_SYMBOL_NOT_FOUND_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/exception.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace plugin
{
namespace library
{

class SGE_CORE_DETAIL_CLASS_SYMBOL symbol_not_found
:
	public sge::plugin::library::exception
{
public:
	SGE_PLUGIN_DETAIL_SYMBOL
	symbol_not_found(
		fcppt::string &&,
		sge::plugin::library::symbol_string &&
	);

	SGE_PLUGIN_DETAIL_SYMBOL
	symbol_not_found(
		symbol_not_found &&
	)
	noexcept;

	SGE_PLUGIN_DETAIL_SYMBOL
	symbol_not_found(
		symbol_not_found const &
	);

	SGE_PLUGIN_DETAIL_SYMBOL
	symbol_not_found &
	operator=(
		symbol_not_found &&
	)
	noexcept;

	SGE_PLUGIN_DETAIL_SYMBOL
	symbol_not_found &
	operator=(
		symbol_not_found const &
	);

	[[nodiscard]]
	SGE_PLUGIN_DETAIL_SYMBOL
	fcppt::string const &
	library_name() const;

	[[nodiscard]]
	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::library::symbol_string const &
	symbol() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	~symbol_not_found()
	override;
private:
	fcppt::string library_name_;

	sge::plugin::library::symbol_string symbol_;
};

}
}
}

#endif
