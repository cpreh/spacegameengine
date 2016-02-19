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


#ifndef SGE_RENDERER_VF_VERTEX_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_VERTEX_DECL_HPP_INCLUDED

#include <sge/renderer/vf/pointer.hpp>
#include <sge/renderer/vf/vertex_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Part,
	typename Constness
>
class vertex
{
	FCPPT_NONASSIGNABLE(
		vertex
	);
public:
	typedef
	sge::renderer::vf::pointer<
		Constness
	>
	pointer;

	typedef typename Part::elements elements;

	typedef typename Part::offsets offsets;

	explicit
	vertex(
		pointer
	);

	template<
		typename Field
	>
	typename boost::enable_if<
		boost::mpl::contains<
			elements,
			Field
		>,
		void
	>::type
	set(
		typename Field::packed_type const &
	);

	template<
		typename Field
	>
	typename boost::enable_if<
		boost::mpl::contains<
			elements,
			Field
		>,
		typename Field::packed_type
	>::type
	get() const;
private:
	pointer const data_;
};

}
}
}

#endif
