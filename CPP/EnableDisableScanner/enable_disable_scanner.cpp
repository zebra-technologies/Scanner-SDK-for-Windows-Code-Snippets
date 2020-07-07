/*******************************************************************************************
* @file enable_disable_scanner.cpp
* @brief This file contains code snippet to enable/disable barcode scanner
* @version 1.0.0.1
* @date 2020-05-21
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
    BSTR out_xml;

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
* Enable all scanners
* return value : Enable success/fail status
*/
bool Enable()
{
    if (num_scanners > 0)
    {
        LONG status = -1;
        HRESULT hr = S_FALSE;
        BSTR out_xml;
        cout << "Enabling all scanners" << endl;
        for (int n = 0; n < num_scanners; n++)
        {
            string in_xml = "<inArgs>";
            in_xml.append("<scannerID>");
            in_xml.append(to_string(scanner_id_array[n]));
            in_xml.append("</scannerID>");
            in_xml.append("</inArgs>");
            CComBSTR input = in_xml.c_str();

            // Enable Scanner
            hr = scanner_interface->ExecCommand(DEVICE_SCAN_ENABLE, // Opcode: ScannerEnable
                &input,                                             // Input xml
                &out_xml,                                           // Output xml 
                &status);                                           // Command execution success/failure return status   

            if ((hr == S_OK) && (status == STATUS_SUCCESS))
            {
                cout << "CoreScanner ScannerEnable() scanner ID:[" << scanner_id_array[n] << "] - Success" << endl;
            }
            else
            {
                cout << "CoreScanner ScannerEnable() scanner ID:[" << scanner_id_array[n] << "] - Failed. Error Code : " << status << endl;
                return false;
            }
        }
        return true;
    }
    else
    {
        cout << "No scanners found." << endl;
        return false;
    }
}

/*
* Disable all scanners
* return value : Disable success/fail status
*/
bool Disable()
{
    if (num_scanners > 0)
    {
        LONG status = -1;
        HRESULT hr = S_FALSE;
        BSTR out_xml;
        for (int n = 0; n < num_scanners; n++)
        {
            string in_xml = "<inArgs>";
            in_xml.append("<scannerID>");
            in_xml.append(to_string(scanner_id_array[n]));
            in_xml.append("</scannerID>");
            in_xml.append("</inArgs>");
            CComBSTR  input = in_xml.c_str();

            cout << "Disabling all scanners" << endl;
            // Disable Scanner
            hr = scanner_interface->ExecCommand(DEVICE_SCAN_DISABLE, // Opcode: ScannerDisable
                &input,                                              // Input xml
                &out_xml,                                            // Output xml 
                &status);                                            // Command execution success/failure return status   

            if ((hr == S_OK) && (status == STATUS_SUCCESS))
            {
                cout << "CoreScanner ScannerDisable() scanner ID:[" << scanner_id_array[n] << "] - Success" << endl;
            }
            else
            {
                cout << "CoreScanner ScannerDisable() scanner ID:[" << scanner_id_array[n] << "] - Failed. Error Code : " << status << endl;
                return false;
            }
        }
        return true;
    }
    else
    {
        cout << "No scanners found." << endl;
        return false;
    }
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
            if (Disable())
            {
                WaitForInput("All scanners disabled, press any key to continue.");
            }

            if (Enable())
            {
                WaitForInput("All scanners enabled, press any key to continue.");
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
