//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_UNSET_ONE_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_UNSET_ONE_HPP_INCLUDED

#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/detail/options_class.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/tag.hpp>
#include <fcppt/record/get.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
class unset_one
{
public:
	typedef
	sge::sprite::state::detail::options_class<
		StateChoices
	>
	options_class;

	typedef
	sge::sprite::state::render_context<
		StateChoices
	>
	render_context;

	unset_one(
		render_context &_render_context,
		options_class const &_options
	)
	:
		render_context_(
			_render_context
		),
		options_(
			_options
		)
	{
	}

	typedef void result_type;

	template<
		typename Type
	>
	result_type
	operator()(
		fcppt::tag<
			Type
		>
	) const
	{
		if(
			fcppt::record::get<
				typename Type::role
			>(
				options_.get()
			)
		)
			Type::unset(
				render_context_.get()
			);
	}
private:
	fcppt::reference<
		render_context
	> render_context_;

	fcppt::reference<
		options_class const
	> options_;
};

}
}
}
}

#endif
