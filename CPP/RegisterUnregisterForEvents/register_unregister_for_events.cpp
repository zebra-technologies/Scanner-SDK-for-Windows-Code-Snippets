/*******************************************************************************************
* @file register_unregister_for_events.cpp
* @brief This file contains code snippet to register/unregister for barcode events
* @version 1.0.0.1
* @date 2020-05-21
* @copyright  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
********************************************************************************************/
#include <iostream>
#include <string>
#include <conio.h>
#include "targetver.h"
#include "event_sink.h"
#include "_core_scanner_i.c"
#include "_core_scanner.h"
#include "common_defs.h"

using namespace std;

int main()
{
    const int kEventIdCount = 1;

    ICoreScanner *scanner_interface;  // Main CoreScanner COM Interface
    DWORD cookie;
    EventSink *scanner_event_sink;
    LPUNKNOWN scanner_event_sink_unknown;

    HRESULT hr = S_FALSE;
    BSTR out_xml = 0;
    int event_id_list[kEventIdCount];

    // Initialize COM
    CoInitialize(NULL);

    //Create the CoreScanner COM object
    cout << "Initializing CoreScanner COM object" << endl;
    hr = CoCreateInstance(CLSID_CCoreScanner, NULL, CLSCTX_ALL, IID_ICoreScanner, ((void**)&scanner_interface));
    if FAILED(hr)
    {
        cout << "CoreScanner COM object creation - Failed" << endl;
        return -1;
    }

    if (scanner_interface)
    {
        cout << "CoreScanner COM object creation  - Success" << endl;

        // Create an instance of a sink object to receive CoreScanner events
        scanner_event_sink = new EventSink();
        scanner_event_sink_unknown = scanner_event_sink->GetIDispatch(FALSE);
        // Advice or make a connection
        BOOL stat = AfxConnectionAdvise(scanner_interface, DIID__ICoreScannerEvents, scanner_event_sink_unknown, FALSE, &cookie);

        const SHORT kNumberOfScannerTypes = 1;
        SHORT scanner_types[kNumberOfScannerTypes];
        LONG  app_handle = 0;
        LONG status = -1;
        BSTR out_xml;

        HRESULT hr = S_FALSE;
        SAFEARRAY* scanner_types_array = NULL;
        SAFEARRAYBOUND bound[kNumberOfScannerTypes];
        bound[0].lLbound = 0;
        bound[0].cElements = kNumberOfScannerTypes;
        scanner_types[0] = SCANNER_TYPES_ALL;  //  All scanner types
        scanner_types_array = SafeArrayCreate(VT_I2, 1, bound);
        for (long i = 0; i < kNumberOfScannerTypes; i++)
        {
            SafeArrayPutElement(scanner_types_array, &i, &scanner_types[i]);
        }

        // Open scanner connection
        hr = scanner_interface->Open(
            app_handle,            // Application handle
            scanner_types_array,   // Array of scanner types    
            kNumberOfScannerTypes, // Length of scanner types array 
            &status);              // Command execution success/failure return status   

        if ((hr == S_OK) && (status == STATUS_SUCCESS))
        {
            if (status == STATUS_SUCCESS)
            {
                cout << "CoreScanner Open() - Success" << endl;

                // Register for barcode events
                event_id_list[0] = EVENT_TYPE_BARCODE;
                string event_id_count;
                event_id_count += to_string(kEventIdCount);
                string event_ids;
                for (int i = 0; i < kEventIdCount; i++)
                {
                    event_ids += to_string(event_id_list[i]);
                    if (i < (kEventIdCount - 1))
                    {
                        event_ids += ",";
                    }
                }

                string in_xml = "<inArgs>";
                in_xml.append("<cmdArgs><arg-int>");
                in_xml.append(event_id_count);
                in_xml.append("</arg-int><arg-int>");
                in_xml.append(event_ids);
                in_xml.append("</arg-int></cmdArgs></inArgs>");
                CComBSTR input = in_xml.c_str();
                // Register for events
                hr = scanner_interface->ExecCommand(REGISTER_FOR_EVENTS,  // Opcode: Register for events
                    &input,               // Input xml
                    &out_xml,             // Output xml 
                    &status);             // Command execution success/failure return status   

                if ((hr == S_OK) && (status == STATUS_SUCCESS))
                {
                    cout << "CoreScanner RegisterForEvents() - Success" << endl;
                }
                else
                {
                    cout << "CoreScanner RegisterForEvents() - Failed. Error Code : " << status << endl;
                }



                cout << "Scan a barcode now, press any key to exit." << endl;


                MSG msg = { 0 };
                while (true)   // Message loop to dispatch windows messages while waiting for barcode events
                {
                    PeekMessage(&msg, NULL, 0, 0, 0);
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                    if (_kbhit())
                    {
                        break;
                    }
                }

                status = -1;
                // Unregister for events
                hr = scanner_interface->ExecCommand(UNREGISTER_FOR_EVENTS, // Opcode: Unregister for events
                    &input,                // Input xml
                    &out_xml,              // Output xml 
                    &status);              // Command execution success/failure return status  

                if ((hr == S_OK) && (status == STATUS_SUCCESS))
                {
                    cout << "CoreScanner UnregisterForEvents() - Success" << endl;
                }
                else
                {
                    cout << "CoreScanner UnregisterForEvents() - Failed. Error Code : " << status << endl;
                }
            }
            else
            {
                cout << "CoreScanner Open() - Failed. Error Code : " << status << endl;
            }
        }
        else
        {
            cout << "COM CoreScanner Open() - Failed" << endl;
            SafeArrayDestroy(scanner_types_array);
            return -1;
        }

        // Close scanner connection 
        hr = scanner_interface->Close(app_handle,  // Application handle
            &status);    // Command execution success/failure return status  

        if ((hr == S_OK) && (status == STATUS_SUCCESS))
        {
            if (status == STATUS_SUCCESS)
            {
                cout << "CoreScanner Close() - Success" << endl;
            }
            else
            {
                cout << "CoreScanner Close() - Failed. Error Code : " << status << endl;
            }
        }
        else
        {
            cout << "COM CoreScanner Close() - Failed" << endl;
            SafeArrayDestroy(scanner_types_array);
            return -1;
        }
        SafeArrayDestroy(scanner_types_array);
    }
    else
    {
        cout << "CoreScanner COM interface creation failed" << endl;
        return -1;
    }

    if (scanner_interface)
    {
        // Remove event bindings and release memory 
        if (cookie != 0 && scanner_event_sink)
        {
            BOOL stat = AfxConnectionUnadvise(scanner_interface, DIID__ICoreScannerEvents, scanner_event_sink_unknown, FALSE, cookie);
            delete scanner_event_sink;
            scanner_event_sink = 0;
            cookie = 0;
        }
    }

    // Uninitialize COM
    CoUninitialize();
    cout << "Press any key to exit." << endl;
    getchar();
}
