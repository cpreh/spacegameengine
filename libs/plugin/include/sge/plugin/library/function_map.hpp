//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_LIBRARY_FUNCTION_MAP_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_FUNCTION_MAP_HPP_INCLUDED

#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/function_base.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace plugin
{
namespace library
{

class function_map
{
public:
	typedef
	std::unordered_map<
		sge::plugin::library::symbol_string,
		sge::plugin::library::function_base
	>
	container;

	SGE_PLUGIN_DETAIL_SYMBOL
	explicit
	function_map(
		container &&
	);

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::library::function_base
	function(
		sge::plugin::library::symbol_string const &
	) const;

	SGE_PLUGIN_DETAIL_SYMBOL
	container const &
	get() const;
private:
	container functions_;
};

}
}
}

#endif
