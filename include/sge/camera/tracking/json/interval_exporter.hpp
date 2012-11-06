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


#ifndef SGE_CAMERA_TRACKING_JSON_INTERVAL_EXPORTER_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_JSON_INTERVAL_EXPORTER_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace camera
{
namespace tracking
{
namespace json
{
class interval_exporter
{
FCPPT_NONCOPYABLE(
	interval_exporter);
public:
	SGE_CAMERA_SYMBOL
	interval_exporter(
		sge::camera::base const &,
		sge::camera::update_duration const &,
		boost::filesystem::path const &);

	SGE_CAMERA_SYMBOL
	void
	update();

	SGE_CAMERA_SYMBOL
	~interval_exporter();
private:
	sge::camera::base const &camera_;
	sge::timer::basic<sge::timer::clocks::standard> update_timer_;
	boost::filesystem::path const export_file_path_;
	sge::camera::tracking::keyframe_sequence keyframes_;
};
}
}
}
}

#endif
