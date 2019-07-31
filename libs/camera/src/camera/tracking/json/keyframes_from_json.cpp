//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/tracking/json/keyframe_from_json.hpp>
#include <sge/camera/tracking/json/keyframes_from_json.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/algorithm/map.hpp>


sge::camera::tracking::keyframe_sequence
sge::camera::tracking::json::keyframes_from_json(
	sge::parse::json::array const &_array
)
{
	return
		fcppt::algorithm::map<
			sge::camera::tracking::keyframe_sequence
		>(
			_array.elements,
			[](
				fcppt::recursive<
					sge::parse::json::value
				> const &_value
			)
			{
				return
					sge::camera::tracking::json::keyframe_from_json(
						sge::parse::json::get_exn<
							sge::parse::json::object const
						>(
							_value.get()
						)
					);
			}
		);
}
