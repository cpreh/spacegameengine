//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_VORBIS_STREAM_HPP_INCLUDED
#define SGE_VORBIS_STREAM_HPP_INCLUDED

#include <sge/vorbis/stream_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/vorbisfile.h>
#include <fcppt/config/external_end.hpp>


namespace sge::vorbis
{

class stream
{
	FCPPT_NONMOVABLE(
		stream
	);
public:
	explicit
	stream(
		OggVorbis_File const &
	);

	~stream();

	[[nodiscard]]
	OggVorbis_File *
	get();
private:
	OggVorbis_File file_;
};

}

#endif
