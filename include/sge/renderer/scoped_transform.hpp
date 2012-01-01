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


#ifndef SGE_RENDERER_SCOPED_TRANSFORM_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_TRANSFORM_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief A scoped transform block
 *
 * This class sets a new matrix for a given matrix mode in the constructor and
 * resets the matrix to the identity in the destructor.
*/
class scoped_transform
{
	FCPPT_NONCOPYABLE(
		scoped_transform
	);
public:
	/**
	 * \brief Sets a new matrix
	 *
	 * Sets \a matrix for \a mode and \a device.
	 *
	 * \param device The device to set the matrix for
	 *
	 * \param mode The matrix mode to set the matrix for
	 *
	 * \param matrix The matrix to set
	*/
	SGE_RENDERER_SYMBOL
	scoped_transform(
		renderer::device &device,
		renderer::matrix_mode::type mode,
		renderer::matrix4 const &matrix
	);

	/**
	 * \brief Resets the matrix of the given matrix mode to the identity
	*/
	SGE_RENDERER_SYMBOL
	~scoped_transform();
private:
	renderer::device &device_;

	renderer::matrix_mode::type const mode_;
};

}
}

#endif
