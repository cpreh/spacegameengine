#include <sge/audio/unsupported_format.hpp>
#include <fcppt/text.hpp>

sge::audio::unsupported_format::unsupported_format(
	optional_path const &_path,
	fcppt::string const &_string
)
:
	audio::file_exception(
		_path,
		FCPPT_TEXT("file has unsupported format: ")
		+ _string
	)
{}
