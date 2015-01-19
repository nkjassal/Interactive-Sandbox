//------------------------------------------------------------------------------
// <copyright file="DepthBasics.cpp" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <strsafe.h>
#include "DepthBasics.h"
#include "resource.h"

static BYTE red[] = {0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 250, 246, 240, 235, 229, 221, 214, 206, 198, 190, 181, 172, 164, 156, 147, 138, 130, 122, 114, 107, 101, 94, 89, 85, 81, 77, 73, 69, 66, 62, 59, 55, 52, 48, 44, 41, 38, 35, 32, 28, 26, 23, 20, 17, 16, 13, 11, 9, 8, 5, 4, 3, 3, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 11, 12, 12, 13, 14, 15, 16, 17, 17, 18, 18, 19, 21, 21, 22, 22, 24, 25, 26, 26, 27, 28, 29, 30, 31, 32, 34, 34, 36, 37, 39, 41, 42, 43, 44, 46, 47, 49, 50, 52, 53, 55, 56, 57, 59, 60, 62, 63, 64, 66, 67, 69, 70, 71, 73, 75, 76, 78, 79, 81, 82, 83, 85, 86, 88, 89, 97, 109, 121, 135, 149, 164, 178, 191, 203, 215, 223, 229, 231, 231, 228, 221, 210, 197, 181, 165, 148, 129, 124, 118, 113, 108, 102, 97, 91, 86, 81, 76, 71, 66, 61, 57, 53, 47, 43, 39, 35, 31, 28, 24, 21, 17, 15, 12, 10, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static BYTE green[] = {0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 251, 246, 241, 235, 229, 221, 214, 206, 198, 189, 181, 172, 165, 156, 148, 140, 132, 125, 118, 112, 106, 101, 97, 94, 92, 90, 88, 86, 83, 82, 80, 78, 76, 75, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 76, 76, 77, 77, 78, 79, 79, 80, 81, 81, 82, 83, 84, 85, 85, 86, 87, 88, 89, 90, 90, 91, 92, 93, 95, 95, 96, 97, 98, 99, 101, 102, 103, 104, 105, 106, 107, 109, 110, 110, 112, 113, 114, 116, 117, 118, 119, 121, 121, 123, 124, 125, 127, 129, 130, 132, 133, 135, 136, 138, 140, 142, 143, 145, 147, 148, 149, 151, 152, 155, 156, 157, 159, 160, 162, 163, 164, 165, 167, 169, 170, 171, 172, 173, 174, 176, 177, 178, 178, 180, 180, 181, 182, 183, 187, 190, 194, 196, 197, 198, 199, 200, 201, 201, 201, 201, 202, 202, 203, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 203, 200, 196, 192, 188, 183, 177, 172, 166, 159, 155, 148, 141, 135, 128, 121, 115, 108, 102, 96, 90, 84, 78, 73, 69, 64, 60, 56, 53, 49, 46, 44, 40, 38, 35, 32, 30, 28, 25, 24, 21, 19, 17, 15};
static BYTE blue[] = {0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 252, 249, 244, 240, 235, 229, 224, 218, 212, 206, 200, 193, 186, 179, 173, 166, 159, 152, 146, 140, 134, 128, 124, 120, 116, 112, 108, 105, 100, 97, 93, 89, 85, 81, 77, 73, 70, 65, 62, 58, 55, 51, 47, 44, 40, 37, 34, 30, 28, 24, 22, 20, 17, 15, 13, 11, 8, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 6, 6, 6, 6, 5, 6, 6, 5, 6, 6, 6, 5, 6, 6, 6, 5, 6, 6, 6, 6, 6, 5, 6, 6, 6, 6, 5, 6, 6, 6, 6, 6, 5, 5, 6, 6, 6, 6, 5, 6, 6, 6, 5, 6, 6, 6, 6, 6, 5, 6, 5, 6, 5, 6, 6, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 10, 13, 16, 19, 22, 26, 31, 36, 42, 48, 54, 60, 69, 76, 85, 96, 107, 119, 132, 145, 157, 161, 165, 169, 172, 176, 178, 182, 185, 188, 192, 195, 198, 202, 204, 208, 209, 212, 215, 218, 219, 222, 224, 226, 227, 229, 231, 232, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 232, 229, 227, 224, 220, 217, 213, 210, 206, 201, 198, 193, 187, 182, 176, 169, 162, 154, 147, 139, 130, 122, 114, 105, 96, 87, 79, 71};
int colorScale = 257;

static int minDepth = 400;
static int maxDepth = 1500;
static int depthRange = maxDepth - minDepth;

static int Width = 640;
static int Height = 480;


/// <summary>
/// Entry point for the application
/// </summary>
/// <param name="hInstance">handle to the application instance</param>
/// <param name="hPrevInstance">always 0</param>
/// <param name="lpCmdLine">command line arguments</param>
/// <param name="nCmdShow">whether to display minimized, maximized, or normally</param>
/// <returns>status</returns>
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    CDepthBasics application;
    application.Run(hInstance, nCmdShow);
}

/// <summary>
/// Constructor
/// </summary>
CDepthBasics::CDepthBasics() :
    m_pD2DFactory(NULL),
    m_pDrawDepth(NULL),
    m_hNextDepthFrameEvent(INVALID_HANDLE_VALUE),
    m_pDepthStreamHandle(INVALID_HANDLE_VALUE),
    m_bNearMode(false),
    m_pNuiSensor(NULL)
{
    // create heap storage for depth pixel data in RGBX format
    m_depthRGBX = new BYTE[cDepthWidth*cDepthHeight*cBytesPerPixel];
}

/// <summary>
/// Destructor
/// </summary>
CDepthBasics::~CDepthBasics()
{
    if (m_pNuiSensor)
    {
        m_pNuiSensor->NuiShutdown();
    }

    if (m_hNextDepthFrameEvent != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_hNextDepthFrameEvent);
    }

    // clean up Direct2D renderer
    delete m_pDrawDepth;
    m_pDrawDepth = NULL;

    // done with depth pixel data
    delete[] m_depthRGBX;

    // clean up Direct2D
    SafeRelease(m_pD2DFactory);

    SafeRelease(m_pNuiSensor);
}

/// <summary>
/// Creates the main window and begins processing
/// </summary>
/// <param name="hInstance">handle to the application instance</param>
/// <param name="nCmdShow">whether to display minimized, maximized, or normally</param>
int CDepthBasics::Run(HINSTANCE hInstance, int nCmdShow)
{
    MSG       msg = {0};
    WNDCLASS  wc;

    // Dialog custom window class
    ZeroMemory(&wc, sizeof(wc));
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.cbWndExtra    = DLGWINDOWEXTRA;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursorW(NULL, IDC_ARROW);
    wc.hIcon         = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_APP));
    wc.lpfnWndProc   = DefDlgProcW;
    wc.lpszClassName = L"DepthBasicsAppDlgWndClass";

    if (!RegisterClassW(&wc))
    {
        return 0;
    }

    // Create main application window
    HWND hWndApp = CreateDialogParamW(
        hInstance,
        MAKEINTRESOURCE(IDD_APP),
        NULL,
        (DLGPROC)CDepthBasics::MessageRouter, 
        reinterpret_cast<LPARAM>(this));

    // Show window
    ShowWindow(hWndApp, nCmdShow);

    const int eventCount = 1;
    HANDLE hEvents[eventCount];

    // Main message loop
    while (WM_QUIT != msg.message)
    {
        hEvents[0] = m_hNextDepthFrameEvent;

        // Check to see if we have either a message (by passing in QS_ALLINPUT)
        // Or a Kinect event (hEvents)
        // Update() will check for Kinect events individually, in case more than one are signalled
        DWORD dwEvent = MsgWaitForMultipleObjects(eventCount, hEvents, FALSE, INFINITE, QS_ALLINPUT);

        // Check if this is an event we're waiting on and not a timeout or message
        if (WAIT_OBJECT_0 == dwEvent)
        {
            Update();
        }

        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If a dialog message will be taken care of by the dialog proc
            if ((hWndApp != NULL) && IsDialogMessageW(hWndApp, &msg))
            {
                continue;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    return static_cast<int>(msg.wParam);
}

/// <summary>
/// Main processing function
/// </summary>
void CDepthBasics::Update()
{
    if (NULL == m_pNuiSensor)
    {
        return;
    }

    if ( WAIT_OBJECT_0 == WaitForSingleObject(m_hNextDepthFrameEvent, 0) )
    {
        ProcessDepth();
    }
}

/// <summary>
/// Handles window messages, passes most to the class instance to handle
/// </summary>
/// <param name="hWnd">window message is for</param>
/// <param name="uMsg">message</param>
/// <param name="wParam">message data</param>
/// <param name="lParam">additional message data</param>
/// <returns>result of message processing</returns>
LRESULT CALLBACK CDepthBasics::MessageRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CDepthBasics* pThis = NULL;
    
    if (WM_INITDIALOG == uMsg)
    {
        pThis = reinterpret_cast<CDepthBasics*>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<CDepthBasics*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (pThis)
    {
        return pThis->DlgProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

/// <summary>
/// Handle windows messages for the class instance
/// </summary>
/// <param name="hWnd">window message is for</param>
/// <param name="uMsg">message</param>
/// <param name="wParam">message data</param>
/// <param name="lParam">additional message data</param>
/// <returns>result of message processing</returns>
LRESULT CALLBACK CDepthBasics::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
        {
            // Bind application window handle
            m_hWnd = hWnd;

            // Init Direct2D
            D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

            // Create and initialize a new Direct2D image renderer (take a look at ImageRenderer.h)
            // We'll use this to draw the data we receive from the Kinect to the screen
            m_pDrawDepth = new ImageRenderer();
            HRESULT hr = m_pDrawDepth->Initialize(GetDlgItem(m_hWnd, IDC_VIDEOVIEW), m_pD2DFactory, cDepthWidth, cDepthHeight, cDepthWidth * sizeof(long));
            if (FAILED(hr))
            {
                SetStatusMessage(L"Failed to initialize the Direct2D draw device.");
            }

            // Look for a connected Kinect, and create it if found
            CreateFirstConnected();
        }
        break;

        // If the titlebar X is clicked, destroy app
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            // Quit the main message pump
            PostQuitMessage(0);
            break;

        // Handle button press
        case WM_COMMAND:
            // If it was for the near mode control and a clicked event, change near mode
            if (IDC_CHECK_NEARMODE == LOWORD(wParam) && BN_CLICKED == HIWORD(wParam))
            {
                // Toggle out internal state for near mode
                m_bNearMode = !m_bNearMode;

                if (NULL != m_pNuiSensor)
                {
                    // Set near mode based on our internal state
                    m_pNuiSensor->NuiImageStreamSetImageFrameFlags(m_pDepthStreamHandle, m_bNearMode ? NUI_IMAGE_STREAM_FLAG_ENABLE_NEAR_MODE : 0);
                }
            }
            break;
    }

    return FALSE;
}

/// <summary>
/// Create the first connected Kinect found 
/// </summary>
/// <returns>indicates success or failure</returns>
HRESULT CDepthBasics::CreateFirstConnected()
{
    INuiSensor * pNuiSensor;
    HRESULT hr;

    int iSensorCount = 0;
    hr = NuiGetSensorCount(&iSensorCount);
    if (FAILED(hr))
    {
        return hr;
    }

    // Look at each Kinect sensor
    for (int i = 0; i < iSensorCount; ++i)
    {
        // Create the sensor so we can check status, if we can't create it, move on to the next
        hr = NuiCreateSensorByIndex(i, &pNuiSensor);
        if (FAILED(hr))
        {
            continue;
        }

        // Get the status of the sensor, and if connected, then we can initialize it
        hr = pNuiSensor->NuiStatus();
        if (S_OK == hr)
        {
            m_pNuiSensor = pNuiSensor;
            break;
        }

        // This sensor wasn't OK, so release it since we're not using it
        pNuiSensor->Release();
    }

    if (NULL != m_pNuiSensor)
    {
        // Initialize the Kinect and specify that we'll be using depth
        hr = m_pNuiSensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH); 
        if (SUCCEEDED(hr))
        {
            // Create an event that will be signaled when depth data is available
            m_hNextDepthFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

            // Open a depth image stream to receive depth frames
            hr = m_pNuiSensor->NuiImageStreamOpen(
                NUI_IMAGE_TYPE_DEPTH,
                NUI_IMAGE_RESOLUTION_640x480,
                0,
                2,
                m_hNextDepthFrameEvent,
                &m_pDepthStreamHandle);
        }
    }

    if (NULL == m_pNuiSensor || FAILED(hr))
    {
        SetStatusMessage(L"No ready Kinect found!");
        return E_FAIL;
    }

    return hr;
}

/// <summary>
/// Handle new depth data
/// </summary>
void CDepthBasics::ProcessDepth()
{
    HRESULT hr;
    NUI_IMAGE_FRAME imageFrame;
	int index;

    // Attempt to get the depth frame
    hr = m_pNuiSensor->NuiImageStreamGetNextFrame(m_pDepthStreamHandle, 0, &imageFrame);
    /*if (FAILED(hr))
    {
        return;
    }*/

    BOOL nearMode;
    INuiFrameTexture* pTexture;

    // Get the depth image pixel texture
    hr = m_pNuiSensor->NuiImageFrameGetDepthImagePixelFrameTexture(
        m_pDepthStreamHandle, &imageFrame, &nearMode, &pTexture);
    /*if (FAILED(hr))
    {
        goto ReleaseFrame;
    }*/

    NUI_LOCKED_RECT LockedRect;

    // Lock the frame data so the Kinect knows not to modify it while we're reading it
    pTexture->LockRect(0, &LockedRect, NULL, 0);

    // Make sure we've received valid data
    if (LockedRect.Pitch != 0)
    {
        // Get the min and max reliable depth for the current frame
        int minDepth = NUI_IMAGE_DEPTH_MINIMUM_NEAR_MODE; 
		int maxDepth = NUI_IMAGE_DEPTH_MAXIMUM_NEAR_MODE; 

        BYTE * rgbrun = m_depthRGBX;


   //     const NUI_DEPTH_IMAGE_PIXEL * pBufferRun = reinterpret_cast<const NUI_DEPTH_IMAGE_PIXEL *>(LockedRect.pBits);
   //
   //     // end pixel is start + width*height - 1
   //     const NUI_DEPTH_IMAGE_PIXEL * pBufferEnd = pBufferRun + (cDepthWidth * cDepthHeight);
   //     while ( pBufferRun < pBufferEnd )
   //     {
   //         // discard the portion of the depth that contains only the player index
   //         USHORT depth = pBufferRun->depth;

			//// increase range = depth progresses slower, multiply depth by smaller value
			//// depth number chooses which 'block' of gradient sections to display
			//float scaled_depth = depth*4 - 2300;
			//int depth_number = ((int)scaled_depth) / 257;

			//index = ((int)scaled_depth) % 257;

			///* check if depth exceeds a certain value, or returns error (0)
			// * depth_number represents the 'block' being displayed - the depth field is split into sections, each section
			// * displaying the depth gradient once
			// */
			//if (scaled_depth > 2500 || index == 0 || depth_number != 5)
			//{
			//	
			//	*(rgbrun++) = 0; // set blue byte
			//	*(rgbrun++) = 0; // set green byte
			//	*(rgbrun++) = 0; // set red byte
			//}
			//else
			//{
			//	*(rgbrun++) = blue[index]; // get blue byte
			//	*(rgbrun++) = green[index]; // get green byte
			//	*(rgbrun++) = red[index]; // get red byte
			//}

   //         // we're outputting bgr, the last byte in the 32 bits is unused so skip it
   //         // if we were outputting bgra, we would write alpha here.
   //         ++rgbrun;

   //         // increment our index into the kinect's depth buffer
   //         ++pBufferRun;
			//
   //     }


		//const USHORT * pBufferRun = (const USHORT *)LockedRect.pBits;
		const NUI_DEPTH_IMAGE_PIXEL * pBufferRun = reinterpret_cast<const NUI_DEPTH_IMAGE_PIXEL *>(LockedRect.pBits);

		for (unsigned int y = 0; y < Height; y++)
		{
			for (unsigned int x = 0; x < Width; x++)
			{
				// shift off the player bits
				USHORT depth = (USHORT)((pBufferRun[(y * Width) + (Width - 1 - x)]).depth);


				float scaled_depth = depth*4 - 2450;
				int depth_number = ((int)scaled_depth) / 257;

				index = ((int)scaled_depth) % 257;

				/* check if depth exceeds a certain value, or returns error (0)
				 * depth_number represents the 'block' being displayed - the depth field is split into sections, each section
				 * displaying the depth gradient once
				 */
				if (scaled_depth > 2500 || index == 0 || depth_number != 4)
				{
				
					*(rgbrun++) = 0; // set blue byte
					*(rgbrun++) = 0; // set green byte
					*(rgbrun++) = 0; // set red byte
				}
				else
				{
					*(rgbrun++) = blue[index]; // get blue byte
					*(rgbrun++) = green[index]; // get green byte
					*(rgbrun++) = red[index]; // get red byte
				}
				++rgbrun;



				// valid depth is (generally) in the range 0 to 4095.
				// here's a simple visualisation to do a greyscale mapping, with white
				// being closest. Set 0 (invalid pixel) to black.
				/*BYTE intensity = 
            depthIn == 0 || depthIn > 4095 ?
                0 : 255 - (BYTE)(((float)depthIn / 4095.0f) * 255.0f);

				*(rgbrun++) = intensity;
				*(rgbrun++) = intensity;
				*(rgbrun++) = intensity;
				++rgbrun;*/
			}
		}



        // Draw the data with Direct2D

        m_pDrawDepth->Draw(m_depthRGBX, cDepthWidth * cDepthHeight * cBytesPerPixel);
    }

    // We're done with the texture so unlock it
    pTexture->UnlockRect(0);

    pTexture->Release();

ReleaseFrame:
    // Release the frame
    m_pNuiSensor->NuiImageStreamReleaseFrame(m_pDepthStreamHandle, &imageFrame);
}

/// <summary>
/// Set the status bar message
/// </summary>
/// <param name="szMessage">message to display</param>
void CDepthBasics::SetStatusMessage(WCHAR * szMessage)
{
    SendDlgItemMessageW(m_hWnd, IDC_STATUS, WM_SETTEXT, 0, (LPARAM)szMessage);
}