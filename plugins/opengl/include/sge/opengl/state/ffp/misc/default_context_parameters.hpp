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


#ifndef SGE_OPENGL_STATE_FFP_MISC_DEFAULT_CONTEXT_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_MISC_DEFAULT_CONTEXT_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/ffp/misc/default_context_parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace misc
{

class default_context_parameters
{
public:
	default_context_parameters(
		fcppt::log::object &,
		sge::opengl::context::object &
	);

	fcppt::log::object &
	log() const;

	sge::opengl::context::object &
	context() const;
private:
	fcppt::reference<
		fcppt::log::object
	> log_;

	fcppt::reference<
		sge::opengl::context::object
	> context_;
};

}
}
}
}
}

#endif
