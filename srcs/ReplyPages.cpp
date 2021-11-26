#include "ReplyPages.hpp"

ReplyPages::ReplyPages()
{
	std::string	defaultBody = readFile("defaultPages/default.html");
	_names[100] = "Continue";
	_names[101] = "Switching Protocol"; // unsupported (Precondition Failed)
	_names[102] = "Processing"; // obsoleted
	_names[103] = "Early Hints"; // experemental (removed in final HTTP 1.1)
	_names[200] = "OK";
	_names[201] = "Created";
	_names[202] = "Accepted";
	_names[203] = "Non-Authoritative Information";
	_names[204] = "No Content";
	_names[205] = "Reset Content";
	_names[206] = "Partial Content";
	_names[300] = "Multiple Choice";
	_names[301] = "Moved Permanently";
	_names[302] = "Found";
	_names[303] = "See Other";
	_names[304] = "Not Modified";
	_names[305] = "Use Proxy";
	_names[306] = "Switch Proxy";
	_names[307] = "Temporary Redirect";
	_names[400] = "Bad Request";
	_names[401] = "Unauthorized";
	_names[402] = "Payment Required";
	_names[403] = "Forbidden";
	_names[404] = "Not Found";
	_names[405] = "Method Not Allowed";
	_names[406] = "Not Acceptable";
	_names[407] = "Proxy Authentication Required";
	_names[408] = "Request Timeout";
	_names[409] = "Conflict";
	_names[410] = "Gone";
	_names[411] = "Length Required";
	_names[412] = "Precondition Failed";
	_names[413] = "Request Entity Too Large";
	_names[414] = "Request-URI Too Long";
	_names[415] = "Unsupported Media Type";
	_names[416] = "Requested Range Not Satisfiable";
	_names[417] = "Expectation Failed";
	_names[500] = "Internal Server Error";
	_names[501] = "Not Implemented";
	_names[502] = "Bad Gateway";
	_names[503] = "Service Unavailable";
	_names[504] = "Gateway Timeout";
	_names[505] = "HTTP Version Not Supported";
	_replyBodys[400].body = getDefaultBody(defaultBody, "400 Bad Request");
	_replyBodys[404].body = getDefaultBody(defaultBody, "404 Not Found");
	_replyBodys[405].body = getDefaultBody(defaultBody, "405 Method Not Allowed");
	_replyBodys[406].body = getDefaultBody(defaultBody, "406 Not Acceptable");
	_replyBodys[500].body = getDefaultBody(defaultBody, "500 Internal Server Error");
	_replyBodys[501].body = getDefaultBody(defaultBody, "501 Not Implemented");
	_replyBodys[502].body = getDefaultBody(defaultBody, "502 Bad Gateway");
	_replyBodys[503].body = getDefaultBody(defaultBody, "503 Service Unavailable");
	_replyBodys[504].body = getDefaultBody(defaultBody, "504 Gateway Timeout");
	_replyBodys[505].body = getDefaultBody(defaultBody, "505 HTTP Version Not Supported");
}

std::string	ReplyPages::getDefaultBody(std::string defaultBody, std::string text) const
{
	const std::string	placeholder = "PLACEHOLDER";
	size_t	idx = defaultBody.find(placeholder);
	if (idx == std::string::npos)
		throw "default.html corrupted!";
	defaultBody.replace(idx, placeholder.length(), text);
	idx = defaultBody.find(placeholder);
	if (idx == std::string::npos)
		throw "default.html corrupted!";
	return defaultBody.replace(idx, placeholder.length(), text);
}

ReplyPages::~ReplyPages()
{}

const std::string	ReplyPages::getReply(unsigned short reply) const
{
	std::stringstream	ss;

	try
	{
		ss << "HTTP/1.1 " << reply << " " << _names.at(reply) << std::endl;
	}
	catch(const std::exception& e)
	{
		throw "Wrong reply!";
	}
	try
	{
		_replyBodys.at(reply);
		ss << "Content-Type: " << _replyBodys.at(reply).type << std::endl;
		ss << "Content-Length: " << _replyBodys.at(reply).body.length() << std::endl;
	}
	catch(const std::exception& e)
	{}
	std::map<std::string, std::string>::const_iterator	it = _headers.begin();
	for (; it != _headers.end(); ++it)
		ss << it->first << ": " << it->second << std::endl;
	ss << std::endl;
	try
	{
		ss << _replyBodys.at(reply).body << "\n";
	}
	catch(const std::exception& e)
	{}
	return ss.str();
}

void				ReplyPages::setReplyBodyFromFile(unsigned short reply, const std::string &bodyPath)
{
	try
	{
		_names.at(reply);
	}
	catch(const std::exception& e)
	{
		throw "Wrong reply number!";
	}
	if (bodyPath.find_last_of('.') == std::string::npos)
		throw "Unsupported file!";
	_replyBodys[reply].body = readFile(bodyPath);
	try
	{
		_replyBodys[reply].type = MIME::getType(bodyPath.substr(bodyPath.find_last_of('.') + 1));
	}
	catch(const char *e)
	{
		_replyBodys[reply].type = "text";
	}
}

void				ReplyPages::setReplyBody(unsigned short reply, const std::string &body, const std::string &type)
{
	try
	{
		_names.at(reply);
	}
	catch(const std::exception& e)
	{
		throw "Wrong reply number!";
	}
	_replyBodys[reply].body = body;
	_replyBodys[reply].type = type;
}

void				ReplyPages::setHeader(const std::string &key, const std::string &value)
{
	_headers[key] = value;
}

void				ReplyPages::clearHeaders()
{
	_headers.clear();
}
