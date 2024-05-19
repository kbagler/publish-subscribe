#ifndef READER_H
#define READER_H

#include <functional>
#include <memory>

class Reader
{
public:
	using Ptr = std::shared_ptr<Reader>;
	using RequestHandler = std::function<int(const std::string&, unsigned int)>;

	Reader() { }
	Reader(const Reader&) = delete;
	Reader(Reader&&) = delete;
	Reader& operator=(const Reader&) = delete;
	Reader& operator=(Reader&&) = delete;
	virtual ~Reader() { }

	void register_request_handler(RequestHandler handler)
	{
		request_handler = handler;
	}

protected:
	RequestHandler request_handler = nullptr;

private:

};

#endif /* READER_H */

