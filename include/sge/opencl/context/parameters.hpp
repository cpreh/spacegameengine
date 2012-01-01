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


#ifndef SGE_OPENCL_CONTEXT_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <sge/opencl/context/error_callback.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opencl
{
namespace context
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_OPENCL_SYMBOL explicit
	parameters(
		platform::object &,
		opencl::device::object_ref_sequence const &);

	SGE_OPENCL_SYMBOL opencl::context::parameters &
	error_callback(
		context::error_callback const &);

	SGE_OPENCL_SYMBOL context::parameters &
	share_with(
		renderer::device &);

	SGE_OPENCL_SYMBOL opencl::device::object_ref_sequence const &
	device_refs() const;

	SGE_OPENCL_SYMBOL context::error_callback const &
	error_callback() const;

	SGE_OPENCL_SYMBOL renderer::device *
	shared_renderer() const;

	SGE_OPENCL_SYMBOL platform::object &
	platform() const;
private:
	platform::object &platform_;
	device::object_ref_sequence device_refs_;
	context::error_callback error_callback_;
	renderer::device *shared_renderer_;
};
}
}
}

#endif
