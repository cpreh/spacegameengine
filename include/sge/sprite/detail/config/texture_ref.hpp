/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_CONFIG_TEXTURE_REF_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_TEXTURE_REF_HPP_INCLUDED

#include <sge/sprite/detail/config/find_texture_config.hpp>
#include <sge/sprite/detail/primitives/texture_ref_type.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/none_t.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
{

template<
	typename Choices
>
struct texture_ref
{
private:

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	template<
		typename Iterator
	>
	struct obtain_ref_type
	:
	sge::sprite::detail::primitives::texture_ref_type<
		boost::mpl::deref<
			Iterator
		>::type::ownership::value
	>
	{
	};

FCPPT_PP_POP_WARNING

	typedef typename sge::sprite::detail::config::find_texture_config<
		Choices
	>::type texture_iterator;
public:
	typedef typename boost::mpl::eval_if<
		std::is_same<
			texture_iterator,
			typename boost::mpl::end<
				typename Choices::optional_elements
			>::type
		>,
		boost::mpl::identity<
			boost::none_t
		>,
		obtain_ref_type<
			texture_iterator
		>
	>::type type;
};

}
}
}
}

#endif
