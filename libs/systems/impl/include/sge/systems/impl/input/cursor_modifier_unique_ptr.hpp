//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_INPUT_CURSOR_MODIFIER_UNIQUE_PTR_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_INPUT_CURSOR_MODIFIER_UNIQUE_PTR_HPP_INCLUDED

#include <sge/systems/impl/input/cursor_modifier_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge::systems::impl::input
{

using
cursor_modifier_unique_ptr
=
fcppt::unique_ptr<
	sge::systems::impl::input::cursor_modifier
>;

}

#endif
