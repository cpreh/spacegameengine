//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WAVE_IGNORE_CHUNKS_UNTIL_HPP_INCLUDED
#define SGE_WAVE_IGNORE_CHUNKS_UNTIL_HPP_INCLUDED

#include <sge/wave/header.hpp>
#include <fcppt/endianness/format_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wave
{

[[nodiscard]]
bool
ignore_chunks_until(
	fcppt::log::object &,
	std::istream &,
	sge::wave::header const &,
	fcppt::endianness::format
);

}
}

#endif
