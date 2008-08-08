/*
#include <sge/log/logger.hpp>
#include <boost/foreach.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/null.hpp>

namespace
{

boost::iostreams::stream_buffer<
	boost::iostreams::basic_null_sink<
		sge::ostream::char_type
	>
> null_sink;

sge::ostream null_stream(&null_sink);

}

sge::log::logger::logger(
	log::level::type const level_,
	ostream &dest)
: level_(level_)
{
	stream(dest);
}

sge::log::logger::logger(
	log::level::type const level_,
	stream_map const &streams_)
: level_(level_),
  streams_(streams_)
{}

sge::ostream &sge::log::logger::debug()
{
	return stream_if_level(log::level::debug);
}

sge::ostream &sge::log::logger::info()
{
	return stream_if_level(log::level::info);
}

sge::ostream &sge::log::logger::warn()
{
	return stream_if_level(log::level::warn);
}

sge::ostream &sge::log::logger::error()
{
	return stream_if_level(log::level::error);
}

void sge::log::logger::level(
	log::level::type const nlevel)
{
	level_ = nlevel;
}

sge::log::level::type
sge::log::logger::level() const
{
	return level_;
}

bool sge::log::logger::has_level(
	log::level::type const l) const
{
	return level() <= l;  
}

void sge::log::logger::stream(
	ostream &dest)
{
	// TODO: use a for_each_enum function here!
	streams_.clear();
	for(unsigned i = 0; i < log::level::size; ++i)
		stream(
			static_cast<log::level::type>(
				i),
			std::tr1::ref(dest));
}

void sge::log::logger::stream(
	log::level::type const l,
	ostream &s)
{
	streams_.erase(l);
	streams_.insert(
		std::make_pair(
			l,
			std::tr1::ref(s)));
}

void sge::log::logger::streams(
	stream_map const &a)
{
	streams_ = a;
}

sge::ostream &
sge::log::logger::stream(
	log::level::type const l)
{
	return stream_if_level(l); 
}

sge::ostream &sge::log::logger::stream_if_level(
	log::level::type const l)
{
	stream_map::iterator const it(streams_.find(l));
	return it != streams_.end() && has_level(l)
		? it->second
		: null_stream;
}
*/
