/*******************************************************************************************
* @file event_sink.cpp
* @brief Definition of class to handle CoreScanner events
* @version 1.0.0.1
* @date 2020-05-21
* @copyright  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
********************************************************************************************/

#include "event_sink.h"
#include "_core_scanner_i.c"
#include <iostream>
#include <string>
#include "afxdisp.h"  // MFC Automation classes

using namespace std;
EventSink * ScannerEventSink;
IMPLEMENT_DYNAMIC(EventSink, CCmdTarget)

/**
* Event sink constructor
**/
EventSink::EventSink()
{
    EnableAutomation();
}

/**
* Event sink destructor
**/
EventSink::~EventSink()
{

}

/**
* virtual function called when last OLE reference is released
*/
void EventSink::OnFinalRelease()
{
    CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(EventSink, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(EventSink, CCmdTarget)
    DISP_FUNCTION_ID(EventSink, "ScanCmdResponseEvent", 5, OnScanCmdResponseEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "PnpEvents", 4, OnPnpEvents, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "ScanDataEvent", 3, OnScanDataEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "ScanRmdEvent", 6, OnScanRmdEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "ImageEvent", 1, OnImageEvent, VT_EMPTY, VTS_I2 VTS_I4 VTS_I2 VTS_PVARIANT VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "VideoEvent", 2, OnVideoEvent, VT_EMPTY, VTS_I2 VTS_I4 VTS_PVARIANT VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "ScannerNotificationEvent", 8, OnScannerNotificationEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "IoEvent", 7, OnIoNotificationEvent, VT_EMPTY, VTS_I2 VTS_UI1)
    DISP_FUNCTION_ID(EventSink, "BinaryDataEvent", 9, OnBinaryDataEvent, VT_EMPTY, VTS_I2 VTS_I4 VTS_I2 VTS_PVARIANT VTS_BSTR)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(EventSink, CCmdTarget)
    INTERFACE_PART(EventSink, DIID__ICoreScannerEvents, Dispatch)
END_INTERFACE_MAP()

/**
* Barcode data event handler
**/
void EventSink::OnScanDataEvent(short event_type, BSTR scan_data)
{
    wstring out_str(scan_data, SysStringLen(scan_data));
    string  output_barcode_data(out_str.begin(), out_str.end());
    cout << "Barcode Event Type : " << event_type << endl;
    cout << "Output Xml : " << endl;
    cout << output_barcode_data << endl;
}

/**
* Response event handler
**/
void EventSink::OnScanCmdResponseEvent(short status, BSTR scan_cmd_response)
{

}

/**
* Notification event handler
**/
void EventSink::OnIoNotificationEvent(short type, unsigned char data)
{

}

/**
* Image event handler
**/
void EventSink::OnImageEvent(SHORT event_type, LONG size, SHORT image_format, VARIANT *image_data, BSTR* scanner_data)
{

}

/**
* Video event handler
**/
void EventSink::OnVideoEvent(SHORT event_type, LONG size, VARIANT *video_data, BSTR* scanner_data)
{

}

/**
* PNP event handler
**/
void EventSink::OnPnpEvents(short event_type, BSTR pnp_data)
{

}

/**
* Scanner notification event handler
**/
void EventSink::OnScannerNotificationEvent(short notification_type, BSTR scanner_data)
{

}

/**
* RMD event handler
**/
void EventSink::OnScanRmdEvent(short event_type, BSTR event_data)
{

}

/**
* Binary data event handler
**/
void EventSink::OnBinaryDataEvent(SHORT event_type, LONG size, SHORT data_format, VARIANT *binary_bata, BSTR* scanner_data)
{

}