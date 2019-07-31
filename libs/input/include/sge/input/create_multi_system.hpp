//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_CREATE_MULTI_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_CREATE_MULTI_SYSTEM_HPP_INCLUDED

#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace sge
{
namespace input
{

SGE_INPUT_DETAIL_SYMBOL
sge::input::system_unique_ptr
create_multi_system(
	fcppt::log::context &,
	sge::input::plugin::collection const &
);

}
}

#endif
