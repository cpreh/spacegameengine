/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PLUGIN_OBJECT_HPP_INCLUDED
#define SGE_PLUGIN_OBJECT_HPP_INCLUDED

#include <sge/symbol.hpp>
#include <sge/plugin/object_fwd.hpp>
#include <sge/plugin/detail/traits.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>
#include <sge/plugin/library/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/shared_ptr_impl.hpp>



namespace sge
{
namespace plugin
{

template<
	typename Type
>
class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef
	typename
	sge::plugin::detail::traits<
		Type
	>::loader_fun
	loader_fun;

	typedef
	fcppt::shared_ptr<
		sge::plugin::library::object
	>
	library_shared_ptr;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	explicit
	object(
		library_shared_ptr const &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	object(
		object &&
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	object &
	operator=(
		object &&
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	~object();

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	loader_fun
	get() const;
private:
	library_shared_ptr lib_;

	loader_fun loader_;
};

}
}

#endif
