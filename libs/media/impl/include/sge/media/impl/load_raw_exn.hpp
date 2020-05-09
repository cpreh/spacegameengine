//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_IMPL_LOAD_RAW_EXN_HPP_INCLUDED
#define SGE_MEDIA_IMPL_LOAD_RAW_EXN_HPP_INCLUDED

#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/impl/load_raw.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


namespace sge
{
namespace media
{
namespace impl
{

template<
	typename Result,
	typename Exception,
	typename System
>
Result
load_raw_exn(
	fcppt::reference<
		System
	> const _system,
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	return
		fcppt::optional::to_exception(
			sge::media::impl::load_raw<
				Result
			>(
				_system,
				_range,
				_extension
			),
			[]{
				return
					Exception(
						FCPPT_TEXT("load_raw_exn failed")
					);
			}
		);
}

}
}
}

#endif
