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
		std::string _directoryListing;		
	public:
		Responce(const std::string & request) : Request(request), _directoryListingDefult(readFile("../directory_listing.html"))
		{

		}

		void AutoIndexOn() {
			DIR *dirp = opendir(_location.c_str());
			dirent * dp;
			std::string str = _directoryListingDefult;
			str.replace(str.find("FILE_DIR"), strlen("FILE_DIR"), _location);
			str.replace(str.find("FILE_DIR"), strlen("FILE_DIR"), _location);

			int index = _directoryListingDefult.find("<hr>");
			index += 2;
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
				 	if(S_ISDIR(buff.st_mode)) {
						ss << "/";
						ss << std::left << std::setw(51 - std::string(dp->d_name).size()) << "</a>";
						ss << std::left << std::setw(40) << "-";

					}
					else {
						ss << std::left << std::setw(52 - std::string(dp->d_name).size()) << "</a>";
						ss << std::left << std::setw(40) << buff.st_size;
					}
					ss  << asctime(gmtime(&(buff.st_ctime)));
					ss << "</pre>\n";
					std::string tmp = ss.str();
					str.insert(index, tmp);
					index += tmp.size();
				}
			}
			closedir(dirp);
			std::fstream ss1("file.html", std::ios::out);
			ss1 << str;
			std::cout << str << std::endl;
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