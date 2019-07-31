//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_STREAM_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SGE_MEDIA_STREAM_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{

typedef
fcppt::unique_ptr<
	std::istream
>
stream_unique_ptr;

}
}

#endif
