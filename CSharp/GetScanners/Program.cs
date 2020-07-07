/*
  File: Program.cs
  Description: Code Snippet to get connected scanners using CoreScanner 
  Version: 1.0.0.1
  Date: 2020-05-21
  Copyright:  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
*/

using System;
using CoreScanner; // CoreScanner namespace
using CoreScannerLib;

namespace CoreScannerSnippet
{
    /// <summary>
    /// Main demo program to get connected scanners
    /// </summary>
    class Program
    {
        /// <summary>
        /// Get connected scanners using CoreScanner 
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            // Initialize CoreScanner COM object
            CoreScanner.CCoreScanner coreScannerObject = new CCoreScanner();

            int appHandle = 0;
            const short NumberOfScannerTypes = 1;
            short[] scannerTypes = new short[NumberOfScannerTypes];
            scannerTypes[0] = (short)ScannerType.All; //  All scanner types
            int status = -1;

            try
            {
                // Open CoreScanner COM Object
                coreScannerObject.Open(appHandle,            // Application handle     
                                       scannerTypes,         // Array of scanner types    
                                       NumberOfScannerTypes, // Length of scanner types array 
                                       out status);          // Command execution success/failure return status 

                if (status == (int)Status.Success)
                {
                    Console.WriteLine("CoreScanner Open() - Success");
                    short numOfScanners = 0;
                    string outXml = "";
                    int[] scannerIdList = new int[Constant.MaxNumDevices];

                    // Get connected scanners
                    coreScannerObject.GetScanners(out numOfScanners, // Returns number of scanners discovered 
                                                  scannerIdList,     // Returns array of connected scanner ids 
                                                  out outXml,        // Output xml containing discovered scanners information 
                                                  out status);       // Command execution success/failure return status   

                    if (status == (int)Status.Success)
                    {
                        Console.WriteLine("CoreScanner GetScanners()- Success");
                        Console.WriteLine(" Total Scanners : " + numOfScanners);
                        string scannerIds = "";
                        Array.Resize(ref scannerIdList, numOfScanners);
                        scannerIds = String.Join(", ", scannerIdList);
                        Console.WriteLine(" Scanner IDs :" + scannerIds);
                        Console.WriteLine(" Out xml : " + Environment.NewLine + outXml);
                    }
                    else
                    {
                        Console.WriteLine("CoreScanner GetScanner() - Failed. Error Code : " + status);
                    }
                }
                else
                {
                    Console.WriteLine("CoreScanner Open() - Failed. Error Code : " + status);
                }

                // Close CoreScanner COM Object
                coreScannerObject.Close(appHandle,   // Application handle
                                        out status); // Command execution success/failure return status 

                if (status == (int)Status.Success)
                {
                    Console.WriteLine("CoreScanner Close() - Success");
                }
                else
                {
                    Console.WriteLine("CoreScanner Close() - Failed. Error Code : " + status);
                }
            }
            catch (Exception exception)
            {
                Console.WriteLine("Exception : " + exception.ToString());
            }

            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}

