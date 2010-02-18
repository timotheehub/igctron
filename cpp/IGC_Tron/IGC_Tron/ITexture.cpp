/**************************************************************************/
/* This file is part of IGC Tron                                          */
/* (c) IGC Software 2009 - 2010                                           */
/* Author : Pierre-Yves GATOUILLAT                                        */
/**************************************************************************/
/* This program is free software: you can redistribute it and/or modify   */
/* it under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                    */
/*                                                                        */
/* This program is distributed in the hope that it will be useful,        */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/* GNU General Public License for more details.                           */
/*                                                                        */
/* You should have received a copy of the GNU General Public License      */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>.  */
/**************************************************************************/

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "png.h"

#include "ITexture.h"

/***********************************************************************************/
/** DEBUG                                                                         **/
/***********************************************************************************/

#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************************/

namespace IGC
{

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	ITexture::ITexture( Engine* _engine )
	{
		engine = _engine;

		renderer = engine->getRenderer();

		data = NULL;

		dirty = true;
	}

	ITexture::~ITexture()
	{
		if ( data ) free( data );
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	Engine* ITexture::getEngine()
	{
		return engine;
	}

	IRenderer* ITexture::getRenderer()
	{
		return renderer;
	}

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

	int ITexture::getPixelSize()
	{
		if ( format == FORMAT_L8 )
			return 1;
		else if ( format == FORMAT_L8A8 )
			return 2;
		else if ( format == FORMAT_R8G8B8 )
			return 3;
		else if ( format == FORMAT_R8G8B8A8 )
			return 4;

		return 0;
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void ITexture::create( int _width, int _height, int _format )
	{
		width = _width;
		height = _height;
		format = _format;

		if ( data ) free( data );

		data = (byte*)malloc( width * height * getPixelSize() );

		dirty = true;
	}

	void ITexture::fill( float _r, float _g, float _b, float _a )
	{
		if ( !data ) return;

		int n = width * height * getPixelSize();

		byte r, g, b, a;

		if ( format == FORMAT_L8 )
		{
			r = (int)(_r * 255.0f);

			for ( int k = 0 ; k < n ; k += 1 )
			{
				data[k+0] = r;
			}
		}
		else if ( format == FORMAT_L8A8 )
		{
			r = (int)(_r * 255.0f);
			a = (int)(_a * 255.0f);

			for ( int k = 0 ; k < n ; k += 2 )
			{
				data[k+0] = r;
				data[k+1] = a;
			}
		}
		else if ( format == FORMAT_R8G8B8 )
		{
			r = (int)(_r * 255.0f);
			g = (int)(_g * 255.0f);
			b = (int)(_b * 255.0f);

			for ( int k = 0 ; k < n ; k += 3 )
			{
				data[k+0] = r;
				data[k+1] = g;
				data[k+2] = b;
			}
		}
		else if ( format == FORMAT_R8G8B8A8 )
		{
			r = (int)(_r * 255.0f);
			g = (int)(_g * 255.0f);
			b = (int)(_b * 255.0f);
			a = (int)(_a * 255.0f);

			for ( int k = 0 ; k < n ; k += 4 )
			{
				data[k+0] = r;
				data[k+1] = g;
				data[k+2] = b;
				data[k+3] = a;
			}
		}

		dirty = true;
	}

	void ITexture::fill( float _l, float _a )
	{
		if ( !data ) return;

		int n = width * height * getPixelSize();

		byte l, a;

		if ( format == FORMAT_L8 )
		{
			l = (int)(_l * 255.0f);

			for ( int k = 0 ; k < n ; k += 1 )
			{
				data[k+0] = l;
			}
		}
		else if ( format == FORMAT_L8A8 )
		{
			l = (int)(_l * 255.0f);
			a = (int)(_a * 255.0f);

			for ( int k = 0 ; k < n ; k += 2 )
			{
				data[k+0] = l;
				data[k+1] = a;
			}
		}
		else if ( format == FORMAT_R8G8B8 )
		{
			l = (int)(_l * 255.0f);

			for ( int k = 0 ; k < n ; k += 3 )
			{
				data[k+0] = l;
				data[k+1] = l;
				data[k+2] = l;
			}
		}
		else if ( format == FORMAT_R8G8B8A8 )
		{
			l = (int)(_l * 255.0f);
			a = (int)(_a * 255.0f);

			for ( int k = 0 ; k < n ; k += 4 )
			{
				data[k+0] = l;
				data[k+1] = l;
				data[k+2] = l;
				data[k+3] = a;
			}
		}

		dirty = true;
	}

	void ITexture::import( const char* _path )
	{
		png_structp png_ptr;
		png_infop info_ptr;

		FILE* fp = fopen( _path, "rb" );

		_assert( fp != NULL, __FILE__, __LINE__, "ITexture::import() : Unable to access file." );

		png_byte magic[8];

		fread( magic, 1, sizeof(magic), fp );

		if ( !png_check_sig( magic, sizeof(magic) ) )
		{
			fclose( fp );

			_assert( false, __FILE__, __LINE__, "ITexture::import() : Invalid PNG file." );
		}

		png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );

		if ( png_ptr == NULL )
		{
			fclose( fp );

			_assert( false, __FILE__, __LINE__, "ITexture::import() : Unable to create PNG context." );
		}

		info_ptr = png_create_info_struct( png_ptr );

		if ( info_ptr == NULL )
		{
			fclose( fp );

			png_destroy_read_struct( &png_ptr, png_infopp_NULL, png_infopp_NULL );

			_assert( false, __FILE__, __LINE__, "ITexture::import() : Unable to allocate PNG header memory." );
		}

		if ( setjmp( png_jmpbuf( png_ptr ) ) )
		{
			png_destroy_read_struct( &png_ptr, &info_ptr, png_infopp_NULL );

			fclose( fp );

			_assert( false, __FILE__, __LINE__, "ITexture::import() : Unable to read PNG data." );
		}

		png_init_io( png_ptr, fp );

		png_set_sig_bytes( png_ptr, sizeof(magic) );

		png_read_info( png_ptr, info_ptr );

		//png_read_png( png_ptr, info_ptr, NULL, png_voidp_NULL );

		int bit_depth = png_get_bit_depth( png_ptr, info_ptr );
		int color_type = png_get_color_type( png_ptr, info_ptr );
		
		if ( color_type == PNG_COLOR_TYPE_PALETTE )
			png_set_palette_to_rgb( png_ptr );

		if ( color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8 )
			png_set_gray_1_2_4_to_8( png_ptr );

		if ( png_get_valid( png_ptr, info_ptr, PNG_INFO_tRNS ) )
			png_set_tRNS_to_alpha( png_ptr );

		if ( bit_depth == 16 )
			png_set_strip_16( png_ptr );
		else if ( bit_depth < 8 )
			png_set_packing( png_ptr );

		png_read_update_info( png_ptr, info_ptr );

		png_get_IHDR( png_ptr, info_ptr, (png_uint_32*)&width, (png_uint_32*)&height,
												&bit_depth, &color_type, NULL, NULL, NULL );

		if ( color_type == PNG_COLOR_TYPE_GRAY )
			format = FORMAT_L8;
		else if ( color_type == PNG_COLOR_TYPE_GRAY_ALPHA )
			format = FORMAT_L8A8;
		else if ( color_type == PNG_COLOR_TYPE_RGB )
			format = FORMAT_R8G8B8;
		else if ( color_type == PNG_COLOR_TYPE_RGB_ALPHA )
			format = FORMAT_R8G8B8A8;

		if ( data ) free( data );

		data = (byte*)malloc( width * height * getPixelSize() );

		png_bytep* row_pointers;

		row_pointers = (png_bytep*)malloc( height * sizeof(png_bytep) );

		for ( int i = 0 ; i < height ; i++ )
		{
			row_pointers[i] = (png_bytep)(data + i * width * getPixelSize());
		}

		png_read_image( png_ptr, row_pointers );

		free( row_pointers );

		png_read_end( png_ptr, NULL );

		png_destroy_read_struct( &png_ptr, &info_ptr, png_infopp_NULL );

		fclose( fp );

		dirty = true;
	}
}
