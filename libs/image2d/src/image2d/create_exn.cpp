//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format_to_string.hpp>
#include <sge/image2d/create_exn.hpp>
#include <sge/image2d/exception.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/media/extension_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::image2d::file_unique_ptr
sge::image2d::create_exn(
	sge::image2d::system_ref const  _system,
	sge::image2d::view::const_object const &_view,
	sge::media::extension const &_extension
)
{
	return
		fcppt::optional::to_exception(
			_system.get().create(
				_view,
				_extension
			),
			[
				&_view,
				&_extension
			]{
				return
					sge::image2d::exception(
						FCPPT_TEXT("No image2d system can create an image with extension ")
						+
						_extension.get()
						+
						FCPPT_TEXT(" and type ")
						+
						sge::image::color::format_to_string(
							sge::image2d::view::format(
								_view
							)
						)
						+
						FCPPT_TEXT('!')
					);
			}
		);
}
