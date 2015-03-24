#include "svg_image.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include "tinydir.h"

using namespace std;


svg_image::svg_image() : m_rect()
{
	m_file_list = generate_filelist(faces_folder);
	m_template_string = file_to_string(template_file);
}


void svg_image::refresh()
{
	m_rect = cv::Rect();
}


std::string svg_image::get_resulting_svg()
{
	string output = m_template_string;
	replace_var(output, "$x"     , std::to_string(m_rect.y     -2));
	replace_var(output, "$y"     , std::to_string(m_rect.x     -2));
	replace_var(output, "$width" , std::to_string(m_rect.width +4));
	replace_var(output, "$height", std::to_string(m_rect.height+4));
	// and choose random image
	replace_var(output, "$image"  , string(faces_folder) + m_file_list[(4945+m_rect.x)%m_file_list.size()]);
	return output;
}


bool replace_var(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if(start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	replace_var(str, from, to); // recursive
	return true;
}


std::string file_to_string(const char * template_file)
{
	std::ifstream t( template_file );
	std::string str((std::istreambuf_iterator<char>(t)),
    	             std::istreambuf_iterator<char>());
	return str;
}

std::vector<string> svg_image::generate_filelist(const char* faces_folder)
{
	std::vector<string> file_list;
	tinydir_dir dir;
	if (tinydir_open(&dir, faces_folder) == -1)
	{
		std::cerr << "Error opening folder: " << faces_folder;
		goto bail;
	}
	while (dir.has_next)
	{
		tinydir_file file;
		if (tinydir_readfile(&dir, &file) == -1)
		{
			std::cerr << "Error getting file";
			goto bail;
		}

		if (!file.is_dir)
		{
			file_list.push_back(file.name);
			//printf("%s\n", file.name);
		}
		tinydir_next(&dir);
	}
	bail:
	tinydir_close(&dir);
	return file_list;
}
