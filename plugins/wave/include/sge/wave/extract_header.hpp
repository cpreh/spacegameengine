//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WAVE_EXTRACT_HEADER_HPP_INCLUDED
#define SGE_WAVE_EXTRACT_HEADER_HPP_INCLUDED

#include <sge/wave/optional_header.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wave
{

sge::wave::optional_header
extract_header(
	std::istream &
);

}
}

#endif
