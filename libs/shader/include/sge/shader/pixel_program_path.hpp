//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_PIXEL_PROGRAM_PATH_HPP_INCLUDED
#define SGE_SHADER_PIXEL_PROGRAM_PATH_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace shader
{
FCPPT_MAKE_STRONG_TYPEDEF(
	boost::filesystem::path,
	pixel_program_path);
}
}

#endif
