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


#include <sge/opengl/glx/proc_address.hpp>
#include <sge/opengl/glx/proc_address_function.hpp>
#include <sge/opengl/glx/raw_function_ref.hpp>
#include <sge/opengl/glx/swap_functions.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	typename Ret
>
fcppt::reference<
	Ret
>
cast_function(
	sge::opengl::glx::raw_function_ref const _func
)
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wundefined-reinterpret-cast)

	return
		fcppt::make_ref(
			reinterpret_cast<
				std::add_lvalue_reference_t<
					Ret
				>
			>(
				_func.get()
			)
		);

FCPPT_PP_POP_WARNING

}

}

sge::opengl::glx::swap_functions::swap_functions(
	sge::opengl::glx::proc_address_function _proc_address
)
:
	swap_interval_sgi_(
		fcppt::optional::map(
			sge::opengl::glx::proc_address(
				_proc_address,
				"glXSwapIntervalSGI"
			),
			[](
				sge::opengl::glx::raw_function_ref const _func
			)
			{
				return
					cast_function<
						glx_swap_interval_sgi
					>(
						_func
					);
			}
		)
	),
	swap_interval_ext_(
		fcppt::optional::map(
			sge::opengl::glx::proc_address(
				_proc_address,
				"glXSwapIntervalEXT"
			),
			[](
				sge::opengl::glx::raw_function_ref const _func
			)
			{
				return
					cast_function<
						glx_swap_interval_ext
					>(
						_func
					);
			}
		)
	)
{
}

sge::opengl::glx::swap_functions::optional_glx_swap_interval_sgi
sge::opengl::glx::swap_functions::swap_interval_sgi() const
{
	return
		swap_interval_sgi_;
}

sge::opengl::glx::swap_functions::optional_glx_swap_interval_ext
sge::opengl::glx::swap_functions::swap_interval_ext() const
{
	return
		swap_interval_ext_;
}
