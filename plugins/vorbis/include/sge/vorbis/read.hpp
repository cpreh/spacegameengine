//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_VORBIS_READ_HPP_INCLUDED
#define SGE_VORBIS_READ_HPP_INCLUDED

#include <sge/audio/raw_pointer.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/vorbis/stream_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace vorbis
{

std::size_t
read(
	fcppt::log::object &,
	sge::vorbis::stream &,
	sge::media::optional_name const &,
	sge::audio::raw_pointer,
	std::size_t
);

}
}

#endif
