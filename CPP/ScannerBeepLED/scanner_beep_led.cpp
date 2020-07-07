/*******************************************************************************************
* @file scanner_beep_led.cpp
* @brief This file contains code snippet to trigger scanner beep/LED using CoreScanner 
* @version 1.0.0.1
* @date 2020-06-09
* @copyright  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
********************************************************************************************/

#include "afxctl.h"
#include <iostream>
#include <string>
#include <conio.h>
#include "targetver.h"
#include "_core_scanner_i.c"
#include "_core_scanner.h"
#include "common_defs.h"

using namespace std;

const int kEventIdCount = 1;

ICoreScanner *scanner_interface;  // Main CoreScanner COM Interface
LONG  app_handle = 0;
SHORT num_scanners = 0;
SAFEARRAY* get_scanners_array = NULL;
SHORT* scanner_id_array;

/*
* Initialize COM - Create the CoreScanner COM object
*/
bool InitializeCOM()
{
    HRESULT hr = S_FALSE;

    // Initialize COM
    CoInitialize(NULL);

    //Create the CoreScanner COM object
    cout << "Initializing CoreScanner COM object" << endl;
    hr = CoCreateInstance(CLSID_CCoreScanner, NULL, CLSCTX_ALL, IID_ICoreScanner, ((void**)&scanner_interface));
    if FAILED(hr)
    {
        cout << "CoreScanner COM object creation - Failed" << endl;
        return false;
    }

    if (scanner_interface)
    {
        cout << "CoreScanner COM object creation  - Success" << endl;
        return true;
    }
    else
    {
        cout << "CoreScanner COM interface creation failed" << endl;
        return false;
    }
}

/*
* Uninitialize COM
*/
void UninitializeCOM()
{
    // Uninitialize COM
    CoUninitialize();
}

/*
* Opens scanner connection
* return value : Open scanner success/fail status
*/
bool Open()
{
    const SHORT kNumberOfScannerTypes = 1;
    HRESULT hr = S_FALSE;
    SHORT scanner_types[kNumberOfScannerTypes];
    LONG status = -1;

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
            SafeArrayDestroy(scanner_types_array);
            return true;
        }
        else
        {
            cout << "CoreScanner Open() - Failed. Error Code : " << status << endl;
        }
    }
    else
    {
        cout << "COM CoreScanner Open() - Failed" << endl;
    }
    SafeArrayDestroy(scanner_types_array);
    return false;
}

/*
* Get connected scanners
* return value : GetScanners success/fail status
*/
bool GetScanners()
{
    SAFEARRAYBOUND bound_get_scanner_array[MAX_NUM_DEVICES];
    HRESULT hr = S_FALSE;
    LONG status = -1;
    BSTR out_xml;
    bound_get_scanner_array[0].lLbound = 0;
    bound_get_scanner_array[0].cElements = MAX_NUM_DEVICES;
    get_scanners_array = SafeArrayCreate(VT_I2, 1, bound_get_scanner_array);

    // Get connected scanners
    hr = scanner_interface->GetScanners(
        &num_scanners,         // Returns number of scanners discovered 
        get_scanners_array,    // Returns array of connected scanner ids 
        &out_xml,              // Output xml containing discovered scanners information 
        &status);              // Command execution success/failure return status   

    if ((hr == S_OK) && (status == STATUS_SUCCESS))
    {
        cout << "CoreScanner GetScanners()- Success" << endl;
        cout << " Total Scanners : " << num_scanners << endl;
        string scanner_id_list = "";
        HRESULT hr = SafeArrayAccessData(get_scanners_array, (void**)&scanner_id_array);
        for (int n = 0; n < num_scanners; n++)
        {
            scanner_id_list = " " + to_string(scanner_id_array[n]);
            if (n != num_scanners - 1)
            {
                scanner_id_list += ",";
            }
        }
        cout << " Scanner IDs :" << scanner_id_list << endl;
        wstring out_str(out_xml, SysStringLen(out_xml));
        string  get_scanners_output_xml(out_str.begin(), out_str.end());
        cout << " Out xml : " << endl;
        cout << get_scanners_output_xml << endl;
        return true;
    }
    else
    {
        cout << "CoreScanner GetScanner() - Failed. Error Code : " << status << endl;
        return false;
    }
}

/*
* Close scanner connection
* return value : Close scanner success/fail status
*/
bool Close()
{
    LONG status = -1;
    HRESULT hr = S_FALSE;

    // Close scanner connection 
    hr = scanner_interface->Close(app_handle,  // Application handle
        &status);                              // Command execution success/failure return status  

    if ((hr == S_OK) && (status == STATUS_SUCCESS))
    {
        if (status == STATUS_SUCCESS)
        {
            cout << "CoreScanner Close() - Success" << endl;
            return true;
        }
        else
        {
            cout << "CoreScanner Close() - Failed. Error Code : " << status << endl;
        }
    }
    else
    {
        cout << "COM CoreScanner Close() - Failed" << endl;
    }
    return false;
}

/*
* Trigger scanner SetAction (beep/led) using CoreScanner
* @param scanner_id Scanner id of specific scanner to send command
* @param action_code SetAction (beeper/led pattern) code
* return value : SetAction success/fail status
*/
bool SetAction(int scanner_id, int action_code)
{
    LONG status = -1;
    HRESULT hr = S_FALSE;
    BSTR out_xml;

    string in_xml = "<inArgs>";
    in_xml.append("<scannerID>");
    in_xml.append(to_string(scanner_id));  // Specify scanner id to send command
    in_xml.append("</scannerID>");
    in_xml.append("<cmdArgs>");
    in_xml.append("<arg-int>");
    in_xml.append(to_string(action_code)); // Specify SetAction (beeper/led) code
    in_xml.append("</arg-int>");
    in_xml.append("</cmdArgs>");
    in_xml.append("</inArgs>");

    CComBSTR input = in_xml.c_str();

    // Send scanner action
    hr = scanner_interface->ExecCommand(SET_ACTION,         // Opcode: for SET_ACTION (beep/Led)
        &input,                                             // Input xml
        &out_xml,                                           // Output xml 
        &status);                                           // Command execution success/failure return status   

    if ((hr == S_OK) && (status == STATUS_SUCCESS))
    {
        cout << "CoreScanner Scanner SetAction(" << action_code << ") scanner ID:[" << scanner_id << "] - Success" << endl;
    }
    else
    {
        cout << "CoreScanner Scanner SetAction(" << action_code << ")  scanner ID:[" << scanner_id << "] - Failed. Error Code : " << status << endl;
        return false;
    }
    return true;
}

/*
* Wait display message and wait for user input
*/
void WaitForInput(string message)
{
    cout << message << endl;
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
    getchar();
}

/*
* Main Program
*/
int main()
{
    if (!InitializeCOM())
        return false;

    if (Open())
    {
        if (GetScanners())
        {
            if (num_scanners > 0)
            {
                // Select first scanner found
                int scanner_id = scanner_id_array[0];

                // Beep scanner (one short high) using setAction
                cout << "Beep scanner (one short high) using setAction" << endl;
                SetAction(scanner_id, ONESHORTHIGH);
                cout << " " << endl;

                // Trigger scanner LED3 (Red) on using setAction
                cout << "Trigger scanner LED3 (Red) on using setAction" << endl;
                SetAction(scanner_id, LED3ON);

                WaitForInput("LED3 (red) switched on, press any key to continue");

                // Trigger scanner LED3 (Red) off using setAction
                cout << "Trigger scanner LED3 (Red) off using setAction" << endl;
                SetAction(scanner_id, LED3OFF);
                cout << "LED3 (red) switched off" << endl;
            }
            else
            {
                cout << "No scanners found." << endl;
            }
        }

        if (get_scanners_array != NULL)
        {
            SafeArrayUnaccessData(get_scanners_array);
            SafeArrayDestroy(get_scanners_array);
        }
    }
    Close();
    UninitializeCOM();
    WaitForInput("Press any key to exit.");
}
