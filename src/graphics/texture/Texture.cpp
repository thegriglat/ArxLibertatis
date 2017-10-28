/*
 * Copyright 2011-2015 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Arx Libertatis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arx Libertatis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arx Libertatis.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "graphics/texture/Texture.h"

#include "core/Config.h"

bool Texture::Init(const res::path & strFileName, TextureFlags newFlags) {
	
	m_filename = strFileName;
	flags = newFlags;
	
	return Restore();
}

bool Texture::Init(const Image & pImage, TextureFlags newFlags) {
	
	m_filename.clear();
	mImage = pImage;
	flags = newFlags;
	
	return Restore();
}

bool Texture::Init(unsigned int pWidth, unsigned int pHeight, Image::Format pFormat) {
	
	m_filename.clear();
	
	size = Vec2i(pWidth, pHeight);
	mImage.create(pWidth, pHeight, pFormat);
	m_format = pFormat;
	flags = 0;
	
	return Create();
}

bool Texture::Restore() {
	
	bool bRestored = false;
	
	if(!getFileName().empty()) {
		
		mImage.load(getFileName());
		
		if((flags & ApplyColorKey) && !mImage.hasAlpha()) {
			mImage.applyColorKeyToAlpha(Color::black, config.video.colorkeyAntialiasing);
		}
		
		if(flags & Intensity) {
			mImage.toGrayscale();
		}
		
	}
	
	if(mImage.isValid()) {
		m_format = mImage.getFormat();
		size = Vec2i(mImage.getWidth(), mImage.getHeight());
		
		Destroy();
		bool bCreated = Create();
		if(!bCreated) {
			return false;
		}
		
		Upload();
		
		bRestored = true;
	}
	
	if(!getFileName().empty()) {
		mImage.reset();
	}
	
	return bRestored;
}
