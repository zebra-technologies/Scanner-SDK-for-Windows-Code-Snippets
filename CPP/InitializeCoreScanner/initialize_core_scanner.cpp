/*******************************************************************************************
* @file initialize_core_scanner.cpp
* @brief This file contains code snippet to Initialize/Open/Close CoreScanner COM Object
* @version 1.0.0.1
* @date 2020-05-21
* @copyright  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
********************************************************************************************/

#include <iostream>
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
    const SHORT kNumberOfScannerTypes = 1;

    // Initialize COM
    CoInitialize(NULL);

    //Create the CoreScanner COM object
    cout << "Initializing CoreScanner COM Object" << endl;
    hr = CoCreateInstance(CLSID_CCoreScanner, NULL, CLSCTX_ALL, IID_ICoreScanner, ((void**)&scanner_interface));
    if FAILED(hr)
    {
        cout << "CoreScanner COM Object creation failed" << endl;
        return -1;
    }

    if (scanner_interface)
    {
        cout << "CoreScanner COM Object Creation Success" << endl;
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
        }
        else
        {
            cout << "CoreScanner Open() - Failed. Error Code : " << status << endl;
        }
        SafeArrayDestroy(scanner_types_array);

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
            return -1;
        }
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
