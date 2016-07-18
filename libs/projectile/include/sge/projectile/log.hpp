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


#ifndef SGE_PROJECTILE_LOG_HPP_INCLUDED
#define SGE_PROJECTILE_LOG_HPP_INCLUDED

#include <sge/projectile/log_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace sge
{
namespace projectile
{

class log
{
	FCPPT_NONCOPYABLE(
		log
	);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	explicit
	log(
		fcppt::log::context &
	);

	SGE_PROJECTILE_DETAIL_SYMBOL
	~log();

	fcppt::log::object &
	world_log() const;

	fcppt::log::object &
	body_log() const;

	fcppt::log::object &
	ghost_log() const;

	fcppt::log::object &
	triangle_log() const;
private:
	mutable fcppt::log::object world_log_;

	mutable fcppt::log::object body_log_;

	mutable fcppt::log::object ghost_log_;

	mutable fcppt::log::object triangle_log_;
};

}
}

#endif
