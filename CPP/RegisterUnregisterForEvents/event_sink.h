/*******************************************************************************************
* @file event_sink.h
* @version 1.0.0.1
* @date 2020-05-21
* @copyright ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
********************************************************************************************/
#pragma once
#include "afxctl.h"
#include "afxwin.h"
#include "afxcmn.h"

/**
* Class to handle CoreScanner events
**/
class EventSink : public CCmdTarget
{
    DECLARE_DYNAMIC(EventSink)

public:
    /**
    * Event sink class constructor
    */
    EventSink();


    /**
    * Event sink class  destructor
    */
    virtual ~EventSink();


    /**
    * virtual function called when last OLE reference is released
    */
    virtual void OnFinalRelease();


    /**
    * Scan decode data event handler function
    * @param event_type - Barcode event type ( 1 - good decode )
    * @param scan_data - Scan data output xml with decode data
    */
    void OnScanDataEvent(short event_type, BSTR scan_data);

    /**
    * Command response event handler function - received after asynchronous command execution
    * @param status - Command execution status
    * @param scan_cmd_response - Command response information string
    */
    void OnScanCmdResponseEvent(short status, BSTR scan_cmd_response);

    /**
    * Video event handler function
    * @param event_type - Type of video event received
    * @param size - Size of video data buffer
    * @param video_data - Video data buffer
    * @param scanner_data - Reserved param (empty string)
    */
    void OnVideoEvent(SHORT event_type, LONG size, VARIANT *video_data, BSTR* scanner_data);

    /**
    * Image event handler function
    * @param event_type - Type of image event received
    * @param size - Size of image data buffer
    * @param image_format - Format of image (jpeg/bmp/tiff)
    * @param image_data - Image data buffer
    * @param scanner_data - Information in xml about the scanner that triggered the image event
    */
    void OnImageEvent(SHORT event_type, LONG size, SHORT image_format, VARIANT *image_data, BSTR* scanner_data);

    /**
    * PNP event handler function
    * @param event_type - PNP event type (0 - attach/1 - detach)
    * @param pnp_data - Information string containing details of attached/detached scanner
    */
    void OnPnpEvents(short event_type, BSTR pnp_data);

    /**
    * Scanner notification event handler function
    * @param notification_type - Type of notification event received
    * @param scanner_data - Information string containing details of scanner
    */
    void OnScannerNotificationEvent(short notification_type, BSTR scanner_data);

    /**
    * Scanner RMD event handler function
    * @param event_type - Type of RMD event received
    * @param event_data - Information string containing data of event
    */
    void OnScanRmdEvent(short event_type, BSTR event_data);

    /**
    * IO notification event handler function
    * @param type - Reserved
    * @param data - Reserved
    */
    void OnIoNotificationEvent(short type, unsigned char data);

    /**
    * Binary data event handler function
    * @param event_type - Reserved
    * @param size - Size of binary data buffer
    * @param data_format - Format of binary data
    * @param binary_data - Binary data buffer
    * @param scanner_data - Information in xml about the scanner that triggered the binary data event
    */
    void OnBinaryDataEvent(SHORT event_type, LONG size, SHORT data_format, VARIANT *binary_data, BSTR* scanner_data);

protected:
    DECLARE_MESSAGE_MAP()
    DECLARE_DISPATCH_MAP()
    DECLARE_INTERFACE_MAP()
};


