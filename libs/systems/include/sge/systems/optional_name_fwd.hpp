//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_OPTIONAL_NAME_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_OPTIONAL_NAME_FWD_HPP_INCLUDED

#include <sge/plugin/name.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace systems
{

typedef fcppt::optional::object<
	sge::plugin::name
> optional_name;

}
}

#endif
