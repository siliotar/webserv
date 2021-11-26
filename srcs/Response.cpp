#include "Response.hpp"


Response::Response(const std::string & request, Server * server) : Request(request, server), \
_conectionClose(false), _directoryListingDefult(readFile("defaultPages/directory_listing.html")) 
{
	
	
	_locationConfig->clearHeaders();
	_oldPath = _path;
	_path = _locationConfig->getPath(_path);
	std::string tmp = _path;
	if (_path.find("?") != std::string::npos)
	{
		_path.erase(_path.find("?"));
		_oldPath.erase(_oldPath.find("?"));

	}
	if (_locationConfig->getRedirection().size() > 0)
	{
		_locationConfig->setHeader("Location", _locationConfig->getRedirection());
		_errorFlag = 301;
	}
	if (_errorFlag == 200)
	{
		try 
		{
			const std::vector<std::string> tmp_vec = _locationConfig->getAllowMethods();
			if (std::find(tmp_vec.begin(), tmp_vec.end(), _response) == tmp_vec.end())
				throw("405:response");
			if (_response == "GET")
			{
				// cgi();
				responseGet();
			}
			else if (_response == "POST")
			{
				responsePost();
				// cgi();
			}
			else if (_response == "DELETE")
				responseDelete();
		}
		catch (const char *str) 
		{
			_errorFlag = atoi(str);
		}
	}
}

std::string Response::autoIndexOn( void )
{
	DIR * dirp = opendir(_path.c_str());
	if (dirp == 0)
		return ("400::autoindexOn");
	dirent * dp;
	std::string str = _directoryListingDefult;
	str.replace(str.find("FILE_DIR"), strlen("FILE_DIR"), _oldPath);
	str.replace(str.find("FILE_DIR"), strlen("FILE_DIR"), _oldPath);
	int index = str.find("<hr>") + 4;
	if (_oldPath != "/") 
	{
		std::string tmp = "\n<pre><a href=\"../\">../</a></pre>\n";
		str.insert(index, tmp);
		index += tmp.size();
	}
	while ((dp = readdir(dirp)))
	{
		
		std::stringstream ss;
		struct stat buff;
		stat((_path + dp->d_name).c_str(), &buff);
		if (std::string(dp->d_name) != "." && std::string(dp->d_name) != "..") 
		{
			 
			if(S_ISDIR(buff.st_mode))
				ss << "<pre><a href=\"" << dp->d_name <<  "/\">" << dp->d_name \
				<< "/" << std::left << std::setw(51 - std::string(dp->d_name).size()) \
				<< "</a>" << std::left << std::setw(40) << "-";
			else
				ss << "<pre><a href=\"" << dp->d_name <<  "\">" << dp->d_name \
				<< std::left << std::setw(52 - std::string(dp->d_name).size()) \
				<< "</a>" << std::left << std::setw(40) << buff.st_size;
			ss  << asctime(gmtime(&(buff.st_ctime))) << "</pre>";
			str.insert(index, ss.str());
			index += ss.str().size();
		}
	}
	closedir(dirp);
	return str;
}

void Response::autoIndexOff(struct stat & buff)
{

	std::string	index = _path;
	if (index[index.size() - 1] != '/')
		index += "/";
	index += _locationConfig->getIndex();
	if (stat(index.c_str(), &buff) < 0)
		throw "404";
	_locationConfig->setReplyBodyFromFile(200, index);
}


void Response::responseGet()
{
	struct stat buff;
	if (stat(_path.c_str(), &buff) < 0)
		throw "404";
	if (_locationConfig->isAutoindex() && S_ISDIR(buff.st_mode)) 
	{
		_locationConfig = _server->getLocation(_path);
		_locationConfig->setReplyBody(200,  autoIndexOn(), "text/html");
	}
	else
	{
		if (!S_ISDIR(buff.st_mode))
			_locationConfig->setReplyBodyFromFile(200, _path);
		else
			autoIndexOff(buff);
	}
}

void Response::responsePost()
{
	struct stat buff;
	if (stat(_path.c_str(), &buff) < 0)
	{
		std::cout << _postResponse << std::endl;
		std::ofstream outfile(_path.c_str());
		outfile << _postResponse;
	}
	if (S_ISREG(buff.st_mode))
		_locationConfig->setReplyBody(200, readFile(_path), "text/html");
	else
		autoIndexOff(buff);
}

bool	Response::getConectionClose( void )
{
	return _conectionClose;
}
void Response::responseDelete( void )
{
	if (remove(_path.c_str()) < 0)
		throw ("404::DELETE");
}

std::string Response::getResponse( void )
{
	if (_errorFlag == 400)
	{
		_conectionClose = true;
		_locationConfig->setHeader("Connection", "close");
	}
	else
		_locationConfig->setHeader("Connection", "keep-alive");
	if (!_cookieData.empty())
	{
		for(size_t i = 0; i < _cookieData.size(); ++i)
			_locationConfig->setHeader("Set-Cookie", _cookieData[i]);
	}
	return (_locationConfig->getReply(_errorFlag));
}


std::string Response::cgi( void )
{


	std::vector<std::string> vectorString;

	vectorString.push_back("SERVER_SOFTWARE=BATYANDDED");
	vectorString.push_back("SERVER_PROTOCOL=HTTP/1.1");
	vectorString.push_back("GATEWAY_INTERFACE:=CGI/1.1");
	vectorString.push_back("SERVER_NAME=" + _host);
	vectorString.push_back("SERVER_PORT=" + _port);
	vectorString.push_back("REQUEST_METHOD=" + _response);
	vectorString.push_back("PATH_TRANSLATED=" + _path);
	// vectorString.push_back("SCRIPT_NAME=/www/cgi_tester");
	// vectorString.push_back("QUERY_STRING=" + _postResponse);
	vectorString.push_back("REMOTE_HOST=" + _host);
	vectorString.push_back("REMOTE_ADDR=127.0.0.1");
	if (_response == "POST")
	{	
		vectorString.push_back("CONTENT_TYPE=" + _postContentType);
		vectorString.push_back("CONTENT_LENGTH=" + _postContentLength);
		std::cout << _postContentLength << std::endl;
	}
	vectorString.push_back("PATH_INFO=/www/cgi_tester");

	sort(vectorString.begin(), vectorString.end());

	char **envp = new char *[vectorString.size() + 1];
	for (size_t i = 0; i < vectorString.size(); i++)
		envp[i] = strdup(vectorString[i].c_str());

	envp[vectorString.size()] = 0;

	pid_t pid;
	int fd[2];
	int fd_2[2];
	pipe(fd);
	int old_fd0 = dup(0);
	int old_fd1 = dup(1);
	
	for (size_t i = 0; i < _cgiArg.size(); i++)
	{
		pipe(fd_2);
		if (i == 0)
		{
			write(fd[1], _postResponse.c_str(), _postResponse.size());
			close(fd[1]);
		}
		pid = fork();
		if (pid == 0)
		{	
			 char *const * a = 0;
			if (dup2(fd_2[1], 1) < 0)
				write(2, "123\n", 4);
			if (dup2(fd[0], 0))
				write(2, "abcd\n", 4);
			if (execve(_cgiArg[i].c_str(), a, envp) < 0)
				throw("404::cgi");
			exit(0);
		}
		wait(0);
		close(fd_2[1]);
		close(fd[0]);
		fd[0] = fd_2[0];
		fd[1] = fd_2[1];
		close(fd[1]);
	}
	dup2(old_fd1, 1);
	dup2(old_fd0, 0);
	close(fd[1]);
	char *str;
	_postResponse = "";
	while (c_get_next_line(fd[0], &str))
	{
		_postResponse += str;
		_postResponse += "\n";
		free(str);
	}
	close(fd[0]);
	_postResponse += str;
	free(str);
	delete [] envp;
	return  ("");
}
Response::~Response() { }

