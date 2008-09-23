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


#include <sge/renderer/state/any_compare.hpp>
#include <sge/renderer/state/var.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <typeinfo>

namespace
{

struct compare : boost::static_visitor<bool> {
	compare(
		sge::renderer::state::any const &a,
		sge::renderer::state::any const &b);
		
	template<typename T>
	bool operator()(
		sge::renderer::state::var<T> const &) const;

	template<typename T>
	bool operator()(
		T) const;
private:
	sge::renderer::state::any const &a, &b;
};

}

bool sge::renderer::state::any_compare::operator()(
	any const &a,
	any const &b) const
{
	return a.type() == b.type()
		? boost::apply_visitor(
			compare(a, b),
			a)
		: a.type().before(b.type());
}

namespace
{

compare::compare(
	sge::renderer::state::any const &a,
	sge::renderer::state::any const &b)
: a(a),
  b(b)
{}
		
template<typename T>
bool compare::operator()(
	sge::renderer::state::var<T> const &) const
{
	typedef sge::renderer::state::var<T> type;
	return boost::get<type>(a).state()
	     < boost::get<type>(b).state();
}

template<typename T>
bool compare::operator()(
	T) const
{
	return false; 
}

}
