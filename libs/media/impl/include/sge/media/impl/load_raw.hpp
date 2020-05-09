//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_IMPL_LOAD_RAW_HPP_INCLUDED
#define SGE_MEDIA_IMPL_LOAD_RAW_HPP_INCLUDED

#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/impl/raw_streambuf.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{
namespace impl
{

template<
	typename Result,
	typename System
>
fcppt::optional::object<
	Result
>
load_raw(
	fcppt::reference<
		System
	> const _system,
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	sge::media::impl::raw_streambuf buf{
		_range
	};

	return
		fcppt::variant::to_optional<
			Result
		>(
			_system.get().load_stream(
				fcppt::make_unique_ptr<
					std::istream
				>(
					&buf
				),
				_extension,
				sge::media::optional_name()
			)
		);
}

}
}
}

#endif
