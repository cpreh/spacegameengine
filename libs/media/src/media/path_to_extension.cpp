//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/media/extension.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/path_to_extension.hpp>
#include <fcppt/string.hpp>
#include <fcppt/filesystem/extension_without_dot.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::media::optional_extension
sge::media::path_to_extension(
	boost::filesystem::path const &_path
)
{
	fcppt::string const ext(
		fcppt::filesystem::extension_without_dot(
			_path
		)
	);

	return
		ext.empty()
		?
			sge::media::optional_extension()
		:
			sge::media::optional_extension(
				sge::media::extension(
					ext
				)
			)
		;
}
