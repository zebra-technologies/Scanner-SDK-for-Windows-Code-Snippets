/*
  File: Program.cs
  Description: Code Snippet to trigger scanner beep/LED using CoreScanner 
  Version: 1.0.0.1
  Date: 2020-06-08
  Copyright:  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
*/

using System;
using System.Threading;
using CoreScanner; // CoreScanner namespace
using CoreScannerLib;

namespace CoreScannerSnippet
{
    /// <summary>
    /// Trigger scanner beep/LED using CoreScanner demo program 
    /// </summary>
    class Program
    {
        /// <summary>
        /// Trigger scanner beep/LED using CoreScanner 
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            // Initialize CoreScanner COM object
            CoreScanner.CCoreScanner coreScannerObject = new CCoreScanner();

            int appHandle = 0;
            const short NumberOfScannerTypes = 1;
            short[] scannerTypes = new short[NumberOfScannerTypes];
            scannerTypes[0] = (short) ScannerType.All; //  All scanner types
            int status = -1;
            int currentScannerId = 1;

            try
            {
                // Open CoreScanner COM Object
                coreScannerObject.Open(appHandle, // Application handle     
                    scannerTypes, // Array of scanner types    
                    NumberOfScannerTypes, // Length of scanner types array 
                    out status); // Command execution success/failure return status 

                if (status == (int) Status.Success)
                {
                    Console.WriteLine("CoreScanner Open() - Success");

                    short numOfScanners = 0;
                    string outXml = "";
                    int[] scannerIdList = new int[Constant.MaxNumDevices];
                    // Get connected scanners
                    coreScannerObject.GetScanners(out numOfScanners, // Returns number of scanners discovered 
                        scannerIdList, // Returns array of connected scanner ids 
                        out outXml, // Output xml containing discovered scanners information 
                        out status); // Command execution success/failure return status   

                    if (status == (int) Status.Success)
                    {
                        Console.WriteLine("CoreScanner GetScanners()- Success");
                        Console.WriteLine(" Total Scanners : " + numOfScanners);
                        string scannerIds = "";
                        Array.Resize(ref scannerIdList, numOfScanners);
                        scannerIds = String.Join(", ", scannerIdList);
                        Console.WriteLine(" Scanner IDs :" + scannerIds);
                        Console.WriteLine(" Out xml : " + Environment.NewLine + outXml);

                        if (numOfScanners > 0)
                        {
                            // Use first scanner
                            currentScannerId = scannerIdList[0];

                            // Trigger Scanner Beep
                            Console.WriteLine("Beep scanner (one short high) using setAction");
                            status = -1;
                            int opCode = (int) Opcode.SetAction;
                            // Beep: one short high - input xml
                            string inXml = "<inArgs>" +
                                           "<scannerID>" + currentScannerId.ToString() + "</scannerID>" +
                                           "<cmdArgs>" +
                                           "<arg-int>" + (int) BeepCode.OneShortHigh +  // Specify beeper code
                                           "</arg-int>" + 
                                           "</cmdArgs>" +
                                           "</inArgs>";

                            coreScannerObject.ExecCommand(opCode, // Opcode: for Scanner Beep (SET_ACTION)
                                ref inXml, // Input XML
                                out outXml, // Output XML 
                                out status); // Command execution success/failure return status  

                            if (status == (int) Status.Success)
                            {
                                Console.WriteLine("Scanner Beep() scanner ID:[" +
                                                  currentScannerId.ToString() + "] - Success");
                            }
                            else
                            {
                                Console.WriteLine("Scanner Beep() scanner ID:[" +
                                                  currentScannerId.ToString() + "] - Failed. Error Code : " + status);
                            }

                            Console.WriteLine();

                            Console.WriteLine("Trigger scanner LED3 (Red) on using setAction");
                            opCode = (int) Opcode.SetAction;
                            // Trigger scanner LED3(Red) on - input xml
                            inXml = "<inArgs>" +
                                    "<scannerID>" + currentScannerId.ToString() + "</scannerID>" +
                                    "<cmdArgs>" +
                                    "<arg-int>" + (int) LEDCode.Led3On +   // Specify LED code to switch on/off
                                    "</arg-int>" +
                                    "</cmdArgs>" +
                                    "</inArgs>";

                            // Trigger scanner LED on
                            coreScannerObject.ExecCommand(opCode, // Opcode: for Scanner LED on (SET_ACTION)
                                ref inXml, // Input XML
                                out outXml, // Output XML 
                                out status); // Command execution success/failure return status  

                            if (status == (int) Status.Success)
                            {
                                Console.WriteLine("Scanner LED on, scanner ID:[" +
                                                  currentScannerId.ToString() + "] - Success");
                            }
                            else
                            {
                                Console.WriteLine("Scanner LED on, scanner ID:[" +
                                                  currentScannerId.ToString() + "] - Failed. Error Code : " + status);
                            }

                            Console.WriteLine("LED3 (red) switched on, press any key to continue.");
                            while (!Console.KeyAvailable)
                            {
                                Thread.Sleep(10);
                            }

                            Console.ReadKey();
                            Console.WriteLine();

                            Console.WriteLine("Trigger scanner LED3 (Red) off using setAction");
                            opCode = (int) Opcode.SetAction;
                            // Trigger scanner LED3 (Red) off - input xml
                            inXml = "<inArgs>" +
                                    "<scannerID>" + currentScannerId.ToString() + "</scannerID>" +
                                    "<cmdArgs>" +
                                    "<arg-int>" + (int) LEDCode.Led3Off +  // Specify LED code to switch on/off
                                    "</arg-int>" +
                                    "</cmdArgs>" +
                                    "</inArgs>";

                            // Trigger scanner LED off 
                            coreScannerObject.ExecCommand(opCode, // Opcode: for Scanner LED on (SET_ACTION)
                                ref inXml, // Input XML
                                out outXml, // Output XML 
                                out status); // Command execution success/failure return status  

                            if (status == (int) Status.Success)
                            {
                                Console.WriteLine("Scanner LED off, scanner ID:[" +
                                                  currentScannerId.ToString() + "] - Success");
                            }
                            else
                            {
                                Console.WriteLine("Scanner LED off, scanner ID:[" +
                                                  currentScannerId.ToString() + "] - Failed. Error Code : " + status);
                            }

                            Console.WriteLine("LED3 (red) switched off, press any key to continue.");
                        }
                        else
                        {
                            Console.WriteLine("CoreScanner GetScanner() - No scanners found");
                        }
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
                coreScannerObject.Close(appHandle, // Application handle
                    out status); // Command execution success/failure return status

                if (status == (int) Status.Success)
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

