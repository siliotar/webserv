#include "Response.hpp"


// delete
std::string	readFile(const std::string &path)
{
	std::ifstream		fin(path.c_str());
	std::string			line;
	std::stringstream	ss;

	if (!fin.is_open())
		throw "Failed to open file!";
	while (std::getline(fin, line))
		ss << line << std::endl;
	return (ss.str());
}
// delete

class Responce : public Request {

	private:
		const std::string _directoryListingDefult;
	public:
		Responce(const std::string & request) : Request(request), _directoryListingDefult(readFile("defaultPages/directory_listing.html"))
		{

		}
		// If autoindex on, open directory in html 
		std::string AutoIndexOn( void ) {
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
		std::string AutoIndexOff( void ) {
			DIR * dirp = opendir(_location.c_str());
			if (dirp == 0)
				throw ("400"); //                									????????????
			return ("");
		}
		void AcceptRanges(const std::string & str) {

		}
		void Age(const std::string & str) {

		}
		void Alternates(const std::string & str) {

		}
		void ContentDisposition () {

		}
		void ETag() {

		}
		void Location() {

		}
		void Public(void) { 

		}
		void RetryAfter () {

		}
		void Server () {

		}
		void Vary() {

		}
};

int main() {
	
	try {
	Responce a("GET . HTTP/1.1");
	a.AutoIndexOn();
	}
	catch (std::string ex) {
		std::cout << ex << std::endl;
	}
	catch (const char *ex) {
		std::cout << ex << std::endl;
	}
	// std::cout << str << std::endl;
	return 0;    
}