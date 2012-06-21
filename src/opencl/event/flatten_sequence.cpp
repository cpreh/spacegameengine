#include <sge/src/opencl/event/flatten_sequence.hpp>

fcppt::container::raw_vector<cl_event> const
sge::opencl::event::flatten_sequence(
	sge::opencl::event::sequence const &_event_sequence)
{
	fcppt::container::raw_vector<cl_event> result;
	for(
		sge::opencl::event::sequence::const_iterator it =
			_event_sequence.begin();
		it != _event_sequence.end();
		++it)
		result.push_back(
			it->handle());
	return result;
}
