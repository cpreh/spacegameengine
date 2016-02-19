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


#ifndef SGE_OPENGL_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/opengl/context/base_fwd.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/id_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/optional_base_ref_fwd.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::opengl::info::context const &
	);

	~object();

	sge::opengl::context::optional_base_ref
	get(
		sge::opengl::context::id
	);

	sge::opengl::context::base &
	insert(
		sge::opengl::context::id,
		sge::opengl::context::base_unique_ptr &&
	);

	sge::opengl::info::context const &
	info() const;
private:
	sge::opengl::info::context const &info_;

	typedef
	fcppt::optional::object<
		sge::opengl::context::base_unique_ptr
	>
	optional_base_unique_ptr;

	typedef
	fcppt::container::index_map<
		optional_base_unique_ptr
	>
	container;

	container elements_;
};

}
}
}

#endif
