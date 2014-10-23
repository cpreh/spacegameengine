/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_STATE_FFP_ALPHA_TEST_ENABLED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_ALPHA_TEST_ENABLED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/alpha_test/enabled_fwd.hpp>
#include <sge/renderer/state/ffp/alpha_test/func.hpp>
#include <sge/renderer/state/ffp/alpha_test/ref.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace alpha_test
{

class enabled
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	enabled(
		sge::renderer::state::ffp::alpha_test::func,
		sge::renderer::state::ffp::alpha_test::ref
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::alpha_test::func
	func() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::alpha_test::ref const
	ref() const;
private:
	sge::renderer::state::ffp::alpha_test::func func_;

	sge::renderer::state::ffp::alpha_test::ref ref_;
};

}
}
}
}
}

#endif
