//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/choose_resolution.hpp>
#include <sge/opengl/xrandr/const_configuration_ref.hpp>
#include <sge/opengl/xrandr/current_mode.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/resolution_unique_ptr.hpp>
#include <sge/opengl/xrandr/sizes.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_unsigned.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::resolution_unique_ptr
sge::opengl::xrandr::choose_resolution(
	sge::opengl::xrandr::const_configuration_ref const _config,
	awl::backends::x11::window::const_base_ref const _window,
	sge::renderer::display_mode::object const &_mode
)
{
	sge::opengl::xrandr::sizes const sizes{
		_config
	};

	return
		fcppt::optional::to_exception(
			fcppt::algorithm::find_by_opt<
				sge::opengl::xrandr::resolution_unique_ptr
			>(
				fcppt::make_int_range_count(
					sizes.size()
				),
				[
					&_config,
					&_window,
					&_mode,
					&sizes
				](
					sge::opengl::xrandr::mode_index const _index
				)
				{
					::XRRScreenSize const &current(
						sizes[
							_index
						]
					);

					fcppt::math::dim::static_<
						int,
						2
					> const current_size{
						current.width,
						current.height
					};

					using
					optional_result
					=
					fcppt::optional::object<
						sge::opengl::xrandr::resolution_unique_ptr
					>;

					return
						fcppt::math::dim::structure_cast<
							sge::renderer::screen_size,
							fcppt::cast::size_fun
						>(
							fcppt::math::dim::to_unsigned(
								current_size
							)
						)
						==
						_mode.pixel_size().get()
						?
							optional_result{
								fcppt::make_unique_ptr<
									sge::opengl::xrandr::resolution
								>(
									_window,
									_config,
									_index,
									_mode.refresh_rate(),
									sge::opengl::xrandr::current_mode(
										_config
									)
								)
							}
						:
							optional_result{}
						;
				}
			),
			[]{
				return
					sge::renderer::exception{
						FCPPT_TEXT("No matching resolution found!")
					};
			}
		);
}
