//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_INFO_CLASS_CAST_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_CLASS_CAST_HPP_INCLUDED

#include <fcppt/brigand/found_t.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/type_traits/remove_cv_ref_t.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <brigand/sequences/list.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace info
{

template<
	typename Result
>
std::enable_if_t<
	fcppt::brigand::found_t<
		brigand::list<
			XIButtonClassInfo,
			XIValuatorClassInfo,
			XIKeyClassInfo,
			XIScrollClassInfo
		>,
		fcppt::type_traits::remove_cv_ref_t<
			Result
		>
	>::value,
	Result
>
class_cast(
	XIAnyClassInfo const &_info
)
{
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Wstrict-aliasing)

	return
		reinterpret_cast<
			Result
		>(
			_info
		);

	FCPPT_PP_POP_WARNING
}

}
}
}
}

#endif
