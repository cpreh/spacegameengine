//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_WRAPPED_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_WRAPPED_WINDOW_HPP_INCLUDED

#include <sge/systems/wrapped_window_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <awl/system/reference.hpp>
#include <awl/window/reference.hpp>


namespace sge
{
namespace systems
{

class wrapped_window
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	wrapped_window(
		awl::system::reference,
		awl::window::reference
	);

	awl::system::reference
	awl_system() const;

	awl::window::reference
	awl_window() const;
private:
	awl::system::reference awl_system_;

	awl::window::reference awl_window_;
};

}
}

#endif
