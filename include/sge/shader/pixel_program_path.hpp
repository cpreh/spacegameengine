#ifndef SGE_SHADER_PIXEL_PROGRAM_PATH_HPP_INCLUDED
#define SGE_SHADER_PIXEL_PROGRAM_PATH_HPP_INCLUDED

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
