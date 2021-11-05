#pragma once

#include <string>
#include <vector>
#include <map>
#include "ReplyPages.hpp"

class Location
{
	protected:
		bool							_autoindex;
		std::string						_root;
		ReplyPages						_errorPages;
		size_t							_bodySize;
		std::vector<std::string>		_allowMethods;
		std::string						_index;
		std::string						_redirection;

	private:
		Location(const Location& copy);
		Location						&operator=(const Location& other);
	public:
		Location();
		virtual ~Location();

		// Getters

		bool							isAutoindex() const;
		const std::string				&getRoot() const;
		const ReplyPages				&getErrorPages() const;
		size_t							getBodySize() const;
		const std::vector<std::string>	&getAllowMethods() const;
		const std::string				&getIndex() const;

		// Other
		
		bool	parseLocation(const std::vector<std::string> &splitedLine);
};
