#include "Response.hpp"


Response::Response(const std::string & request, const Server & _servers) : \
Request(request), _directoryListingDefult(readFile("defaultPages/directory_listing.html")) {

}

std::string Response::autoIndexOn( void ) {
	DIR * dirp = opendir(_location.c_str());
	if (dirp == 0)
		throw ("400"); //                									????????????
	dirent * dp;
	std::string str = _directoryListingDefult;
	str.replace(str.find("FILE_DIR"), strlen("FILE_DIR"), _location);
	str.replace(str.find("FILE_DIR"), strlen("FILE_DIR"), _location);
	int index = str.find("<hr>") + 4;
	if (_location != "/") {
		std::string tmp = "\n<pre><a href=\"../\">..</a></pre>\n";
		str.insert(index, tmp);
		index += tmp.size();
	}
	while ((dp = readdir(dirp))) {
		
		std::stringstream ss;
		struct stat buff;
		stat(dp->d_name, &buff);
		if (std::string(dp->d_name) != "." && std::string(dp->d_name) != "..") {
			ss << "<pre><a href=\"" << dp->d_name <<  "\">" << dp->d_name;
			if(S_ISDIR(buff.st_mode))
				ss << "/" << std::left << std::setw(51 - std::string(dp->d_name).size()) << "</a>" << std::left << std::setw(40) << "-";
			else
				ss << std::left << std::setw(52 - std::string(dp->d_name).size()) << "</a>" << std::left << std::setw(40) << buff.st_size;
			ss  << asctime(gmtime(&(buff.st_ctime))) << "</pre>";
			str.insert(index, ss.str());
			index += ss.str().size();
		}
	}
	closedir(dirp);
	return str;
}

std::string Response::autoIndexOff( void ) {
	DIR * dirp = opendir(_location.c_str());
	if (dirp == 0)
		throw ("400"); //                									????????????
	return ("");
}

void Response::acceptRanges(const std::string & str) {

}
void Response::age(const std::string & str) {

}
void Response::alternates(const std::string & str) {

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

std::string Response::getResponse ( void ) {
	return (autoIndexOn());
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