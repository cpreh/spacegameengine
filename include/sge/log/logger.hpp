#ifndef SGE_LOG_LOGGER_HPP_INCLUDED
#define SGE_LOG_LOGGER_HPP_INCLUDED

namespace sge
{
namespace log
{
/*
class logger : boost::noncopyable {
public:
	typedef std::tr1::reference_wrapper<
		ostream
	> stream_ref;

	typedef std::map<
		log::level::type,
		stream_ref
	> stream_map;

	SGE_SYMBOL logger(
		log::level::type,
		ostream &dest);

	SGE_SYMBOL logger(
		log::level::type,
		stream_map const &);

	SGE_SYMBOL ostream &debug();
	SGE_SYMBOL ostream &info();
	SGE_SYMBOL ostream &warn();
	SGE_SYMBOL ostream &error();

	SGE_SYMBOL void level(
		log::level::type);
	
	SGE_SYMBOL log::level::type level() const;

	SGE_SYMBOL bool has_level(
		log::level::type) const;

	SGE_SYMBOL void stream(
		ostream &);
	
	SGE_SYMBOL void stream(
		log::level::type,
		ostream &);
	
	SGE_SYMBOL void streams(
		stream_map const &);

	SGE_SYMBOL ostream &stream(
		log::level::type);
private:
	ostream &stream_if_level(
		log::level::type);

	log::level::type level_;
	stream_map       streams_;
};
*/
}
}

#endif
