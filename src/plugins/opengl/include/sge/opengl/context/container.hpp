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


#ifndef SGE_OPENGL_CONTEXT_CONTAINER_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_CONTAINER_HPP_INCLUDED

#include <sge/opengl/context/base_fwd.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/container_fwd.hpp>
#include <sge/opengl/context/optional_base_ref_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

class container
{
	FCPPT_NONCOPYABLE(
		container
	);
public:
	typedef
	std::size_t
	size_type;

	container();

	~container();

	sge::opengl::context::optional_base_ref
	get(
		size_type
	) const;

	sge::opengl::context::optional_base_ref
	insert(
		size_type index,
		sge::opengl::context::base_unique_ptr &&
	);
private:
	typedef
	fcppt::optional<
		sge::opengl::context::base_unique_ptr
	>
	optional_unique_ptr;

	typedef
	std::vector<
		optional_unique_ptr
	>
	inner_container;

	inner_container elements_;
};

}
}
}

#endif
