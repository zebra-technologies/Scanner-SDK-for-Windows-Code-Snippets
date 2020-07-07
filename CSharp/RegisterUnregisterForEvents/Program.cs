/*
  File: Program.cs
  Description: Code Snippet to register/unregister for events using CoreScanner 
  Version: 1.0.0.1
  Date: 2020-05-22
  Copyright:  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
*/

using System;
using System.IO;
using System.Threading;
using System.Xml.Linq;
using System.Linq;
using CoreScanner; // CoreScanner namespace
using CoreScannerLib;

namespace CoreScannerSnippet
{
    /// <summary>
    /// Register/unregister for events using CoreScanner demo program 
    /// </summary>
    class Program
    {

        /// <summary>
        /// Register/Unregister for events using CoreScanner 
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
                coreScannerObject.Open(appHandle, // Application handle     
                    scannerTypes,                 // Array of scanner types    
                    NumberOfScannerTypes,         // Length of scanner types array 
                    out status);                  // Command execution success/failure return status 

                if (status == (int)Status.Success)
                {
                    Console.WriteLine("CoreScanner Open() - Success");

                    int eventIdCount = 1; // Number of events to register (only barcode events)
                    int[] eventIdList = new int[eventIdCount];
                    // Register for barcode events only
                    eventIdList[0] = (int)EventType.Barcode;

                    string eventIds = String.Join(",", eventIdList);
                    string inXml = "<inArgs>" +
                                   "<cmdArgs>" +
                                   "<arg-int>" + eventIdCount + "</arg-int>" +   // Number of events to register
                                   "<arg-int>" + eventIds + "</arg-int>" +       // Event id list of events to register for
                                   "</cmdArgs>" +
                                   "</inArgs>";

                    int opCode = (int)Opcode.RegisterForEvents;
                    string outXml = "";
                    status = -1;

                    // Call register for events
                    coreScannerObject.ExecCommand(opCode,      // Opcode: Register for events
                                                  ref inXml,   // Input XML
                                                  out outXml,  // Output XML 
                                                  out status); // Command execution success/failure return status  

                    if (status == (int)Status.Success)
                    {
                        Console.WriteLine("CoreScanner RegisterForEvents() - Success");
                    }
                    else
                    {
                        Console.WriteLine("CoreScanner RegisterForEvents() - Failed. Error Code : " + status);
                    }

                    // Add barcode data event handler
                    coreScannerObject.BarcodeEvent += CoreScannerObject_BarcodeEvent;

                    Console.WriteLine("Scan a barcode now, press " +
                                      "any key to exit.");
                    while (!Console.KeyAvailable)
                    {
                        Thread.Sleep(10);
                    }

                    status = -1;
                    opCode = (int)Opcode.UnregisterForEvents;

                    // Call unregister for events
                    coreScannerObject.ExecCommand(opCode,      // Opcode: Unregister for events
                                                  ref inXml,   // Input XML
                                                  out outXml,  // Output XML 
                                                  out status); // Command execution success/failure return status  

                    if (status == (int)Status.Success)
                    {
                        Console.WriteLine("CoreScanner UnregisterForEvents() - Success");
                    }
                    else
                    {
                        Console.WriteLine("CoreScanner UnregisterForEvents() - Failed. Error Code : " + status);
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

        /// <summary>
        /// Barcode data event handler
        /// </summary>
        /// <param name="eventType">Barcode event type</param>
        /// <param name="barcodeData">Output xml</param>
        private static void CoreScannerObject_BarcodeEvent(short eventType, ref string barcodeData)
        {
            Console.WriteLine("Decode Event Type : " + Enum.GetName(typeof(DecodeEventType), eventType));
            var document = XDocument.Load(new StringReader(barcodeData));
            int barcodeDataType = Int32.Parse(document.Descendants(XName.Get("datatype")).First().Value);
            string barcodeDataLabel = document.Descendants(XName.Get("datalabel")).First().Value;
            Console.WriteLine("Decode Data Type: " + Enum.GetName(typeof(CodeType), barcodeDataType));
            Console.WriteLine("Decode Data Label: " + barcodeDataLabel);
            Console.WriteLine("Output Xml : ");
            Console.WriteLine(barcodeData + Environment.NewLine);
        }
    }
}

