//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_FONT_HPP_INCLUDED
#define SGE_SYSTEMS_FONT_HPP_INCLUDED

#include <sge/plugin/name.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/detail/symbol.hpp>


namespace sge
{
namespace systems
{

class font
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	font();

	[[nodiscard]]
	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::font
	name(
		sge::plugin::name &&
	) &&;

	[[nodiscard]]
	sge::systems::optional_name const &
	name() const;
private:
	sge::systems::optional_name name_;
};

}
}

#endif
