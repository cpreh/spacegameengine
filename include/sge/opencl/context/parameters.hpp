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


#ifndef SGE_OPENCL_CONTEXT_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/context/error_callback.hpp>
#include <sge/opencl/context/parameters_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional.hpp>


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
	typedef
	fcppt::optional<renderer::device::core &>
	optional_renderer;

	SGE_OPENCL_DETAIL_SYMBOL
	parameters(
		platform::object &,
		opencl::device::object_ref_sequence const &);

	SGE_OPENCL_DETAIL_SYMBOL
	parameters(
		parameters const &);

	SGE_OPENCL_DETAIL_SYMBOL
	~parameters();

	SGE_OPENCL_DETAIL_SYMBOL opencl::context::parameters &
	error_callback(
		context::error_callback const &);

	SGE_OPENCL_DETAIL_SYMBOL context::parameters &
	share_with(
		renderer::device::core &);

	SGE_OPENCL_DETAIL_SYMBOL opencl::device::object_ref_sequence const &
	device_refs() const;

	SGE_OPENCL_DETAIL_SYMBOL context::error_callback const &
	error_callback() const;

	SGE_OPENCL_DETAIL_SYMBOL optional_renderer const &
	shared_renderer() const;

	SGE_OPENCL_DETAIL_SYMBOL platform::object &
	platform() const;
private:
	platform::object &platform_;
	device::object_ref_sequence device_refs_;
	context::error_callback error_callback_;
	optional_renderer shared_renderer_;
};
}
}
}

#endif
