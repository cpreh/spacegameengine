//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_CREATE_FUNCTION_HPP_INCLUDED
#define SGE_WLINPUT_CREATE_FUNCTION_HPP_INCLUDED

#include <awl/backends/wayland/seat_ref.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/unique_ptr_fwd.hpp>


namespace sge
{
namespace wlinput
{

template<
	typename Type
>
using
create_function
=
fcppt::function<
	fcppt::unique_ptr<
		Type
	>(
		awl::backends::wayland::seat_ref
	)
>;

}

}

#endif
