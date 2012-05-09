/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VF_TEXPOS_HPP_INCLUDED
#define SGE_RENDERER_VF_TEXPOS_HPP_INCLUDED

#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/is_index.hpp>
#include <sge/renderer/vf/texpos_fwd.hpp>
#include <sge/renderer/vf/vector_base.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/type_traits/is_float_or_double.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/static_assert.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Format,
	sge::renderer::vf::element_count_type NumSubElements,
	typename Index
>
struct texpos
:
sge::renderer::vf::vector_base<
	Format,
	NumSubElements
>
{
	BOOST_STATIC_ASSERT(
		fcppt::type_traits::is_float_or_double<
			Format
		>::value
	);

	BOOST_STATIC_ASSERT(
		NumSubElements >= 2
		&& NumSubElements <= 3
	);

	BOOST_STATIC_ASSERT(
		sge::renderer::vf::is_index<
			Index
		>::value
	);

	typedef Index index;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
