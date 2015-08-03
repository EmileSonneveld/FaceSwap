#include "face_feed.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include "tinydir.h"

#include <opencv2/core/utility.hpp>

using namespace std;

face_feed* face_feed::inst = nullptr;

face_feed::face_feed()
{
	face_feed::inst = this;
	m_file_list = generate_filelist(faces_folder);
}

std::string face_feed::GetRandomFacePath()
{
	auto str = string(faces_folder) + m_file_list[(1)%m_file_list.size()];
	std::cout << "Random face: " << str;
	return str;
}

std::vector<string> face_feed::generate_filelist(const char* faces_folder)
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
