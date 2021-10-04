//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_IMPL_LOAD_EXN_HPP_INCLUDED
#define SGE_MEDIA_IMPL_LOAD_EXN_HPP_INCLUDED

#include <sge/media/impl/load.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::media::impl
{

template<
	typename Result,
	typename Exception,
	typename System
>
Result
load_exn(
	fcppt::reference<
		System
	> const _system,
	std::filesystem::path const &_path
)
{
	return
		fcppt::optional::to_exception(
			sge::media::impl::load<
				Result,
				Exception
			>(
				_system,
				_path
			),
			[
				&_path
			]{
				return
					Exception(
						FCPPT_TEXT("Unable to load ")
						+
						fcppt::filesystem::path_to_string(
							_path
						)
					);
			}
		);
}

}

#endif
