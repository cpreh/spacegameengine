/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/index/dynamic/basic_view.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/export_symbol.hpp>

namespace
{

struct view_size_visitor
{
	typedef sge::renderer::size_type result_type;

	template<
		typename T
	>
	result_type
	operator()(
		T const &_t
	) const
	{
		return _t.size();
	}
};

struct view_format_visitor
{
	typedef sge::renderer::index::dynamic::format::type result_type;

	template<
		typename T
	>
	result_type
	operator()(
		T const &_t
	) const
	{
		return _t.format();
	}
};

}

template<
	bool IsConst
>
sge::renderer::index::dynamic::basic_view<IsConst>::basic_view(
	any_type const &_any
)
:
	any_(_any)
{}
	
template<
	bool IsConst
>
typename sge::renderer::index::dynamic::basic_view<IsConst>::any_type const &
sge::renderer::index::dynamic::basic_view<IsConst>::any() const
{
	return any_;
}

template<
	bool IsConst
>
sge::renderer::size_type
sge::renderer::index::dynamic::basic_view<IsConst>::size() const
{
	return
		fcppt::variant::apply_unary(
			::view_size_visitor(),
			any()
		);
}

template<
	bool IsConst
>
sge::renderer::index::dynamic::format::type
sge::renderer::index::dynamic::basic_view<IsConst>::format() const
{
	return 
		fcppt::variant::apply_unary(
			::view_format_visitor(),
			any()
		);
}

#define SGE_RENDERER_INDEX_DYNAMIC_DEFINE_BASIC_VIEW(x)\
template FCPPT_EXPORT_SYMBOL \
class sge::renderer::index::dynamic::basic_view<\
	x\
>;

SGE_RENDERER_INDEX_DYNAMIC_DEFINE_BASIC_VIEW(true)
SGE_RENDERER_INDEX_DYNAMIC_DEFINE_BASIC_VIEW(false)

#undef SGE_RENDERER_INDEX_DYNAMIC_DEFINE_BASIC_VIEW
