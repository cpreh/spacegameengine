//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DEVICE_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_DEVICE_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/window/object_ref.hpp>


namespace sge
{
namespace renderer
{
namespace device
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::display_mode::parameters,
		sge::window::object_ref
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::display_mode::parameters const &
	display_mode() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::window::object_ref
	window() const;
private:
	sge::renderer::display_mode::parameters display_mode_;

	sge::window::object_ref window_;
};

}
}
}

#endif
