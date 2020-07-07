/*******************************************************************************************
* @file get_scanners.cpp
* @brief This file contains code snippet to get connected scanners using CoreScanner COM Object
* @version 1.0.0.1
* @date 2020-05-21
* @copyright  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
********************************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include "targetver.h"
#include "afxctl.h"
#include "_core_scanner_i.c"
#include "_core_scanner.h"
#include "common_defs.h"

using namespace std;

int main()
{
    ICoreScanner *scanner_interface;  // Main CoreScanner COM Interface
    HRESULT hr = S_FALSE;

    SHORT num_scanners = 0;
    BSTR out_xml = 0;

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
        const SHORT kNumberOfScannerTypes = 1;
        SHORT scanner_types[kNumberOfScannerTypes];
        LONG  app_handle = 0;
        LONG status = -1;

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
            cout << "CoreScanner Open() - Success" << endl;
            SAFEARRAY* get_scanners_array = NULL;
            SAFEARRAYBOUND bound_get_scanner_array[MAX_NUM_DEVICES];
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
                SHORT* array_values;
                HRESULT hr = SafeArrayAccessData(get_scanners_array, (void**)&array_values);
                for (int n = 0; n < num_scanners; n++)
                {
                    scanner_id_list = " " + to_string(array_values[n]);
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
                hr = SafeArrayUnaccessData(get_scanners_array);
            }
            else
            {
                cout << "CoreScanner GetScanner() - Failed. Error Code : " << status << endl;
            }
            SafeArrayDestroy(get_scanners_array);
        }
        else
        {
            cout << "CoreScanner Open() - Failed. Error Code : " << status << endl;
        }

        // Close scanner connection 
        hr = scanner_interface->Close(
            app_handle,  // Application handle
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
    // Uninitialize COM
    CoUninitialize();
    cout << "Press any key to exit." << endl;
    getchar();
}
