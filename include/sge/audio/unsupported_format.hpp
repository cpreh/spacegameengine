#ifndef SGE_AUDIO_UNSUPPORTED_FORMAT_HPP_INCLUDED
#define SGE_AUDIO_UNSUPPORTED_FORMAT_HPP_INCLUDED

#include <sge/audio/file_exception.hpp>
#include <sge/audio/optional_path.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace audio
{
class SGE_CLASS_SYMBOL unsupported_format
:
	public file_exception
{
public:
	SGE_SYMBOL unsupported_format(
		optional_path const &,
		fcppt::string const &
	);
};
}
}

#endif
