/*
===========================================================================
ARX FATALIS GPL Source Code
Copyright (C) 1999-2010 Arkane Studios SA, a ZeniMax Media company.

This file is part of the Arx Fatalis GPL Source Code ('Arx Fatalis Source Code'). 

Arx Fatalis Source Code is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Arx Fatalis Source Code is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Arx Fatalis Source Code.  If not, see 
<http://www.gnu.org/licenses/>.

In addition, the Arx Fatalis Source Code is also subject to certain additional terms. You should have received a copy of these 
additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Arx 
Fatalis Source Code. If not, please request a copy in writing from Arkane Studios at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing Arkane Studios, c/o 
ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.
===========================================================================
*/

#include "io/Filesystem.h"

#include "io/FilePath.h"

using std::string;

namespace fs {

bool exists(const path & p) {
	try {
		return fs_boost::exists(p.string());
	} catch(...) {
		return false;
	}
}

bool is_directory(const path & p) {
	try {
		return fs_boost::is_directory(p.string());
	} catch(...) {
		return false;
	}
}

bool is_regular_file(const path & p) {
	try {
		return fs_boost::is_regular_file(p.string());
	} catch(...) {
		return false;
	}
}

std::time_t last_write_time(const path & p) {
	try {
		return fs_boost::last_write_time(p.string());
	} catch(...) {
		return 0;
	}
}

u64 file_size(const path & p) {
	try {
		return fs_boost::file_size(p.string());
	} catch(...) {
		return (u64)-1;
	}
}

bool remove(const path & p) {
	try {
		fs_boost::remove(p.string());
		return true;
	} catch(...) {
		return false;
	}
}

bool remove_all(const path & p) {
	boost::system::error_code ec;
	fs_boost::remove_all(p.string(), ec);
	return !ec;
}

bool create_directory(const path & p) {
	boost::system::error_code ec;
	fs_boost::create_directory(p.string(), ec);
	return !ec;
}

bool create_directories(const path & p) {
	boost::system::error_code ec;
	fs_boost::create_directories(p.string(), ec);
	return !ec;
}

bool copy_file(const path & from_p, const path & to_p) {
	boost::system::error_code ec;
	fs_boost::copy_file(from_p.string(), to_p.string(), ec);
	return !ec;
}

bool rename(const path & old_p, const path & new_p) {
	boost::system::error_code ec;
	fs_boost::rename(old_p.string(), new_p.string(), ec);
	return !ec;
}

char * read_file(const path & p, size_t & size) {
	
	fs_boost::ifstream ifs(p.string(), fs_boost::ifstream::in | fs_boost::ifstream::binary | fs_boost::ifstream::ate);
	if(!ifs.is_open()) {
		return NULL;
	}
	
	size = ifs.tellg();
	
	char * buf = new char[size];
	
	if(ifs.seekg(0).read(buf, size).fail()) {
		delete[] buf;
		return NULL;
	}
	
	return buf;
}

} // namespace fs

std::istream & fread(std::istream & ifs, string & buf) {
	while(ifs.good()) {
		char c = static_cast<char>(ifs.get());
		if(c == '\0') {
			break;
		}
		buf.push_back(c);
	}
	return ifs;
}
