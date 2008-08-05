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


#include <sge/sprite/texture_animation.hpp>
#include <sge/sprite/object.hpp>
#include <sge/time/resolution.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <boost/next_prior.hpp>

sge::sprite::texture_animation::texture_animation(
	animation_series const &series_,
	loop_method::type const action,
	object &spr,
	time::fun const &time_function)
: series(series_),
  action(action),
  cur_timer(
  	time::resolution(
		0),
	true,
	time_function),
  spr(spr),
  pos(series.begin())
{
	if(series.empty())
		throw exception(
			SGE_TEXT("texture_animation series is empty!"));
	reset();
}

bool sge::sprite::texture_animation::process()
{
	if(!cur_timer.expired())
		return false;

	if(boost::next(pos) == series.end())
	{
		switch(action) {
		case loop_method::repeat:
			reset();
		case loop_method::stop_at_end:
			return true;
		default:
			throw exception(
				SGE_TEXT("Invalid loop_method!"));
		}
	}

	++pos;

	cur_timer.interval(
		time::resolution(
			pos->delay()));
	spr.set_texture(pos->tex());

	return false;
}

void sge::sprite::texture_animation::reset()
{
	spr.set_texture(series.begin()->tex());
	pos = series.begin();
	cur_timer.interval(
		time::resolution(
			series.begin()->delay()));
}

const sge::renderer::texture::dim_type
sge::sprite::texture_animation::dim() const
{
	return series.dim();
}
