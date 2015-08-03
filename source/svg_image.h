#include <opencv2/core/utility.hpp>

#include <vector>
#include <string>

// Create this object one and reuse often (could berhaps be singleton?)
class svg_image
{
public:
	svg_image();

	void refresh();
	std::string get_resulting_svg();
	void set_rect(cv::Rect& rect)
	{
		m_rect = rect;
	}

	
private:
	std::vector<std::string> m_file_list;
	std::string m_template_string;
	cv::Rect m_rect;

	const char * template_file = "./img-template.xml";
	const char * faces_folder = "../photo_heads/";

	std::vector<std::string> generate_filelist(const char* faces_folder);
};

std::string file_to_string(const char * template_file);
bool replace_var(std::string& str, const std::string& from, const std::string& to);
