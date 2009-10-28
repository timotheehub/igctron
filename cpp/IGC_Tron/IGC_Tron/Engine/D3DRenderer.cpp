
#ifdef _WIN32

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "W32Window.h"
#include "D3DRenderer.h"
#include "IRenderer.h"
#include "Engine.h"

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

	D3DRenderer::D3DRenderer( Engine* _engine ) : IRenderer( _engine )
	{
	}

	D3DRenderer::~D3DRenderer()
	{
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	LPDIRECT3DDEVICE9 D3DRenderer::getDevice()
	{
		return lpD3DDevice;
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void D3DRenderer::initialize()
	{
		lpD3D = Direct3DCreate9( D3D_SDK_VERSION );

		_assert( lpD3D != NULL, __FILE__, __LINE__, "D3DRenderer::initialize() : Unable to initialize Direct3D." );

		_assert( typeid( *engine->getWindow() ) == typeid( W32Window ), __FILE__, __LINE__,
			"D3DRenderer::initialize() : Invalid window type, W32Window needed." );

		W32Window* window = (W32Window*)engine->getWindow();

		D3DPRESENT_PARAMETERS d3dpp = {0};
		d3dpp.Windowed						= fullscreen ? false : true;
		d3dpp.SwapEffect					= D3DSWAPEFFECT_COPY;
		d3dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;
		d3dpp.BackBufferWidth				= window->getInnerWidth();
		d3dpp.BackBufferHeight				= window->getInnerHeight();
		d3dpp.BackBufferCount				= 1;
		d3dpp.EnableAutoDepthStencil		= TRUE;
		d3dpp.AutoDepthStencilFormat		= D3DFMT_D16;
		d3dpp.FullScreen_RefreshRateInHz	= 0;
		d3dpp.PresentationInterval			= verticalSync ? D3DPRESENT_INTERVAL_ONE
													: D3DPRESENT_INTERVAL_IMMEDIATE;

		if ( hardware )
		{
			lpD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window->getHandle(),
									D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice );
		}
		else
		{
			lpD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, window->getHandle(),
												D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice );
		}

		_assert( lpD3DDevice != NULL, __FILE__, __LINE__, "D3DRenderer::initialize() : Unable to create Direct3D device." );

		if ( FAILED( lpD3DDevice->CreateTexture( window->getInnerWidth(), window->getInnerHeight(), 1, 0,
									D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &lpRenderTexture, NULL ) ) )
			_assert( false, __FILE__, __LINE__, "D3DRenderer::initialize() : Unable to create Direct3D render texture." );

		{
			void* data = NULL;

			float vertices[] =
			{
				-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
				+1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
				-1.0f, +1.0f, 0.0f, 0.0f, 0.0f,
				+1.0f, +1.0f, 0.0f, 1.0f, 0.0f
			};

			lpD3DDevice->CreateVertexBuffer( sizeof(vertices), D3DUSAGE_WRITEONLY,
				D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_DEFAULT, &lpVertexBuffer, NULL );

			lpVertexBuffer->Lock( 0, sizeof(vertices), (void**)&data, 0 );
			CopyMemory( data, vertices, sizeof(vertices) );
			lpVertexBuffer->Unlock();
		}

		{
			void* data = NULL;

			word indices[] = { 0, 1, 2, 3, 2, 1 };

			lpD3DDevice->CreateIndexBuffer( sizeof(indices), D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16, D3DPOOL_DEFAULT, &lpIndexBuffer, NULL );

			lpIndexBuffer->Lock( 0, sizeof(indices), (void**)&data, 0 );
			CopyMemory( data, indices, sizeof(indices) );
			lpIndexBuffer->Unlock();
		}

		{
			LPD3DXBUFFER code = NULL;

			D3DVERTEXELEMENT9 declaration[] = 
			{
				{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
				D3DDECL_END()
			};

			lpD3DDevice->CreateVertexDeclaration( declaration, &lpVertexDeclaration );

			const CHAR vertexShader[] =
				"vs_1_1 \n"\
				\
				"dcl_position v0 \n"\
				"dcl_texcoord v1 \n"\
				\
				"mov oPos, v0 \n"\
				"mov oT0, v1 \n";
			D3DXAssembleShader( vertexShader, strlen(vertexShader), NULL, NULL, NULL, &code, NULL );

			lpD3DDevice->CreateVertexShader( (DWORD*)code->GetBufferPointer(), &lpVertexShader );

			if( code )
				code->Release(); 
		}

		{
			LPD3DXBUFFER code = NULL;

			const CHAR pixelShader[] = 
				"ps_1_1 \n"\
				\
				"tex t0 \n"\
				"mov r0, t0 \n";
			D3DXAssembleShader( pixelShader, strlen(pixelShader), NULL, NULL, NULL, &code, NULL );

			lpD3DDevice->CreatePixelShader( (DWORD*)code->GetBufferPointer(), &lpPixelShader );

			if( code )
				code->Release(); 
		}

		if( FAILED( D3DXCreateFont( lpD3DDevice, 16, 0, FW_BOLD, 0, FALSE,
						DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE, "Arial", &lpFont ) ) )
			_assert( false, __FILE__, __LINE__, "D3DRenderer::initialize() : Unable to create Direct3D font." );
	}

	void D3DRenderer::finalize()
	{
		if ( lpFont )
			lpFont->Release();

		if ( lpPixelShader )
			lpPixelShader->Release();

		if ( lpVertexShader )
			lpVertexShader->Release();

		if ( lpVertexDeclaration )
			lpVertexDeclaration->Release();

		if ( lpIndexBuffer )
			lpIndexBuffer->Release();

		if ( lpVertexBuffer )
			lpVertexBuffer->Release();

		if ( lpRenderTexture )
			lpRenderTexture->Release();

		if ( lpD3DDevice )
			lpD3DDevice->Release();

		lpD3DDevice = NULL;

		if ( lpD3D )
			lpD3D->Release();

		lpD3D = NULL;
	}

	void D3DRenderer::update()
	{
		/*lpD3DDevice->BeginScene();

		lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
		lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );
		lpD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );

		lpD3DDevice->SetStreamSource( 0, lpVertexBuffer, 0, 20 );
		lpD3DDevice->SetIndices( lpIndexBuffer );

		lpD3DDevice->SetTexture( 0, lpRenderTexture );

		lpD3DDevice->SetVertexDeclaration( lpVertexDeclaration );

		lpD3DDevice->SetVertexShader( lpVertexShader );
		lpD3DDevice->SetPixelShader( lpPixelShader );

		lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );

		lpD3DDevice->EndScene();*/

		lpD3DDevice->BeginScene();

		for ( vector<Label>::iterator it = labels.begin() ; it != labels.end() ; ++it )
		{
			Label label = *it;

			RECT rect = { label.x, label.y, 0, 0 };

			lpFont->DrawText( NULL, label.text.c_str(), -1, &rect, DT_NOCLIP,
								D3DXCOLOR( label.r, label.g, label.b, label.a ) );
		}

		lpD3DDevice->EndScene();

		lpD3DDevice->Present( NULL, NULL, NULL, NULL );
	}

	void D3DRenderer::clear( float _r, float _g, float _b, float _depth )
	{
		lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB( (int)(_r * 255.0f), (int)(_g * 255.0f), (int)(_b * 255.0f) ), _depth, 0 );
	}

} 

#endif
