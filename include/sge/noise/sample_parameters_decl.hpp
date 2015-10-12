/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_NOISE_SAMPLE_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_NOISE_SAMPLE_PARAMETERS_DECL_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace noise
{

template<
	typename Noise
>
class sample_parameters
{
FCPPT_NONASSIGNABLE(
	sample_parameters);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		typename Noise::vector_type,
		position_type);

	FCPPT_MAKE_STRONG_TYPEDEF(
		typename Noise::value_type,
		amplitude_type);

	FCPPT_MAKE_STRONG_TYPEDEF(
		typename Noise::value_type,
		frequency_type);

	FCPPT_MAKE_STRONG_TYPEDEF(
		unsigned,
		octaves_type);

	sample_parameters(
		position_type const &,
		amplitude_type const &,
		frequency_type const &,
		octaves_type const &);

	position_type
	position() const;

	frequency_type
	frequency() const;

	amplitude_type
	amplitude() const;

	octaves_type
	octaves() const;
private:
	position_type const &position_;
	amplitude_type const &amplitude_;
	frequency_type const &frequency_;
	octaves_type const octaves_;
};

}
}

#endif
