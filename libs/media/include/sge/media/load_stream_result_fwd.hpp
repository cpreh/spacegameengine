//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_LOAD_STREAM_RESULT_FWD_HPP_INCLUDED
#define SGE_MEDIA_LOAD_STREAM_RESULT_FWD_HPP_INCLUDED

#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/variant/variadic_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{

template<
	typename File
>
using
load_stream_result
=
fcppt::variant::variadic<
	sge::media::stream_unique_ptr,
	fcppt::unique_ptr<
		File
	>
>;

}
}

#endif
