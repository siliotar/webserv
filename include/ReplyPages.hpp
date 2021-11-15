#pragma once

#include <string>
#include <map>
#include <sstream>
#include "utils.hpp"

class MIME;

typedef struct s_body
{
	s_body() : type("text/html") {}
	std::string	body;
	std::string	type;
} t_body;

class ReplyPages
{
	private:
		std::map<unsigned short, std::string>	_names;
		std::map<unsigned short, t_body>		_replyBodys;
		std::map<std::string, std::string>		_headers;

		ReplyPages(const ReplyPages& copy);
		ReplyPages	&operator=(const ReplyPages& other);

		std::string				getDefaultBody(std::string defaultBody, std::string text) const;
	public:
		ReplyPages();
		virtual ~ReplyPages();

		const std::string		getReply(unsigned short reply) const;

		void					setReplyBodyFromFile(unsigned short reply, const std::string &bodyPath);
		void					setReplyBody(unsigned short reply, const std::string &body, const std::string &type = "text");
		void					setHeader(const std::string &key, const std::string &value);

		void					clearHeaders();
};

#include "MIME.hpp"
