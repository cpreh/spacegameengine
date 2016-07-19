/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/config.hpp>
#include <sge/opengl/platform/create_system.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/platform/system_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/system/object.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/container/make_array.hpp>
#include <fcppt/either/first_success.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <vector>
#include <fcppt/config/external_end.hpp>

#include <fcppt/config/platform.hpp>
#if defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/x11/system.hpp>
#include <awl/backends/x11/system/object.hpp>
#endif
#if defined(SGE_OPENGL_HAVE_WAYLAND)
#include <sge/opengl/wayland/system.hpp>
#include <awl/backends/wayland/system/object.hpp>
#endif
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/opengl/windows/system.hpp>
#endif


#if defined(SGE_OPENGL_HAVE_X11) || defined(SGE_OPENGL_HAVE_WAYLAND)
#define SGE_OPENGL_NEED_TRY_CREATE
#define SGE_OPENGL_NEED_SYSTEM
#endif

#if defined(SGE_OPENGL_HAVE_X11)
#define SGE_OPENGL_NEED_LOG
#endif

namespace
{

typedef
fcppt::either::object<
	fcppt::string,
	sge::opengl::platform::system_unique_ptr
>
either_type;

typedef
fcppt::function<
	either_type ()
>
function_type;

#if defined(SGE_OPENGL_NEED_TRY_CREATE)

template<
	typename Result,
	typename Arg
>
using
create_function
=
fcppt::function<
	fcppt::unique_ptr<
		Result
	>(
		fcppt::reference<
			Arg
		>
	)
>;

template<
	typename Result,
	typename Arg
>
function_type
try_create(
	awl::system::object &_awl_system,
	create_function<
		Result,
		Arg
	> const _create
)
{
	return
		function_type{
			[
				&_create,
				&_awl_system
			]{
				return
					fcppt::either::from_optional(
						fcppt::optional::map(
							fcppt::cast::dynamic<
								Arg
							>(
								_awl_system
							),
							[
								&_create
							](
								fcppt::reference<
									Arg
								> const _system
							)
							{
								return
									fcppt::unique_ptr_to_base<
										sge::opengl::platform::system
									>(
										_create(
											_system
										)
									);
							}
						),
						[]{
							return
								fcppt::string{
									FCPPT_TEXT("Failed to convert to \"")
									+
									fcppt::type_name_from_info(
										typeid(
											Arg
										)
									)
									+
									FCPPT_TEXT('"')
								};
						}
					);
			}
		};
}
#endif

}

sge::opengl::platform::system_unique_ptr
sge::opengl::platform::create_system(
#if defined(SGE_OPENGL_NEED_LOG)
	fcppt::log::object &_log
#else
	fcppt::log::object &
#endif
	,
#if defined(SGE_OPENGL_NEED_SYSTEM)
	awl::system::object &_awl_system
#else
	awl::system::object &
#endif
)
{
	return
		fcppt::either::to_exception(
			fcppt::either::first_success(
				fcppt::container::make_array(
#if defined(SGE_OPENGL_HAVE_X11)
					/*
					try_create<
						sge::opengl::x11::system,
						awl::backends::x11::system::object
					>(*/
					try_create(
						_awl_system,
						create_function<
							sge::opengl::x11::system,
							awl::backends::x11::system::object
						>{
							[
								&_log
							](
								fcppt::reference<
									awl::backends::x11::system::object
								> const _system
							)
							{
								return
									fcppt::make_unique_ptr<
										sge::opengl::x11::system
									>(
										_log,
										_system.get()
									);
							}
						}
					),
#endif
#if defined(SGE_OPENGL_HAVE_WAYLAND)
					try_create<
						sge::opengl::wayland::system,
						awl::backends::wayland::system::object
					>(
						_awl_system,
						create_function<
							sge::opengl::wayland::system,
							awl::backends::wayland::system::object
						>{
							[](
								fcppt::reference<
									awl::backends::wayland::system::object
								> const _system
							)
							{
								return
									fcppt::make_unique_ptr<
										sge::opengl::wayland::system
									>(
										_system.get()
									);
							}
						}
					),
#endif
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
					function_type{
						[]{
							return
								either_type{
									fcppt::unique_ptr_to_base<
										sge::opengl::platform::system
									>(
										fcppt::make_unique_ptr<
											sge::opengl::windows::system
										>()
									)
								};
						}
					},
#endif
					function_type{
						[]{
							return
								either_type{
									fcppt::string{
										FCPPT_TEXT("")
									}
								};
						}
					}
				)
			),
			[](
				std::vector<
					fcppt::string
				> const &_failures
			)
			{
				return
					sge::renderer::exception{
						FCPPT_TEXT("Cannot create any opengl systems: ")
						+
						fcppt::algorithm::join_strings(
							_failures,
							fcppt::string{
								FCPPT_TEXT(", ")
							}
						)
					};
			}
		);
}
