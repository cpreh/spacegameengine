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
#include <sge/opengl/backend/create_system.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/backend/system_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/system/object_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/either/first_success.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/either/try_call.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <utility>
#include <fcppt/config/external_end.hpp>
#if defined(SGE_OPENGL_HAVE_SDL)
#include <sge/opengl/sdl/backend_system.hpp>
#include <awl/backends/sdl/system/object.hpp>
#endif
#if defined(SGE_OPENGL_HAVE_EGL)
#include <sge/opengl/egl/system.hpp>
#endif
#if defined(SGE_OPENGL_HAVE_GLX)
#include <sge/opengl/glx/system.hpp>
#include <awl/backends/x11/system/object.hpp>
#endif
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/opengl/wgl/system.hpp>
#endif


namespace
{

typedef
fcppt::function<
	sge::opengl::backend::system_unique_ptr(
		fcppt::log::object &,
		awl::system::object &
	)
>
create_function_exn;

typedef
std::vector<
	create_function_exn
>
create_function_exn_vector;

create_function_exn_vector
create_functions_exn()
{
	return
		create_function_exn_vector{
#if defined(SGE_OPENGL_HAVE_SDL)
			create_function_exn{
				[](
					fcppt::log::object &,
					awl::system::object &_awl_system
				)
				{
					return
						fcppt::unique_ptr_to_base<
							sge::opengl::backend::system
						>(
							fcppt::make_unique_ptr<
								sge::opengl::sdl::backend_system
							>(
								fcppt::cast::dynamic_exn<
									awl::backends::sdl::system::object &
								>(
									_awl_system
								)
							)
						);
				}
			},
#endif
#if defined(SGE_OPENGL_HAVE_EGL)
			create_function_exn{
				[](
					fcppt::log::object &_log,
					awl::system::object &_awl_system
				)
				{
					return
						fcppt::unique_ptr_to_base<
							sge::opengl::backend::system
						>(
							fcppt::make_unique_ptr<
								sge::opengl::egl::system
							>(
								_log,
								_awl_system
							)
						);
				}
			},
#endif
#if defined(SGE_OPENGL_HAVE_GLX)
			create_function_exn{
				[](
					fcppt::log::object &_log,
					awl::system::object &_awl_system
				)
				{
					return
						fcppt::unique_ptr_to_base<
							sge::opengl::backend::system
						>(
							fcppt::make_unique_ptr<
								sge::opengl::glx::system
							>(
								_log,
								fcppt::cast::dynamic_exn<
									awl::backends::x11::system::object &
								>(
									_awl_system
								)
							)
						);
				}
			},
#endif
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
			create_function_exn{
				[](
					fcppt::log::object &,
					awl::system::object &_awl_system
				)
				{
					return
						fcppt::unique_ptr_to_base<
							sge::opengl::backend::system
						>(
							fcppt::make_unique_ptr<
								sge::opengl::wgl::system
							>(
								_awl_system
							)
						);
				}
			},
#endif
			create_function_exn{
				[](
					fcppt::log::object &,
					awl::system::object &
				)
				->
				sge::opengl::backend::system_unique_ptr
				{
					throw
						sge::renderer::exception{
							fcppt::string{
								FCPPT_TEXT("All possibilities exhausted.")
							}
						};
				}
			}
		};
}

typedef
fcppt::function<
	fcppt::either::object<
		fcppt::string,
		sge::opengl::backend::system_unique_ptr
	>()
>
create_function;

typedef
std::vector<
	create_function
>
create_function_vector;

create_function_vector
create_functions(
	fcppt::log::object &_log,
	awl::system::object &_awl_system
)
{
	return
		fcppt::algorithm::map<
			create_function_vector
		>(
			create_functions_exn(),
			[
				&_log,
				&_awl_system
			](
				create_function_exn &&_function
			)
			{
				return
					create_function{
						[
							&_log,
							&_awl_system,
							function =
								std::move(
									_function
								)
						]()
						->
						fcppt::either::object<
							fcppt::string,
							sge::opengl::backend::system_unique_ptr
						>
						{
							return
								fcppt::either::try_call<
									fcppt::exception
								>(
									[
										&function,
										&_log,
										&_awl_system
									]()
									{
										return
											function(
												_log,
												_awl_system
											);
									},
									[](
										fcppt::exception const &_error
									)
									->
									fcppt::string
									{
										return
											_error.string();
									}
								);
						}
					};
			}
		);
}

}

sge::opengl::backend::system_unique_ptr
sge::opengl::backend::create_system(
	fcppt::log::object &_log,
	awl::system::object &_awl_system
)
{
	return
		fcppt::either::to_exception(
			fcppt::either::first_success(
				create_functions(
					_log,
					_awl_system
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
						FCPPT_TEXT("Cannot create an OpenGL backend: ")
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
