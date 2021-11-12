#include "Response.hpp"


Response::Response(const std::string & request, Server * server) : Request(request), \
_conectionClose(false), _directoryListingDefult(readFile("defaultPages/directory_listing.html")), _server(server) {
	_locationConfig = _server->getLocation(_path);
	_locationConfig->clearHeaders();
	_oldPath = _path;
	_path = _locationConfig->getPath(_path);
	if (_errorFlag == 200)
	{
		try {
			const std::vector<std::string> tmp_vec = _locationConfig->getAllowMethods();
			if (std::find(tmp_vec.begin(), tmp_vec.end(), _response) == tmp_vec.end())
				throw("405:response");
			if (_response == "GET")
				responseGet();	
			else if (_response == "POST")
				responsePost();
		}
		catch (const char *str) {
			_errorFlag = atoi(str);
		}
	}
}

std::string Response::autoIndexOn( void ) {
	DIR * dirp = opendir(_path.c_str());
	if (dirp == 0)
		return (""); //                									????????????
	dirent * dp;
	std::string str = _directoryListingDefult;
	str.replace(str.find("FILE_DIR"), strlen("FILE_DIR"), _oldPath);
	str.replace(str.find("FILE_DIR"), strlen("FILE_DIR"), _oldPath);
	int index = str.find("<hr>") + 4;
	if (_oldPath != "/") {
		std::string tmp = "\n<pre><a href=\"../\">../</a></pre>\n";
		str.insert(index, tmp);
		index += tmp.size();
	}
	while ((dp = readdir(dirp))) {
		
		std::stringstream ss;
		struct stat buff;
		stat((_path + dp->d_name).c_str(), &buff);
		if (std::string(dp->d_name) != "." && std::string(dp->d_name) != "..") {
			 
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

std::string Response::autoIndexOff( void ) {
	return (readFile(_path));
}


void Response::responseGet() {
	struct stat buff;
	stat((_path).c_str(), &buff);
	if (_locationConfig->isAutoindex() && S_ISDIR(buff.st_mode)) {
		_locationConfig = _server->getLocation(_path);
		_locationConfig->setReplyBody(200,  autoIndexOn(), "text/html");
	}
	else
			_locationConfig->setReplyBodyFromFile(200, _path);
}

std::string Response::postDone ( void ) {
	std::string str (readFile(_locationConfig->getPath("/index.html")));
	int a = str.find("<form action=\"\" method=\"post\">");
	int b = str.find_last_of("<input type=\"submit\" value=\"Save\"></form>");
	str.erase(a, b);
	str.insert(a, "User: " + _dataBaseMap["name"] );
	return (str);


}
void Response::responsePost() {


	_locationConfig->setReplyBody(200,  postDone(), "text/html");
}

void Response::responseDelete() {
	
}


void Response::acceptRanges(const std::string & str) {
	(void)str;
}
void Response::age(const std::string & str) {
	(void)str;
}
void Response::alternates(const std::string & str) {
	(void)str;
}
void Response::contentDisposition () {

}
void Response::eTag() {

}
void Response::location() {

}
void Response::publicR(void) { 

}
void Response::retryAfter () {

}
void Response::server () {

}
void Response::vary() {

}

bool	Response::getConectionClose( void ) {
	return _conectionClose;
}

std::string Response::getResponse( void ) {
	if (_errorFlag == 400)
	{
		_conectionClose = true;
		_locationConfig->setHeader("Connection", "close");
	}
	return (_locationConfig->getReply(_errorFlag));
}



// int main() {
	
// 	try {
// 	Response a("GET . HTTP/1.1");
// 	a.AutoIndexOn();
// 	}
// 	catch (std::string ex) {
// 		std::cout << ex << std::endl;
// 	}
// 	catch (const char *ex) {
// 		std::cout << ex << std::endl;
// 	}
// 	// std::cout << str << std::endl;
// 	return 0;    
// }