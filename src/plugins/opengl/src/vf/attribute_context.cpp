/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/vf/attribute_config.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/vf/optional_attribute_config.hpp>


sge::opengl::vf::attribute_context::attribute_context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	config_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				2u
			},
			sge::opengl::info::minor_version{
				0u
			}
		)
		?
			sge::opengl::vf::optional_attribute_config(
				sge::opengl::vf::attribute_config(
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLVERTEXATTRIBPOINTERPROC
						>(
							_info.load_function(
								"glVertexAttribPointer"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLENABLEVERTEXATTRIBARRAYPROC
						>(
							_info.load_function(
								"glEnableVertexAttribArray"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLDISABLEVERTEXATTRIBARRAYPROC
						>(
							_info.load_function(
								"glDisableVertexAttribArray"
							)
						)
					)
				)
			)
		:
			sge::opengl::info::extension_supported(
				_info.extensions(),
				sge::opengl::info::extension{
					"GL_ARB_vertex_shader"
				}
			)
			?
				sge::opengl::vf::optional_attribute_config(
					sge::opengl::vf::attribute_config(
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLVERTEXATTRIBPOINTERPROC
							>(
								_info.load_function(
									"glVertexAttribPointerARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLENABLEVERTEXATTRIBARRAYPROC
							>(
								_info.load_function(
									"glEnableVertexAttribArrayARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLDISABLEVERTEXATTRIBARRAYPROC
							>(
								_info.load_function(
									"glDisableVertexAttribArrayARB"
								)
							)
						)
					)
				)
			:
				sge::opengl::vf::optional_attribute_config()
	)
{
}

sge::opengl::vf::attribute_context::~attribute_context()
{
}

sge::opengl::vf::optional_attribute_config const &
sge::opengl::vf::attribute_context::config() const
{
	return
		config_;
}

sge::opengl::context::id const
sge::opengl::vf::attribute_context::static_id(
	sge::opengl::context::make_id()
);
