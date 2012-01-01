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


#ifndef SGE_RENDERER_SCOPED_BLOCK_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_BLOCK_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief A scoped rendering block
 *
 * This class calls device::begin_rendering in the constructor an
 * device::end_rendering in the destructor.
*/
class scoped_block
{
	FCPPT_NONCOPYABLE(
		scoped_block
	);
public:
	/**
	 * \brief Calls device::begin_rendering
	 *
	 * Calls \c device.begin_rendering()
	 *
	 * \param device The device to begin rendering for
	 *
	 * \warning The behaviour is undefined if device::begin_rendering has
	 * already been called before a call to device::end_rendering.
	*/
	SGE_RENDERER_SYMBOL
	explicit scoped_block(
		renderer::device &device
	);

	/**
	 * \brief Calls device::end_rendering
	 *
	 * \warning The behaviour is undefined if device::end_rending was
	 * already called.
	*/
	SGE_RENDERER_SYMBOL
	~scoped_block();
private:
	renderer::device &rend_;
};

}
}

#endif
