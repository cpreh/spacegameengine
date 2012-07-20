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


#ifndef SGE_MODEL_MANAGER_INSTANCE_OBJECT_HPP_INCLUDED
#define SGE_MODEL_MANAGER_INSTANCE_OBJECT_HPP_INCLUDED

#include <sge/model/manager/symbol.hpp>
#include <sge/model/manager/instance/identifier.hpp>
#include <sge/model/manager/instance/position.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace sge
{
namespace model
{
namespace manager
{
namespace instance
{
class object
{
public:
	SGE_MODEL_MANAGER_SYMBOL
	object(
		sge::model::manager::instance::identifier const &_identifier,
		sge::model::manager::instance::position const &_position);

	SGE_MODEL_MANAGER_SYMBOL
	sge::model::manager::instance::identifier const &
	identifier() const;

	SGE_MODEL_MANAGER_SYMBOL
	sge::model::manager::instance::position const &
	position() const;

	SGE_MODEL_MANAGER_SYMBOL
	~object();
private:
	sge::model::manager::instance::identifier identifier_;
	sge::model::manager::instance::position position_;
};
}
}
}
}

#endif
