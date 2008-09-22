/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <boost/foreach.hpp>

sge::renderer::state::list::list(
	any const &a)
{
	set_.insert(a);
}

sge::renderer::state::list const
sge::renderer::state::list::operator()(
	any const &a) const
{
	state::list temp(*this);
	if(!temp.set_.insert(a).second)
		SGE_LOG_WARNING(
			log::global(),
			log::_1 << SGE_TEXT("duplicate renderer state given!"));
	return temp;
}

void sge::renderer::state::list::overwrite(
	any const& a)
{
	set_type::iterator const it(set_.find(a));
	if(it != set_.end())
		set_.erase(it);
	set_.insert(a);
	// TODO: is there a better way to do this?
}

template<typename T>
T sge::renderer::state::list::get() const
{
	BOOST_FOREACH(set_type::const_reference ref, set_)
		if(ref.type() == typeid(T))
			return boost::get<T>(ref);
	
	throw exception(
		SGE_TEXT("renderer::list::get(): state not found!"));
}

template<typename T>
T sge::renderer::state::list::get(
	trampoline<T> const &) const
{
	typedef typename trampoline<T>::var_type var_type;

	BOOST_FOREACH(set_type::const_reference ref, set_)
		if(ref.type() == typeid(var_type))
			return boost::get<var_type>(ref).value();
	
	throw exception(
		SGE_TEXT("renderer::list::get(): state not found!"));
}

sge::renderer::state::list::set_type const &
sge::renderer::state::list::values() const
{
	return set_;
}

sge::renderer::state::list const
sge::renderer::state::combine(
	list l,
	list const &r)
{
	// FIXME
//	BOOST_FOREACH(renderer::any_state const &s, states.values())
//		l.overwrite(r.get_dynamic(s));
	return l;
}

#define SGE_INSTANTIATE_STATE_LIST_GET(x)\
template x sge::renderer::state::list::get<x>() const;

SGE_INSTANTIATE_STATE_LIST_GET(sge::renderer::state::cull_mode::type)
SGE_INSTANTIATE_STATE_LIST_GET(sge::renderer::state::depth_func::type)
SGE_INSTANTIATE_STATE_LIST_GET(sge::renderer::state::stencil_func::type)
SGE_INSTANTIATE_STATE_LIST_GET(sge::renderer::state::alpha_func::type)
SGE_INSTANTIATE_STATE_LIST_GET(sge::renderer::state::fog_mode::type)
SGE_INSTANTIATE_STATE_LIST_GET(sge::renderer::state::draw_mode::type)
SGE_INSTANTIATE_STATE_LIST_GET(sge::renderer::state::source_blend_func::type)
SGE_INSTANTIATE_STATE_LIST_GET(sge::renderer::state::dest_blend_func::type)

#undef SGE_INSTANTIATE_STATE_LIST_GET

#define SGE_INSTANTIATE_STATE_LIST_GET_T(x)\
template x sge::renderer::state::list::get(\
	sge::renderer::state::trampoline<x> const &) const;

SGE_INSTANTIATE_STATE_LIST_GET_T(sge::renderer::state::int_::base_type)
SGE_INSTANTIATE_STATE_LIST_GET_T(sge::renderer::state::bool_::base_type)
SGE_INSTANTIATE_STATE_LIST_GET_T(sge::renderer::state::float_::base_type)
SGE_INSTANTIATE_STATE_LIST_GET_T(sge::renderer::state::color_::base_type)

#undef SGE_INSTANTIATE_STATE_LIST_GET_T
