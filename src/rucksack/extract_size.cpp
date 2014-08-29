#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/src/rucksack/extract_size.hpp>
#include <fcppt/variant/apply_unary.hpp>


sge::rucksack::scalar
sge::rucksack::extract_size(
	sge::rucksack::axis_policy const &_policy
)
{
	struct extract_visitor
	{
		typedef
		sge::rucksack::scalar
		result_type;

		result_type
		operator()(
			sge::rucksack::minimum_size const _pol
		) const
		{
			return
				_pol.get();
		}

		result_type
		operator()(
			sge::rucksack::preferred_size const _pol
		) const
		{
			return
				_pol.get();
		}
	};

	return
		fcppt::variant::apply_unary(
			extract_visitor(),
			_policy
		);
}
