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


#ifndef SGE_RENDERER_SCOPED_TARGET_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_TARGET_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/target_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief A scoped target block
 *
 * This class sets a new target in the constructor and resets to the onscreen
 * target in the destructor.
*/
class scoped_target
{
	FCPPT_NONCOPYABLE(
		scoped_target
	);
public:
	/**
	 * \brief Sets a new render target
	 *
	 * Sets \a target for \a device
	 *
	 * \param device The device to set the target for
	 *
	 * \param target The target to set
	*/
	SGE_RENDERER_SYMBOL
	scoped_target(
		renderer::device &device,
		renderer::target &target
	);

	/**
	 * \brief Resets to the onscreen target
	*/
	SGE_RENDERER_SYMBOL
	~scoped_target();
private:
	renderer::device &rend_;
};

}
}

#endif
