#include <vector>
#include <string>

// Find usable faces
class face_feed
{
public:
	face_feed();
	static face_feed * inst;
	std::string GetRandomFacePath();

	
private:
	std::vector<std::string> m_file_list;

	const char * faces_folder = "../photo_heads/";

	std::vector<std::string> generate_filelist(const char* faces_folder);
};
