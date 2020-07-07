/*
  File: CommonDefs.cs
  Description : CoreScanner common definitions
  Version: 1.0.0.1
  Date: 2020-05-22
  Copyright:  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
*/

namespace CoreScannerLib
{
    /// <summary>
    /// Scanner Types
    /// </summary>
    public enum ScannerType
    {
        /// <summary>
        /// All Scanner Types mentioned below
        /// </summary>
        All = 1,
        /// <summary>
        /// Symbol Native API (SNAPI) with Imaging Interface
        /// </summary>
        Snapi = 2,
        /// <summary>
        /// Simple Serial Interface (SSI) over RS-232
        /// </summary>
        SsiRs232 = 3,
        /// <summary>
        /// IBM Hand-held USB
        /// </summary>
        IbmHandheldUsb = 6,
        /// <summary>
        /// WincorNixdorf Mode B
        /// </summary>
        NixdorfModeB = 7,
        /// <summary>
        /// USB Keyboard HID
        /// </summary>
        UsbKeyboardHid = 8,
        /// <summary>
        /// IBM Table-top USB
        /// </summary>
        IbmTableTopUsb = 9,
        /// <summary>
        /// Simple Serial Interface (SSI) over Bluetooth Classic
        /// </summary>
        SsiBluetoothClassic = 11,
        /// <summary>
        /// OPOS (IBM Hand-held)
        /// </summary>
        Opos = 13
    }

    /// <summary>
    /// Event Types
    /// </summary>
    public enum EventType
    {
        /// <summary>
        /// Barcode event Type
        /// </summary>
        Barcode = 1,

        /// <summary>
        /// Image event Type
        /// </summary>
        Image = 2,

        /// <summary>
        /// Video event Type
        /// </summary>
        Video = 4,

        /// <summary>
        /// RMD event Type
        /// </summary>
        Rmd = 8,

        /// <summary>
        /// PNP event Type
        /// </summary>
        Pnp = 16,

        /// <summary>
        /// Other event Types
        /// </summary>
        Other = 32,
    }

    /// <summary>
    /// Available Values For 'Status' 
    /// </summary>
    public enum Status
    {
        /// <summary>
        /// Status success
        /// </summary>
        Success = 0,

        /// <summary>
        /// Status locked
        /// </summary>
        Locked = 10
    }

    /// <summary>
    /// Barcode Event Type
    /// </summary>
    public enum DecodeEventType
    {
        /// <summary>
        /// Successful decode
        /// </summary>
        ScannerDecodeGood = 1
    }

    /// <summary>
    /// Video Event Type
    /// </summary>
    public enum VideoEventType
    {
        /// <summary>
        /// Complete video frame captured
        /// </summary>
        VideoFrameComplete = 1
    }


    /// <summary>
    /// Image Event Type
    /// </summary>
    public enum ImageEventType
    {
        /// <summary>
        /// Image captured
        /// </summary>
        ImageComplete = 1,

        /// <summary>
        /// Image error or status
        /// </summary>
        ImageTranStatus = 2,
    }

    /// <summary>
    /// Device Notification 
    /// </summary>
    public enum DeviceNotification
    {
        /// <summary>
        /// Scanner attached
        /// </summary>
        ScannerAttached = 0,

        /// <summary>
        /// Scanner detached
        /// </summary>
        ScannerDetached = 1
    }

    /// <summary>
    /// Scanner Notification
    /// </summary>
    public enum ScannerNotification
    {
        /// <summary>
        /// Barcode mode
        /// </summary>
        BarcodeMode = 1,

        /// <summary>
        /// Image mode
        /// </summary>
        ImageMode = 2,

        /// <summary>
        /// Video mode
        /// </summary>
        VideoMode = 3,

        /// <summary>
        /// Device enabled
        /// </summary>
        DeviceEnabled = 13,

        /// <summary>
        /// Device disabled
        /// </summary>
        DeviceDisabled = 14
    }

    /// <summary>
    /// Firmware Download Events
    /// </summary>
    public enum FirmwareDownloadEvent
    {
        /// <summary>
        /// Triggered when flash download session starts 
        /// </summary>
        ScannerUfSessionStart = 11,

        /// <summary>
        /// Triggered when component download starts 
        /// </summary>
        ScannerUfDownloadStart = 12,

        /// <summary>
        /// Triggered when block(s) Of flash completed 
        /// </summary>
        ScannerUfDownloadProgress = 13,

        /// <summary>
        /// Triggered when component download ends 
        /// </summary>
        ScannerUfDownloadEnd = 14,

        /// <summary>
        /// Triggered when flash download session ends 
        /// </summary>
        ScannerUFSessionEnd = 15
    }

    /// <summary>
    /// File Types
    /// Please refer scanner PRGs for more information on scanner parameters.   
    /// </summary>
    public enum FileType
    {
        /// <summary>
        /// Jpeg file
        /// </summary>
        JpegFileSelection = 1,

        /// <summary>
        /// Bmp file
        /// </summary>
        BmpFileSelection = 3,

        /// <summary>
        /// Tiff file
        /// </summary>
        TiffFileSelection = 4
    }

    /// <summary>
    /// Video View Finder 
    /// </summary>
    public enum VideoViewFinder
    {
        /// <summary>
        ///  Video View Finder On  
        /// </summary>
        On = 1,

        /// <summary>
        /// Video View Finder Off
        /// </summary>
        Off = 0
    }

    /// <summary>
    /// Param Persistance
    /// </summary>
    public enum ParamPersistance
    {
        /// <summary>
        /// Parameters Persistance On
        /// </summary>
        ParamPersistanceOn = 1,

        /// <summary>
        /// Parameters Persistance On
        /// </summary>
        ParamPersistanceOff = 0
    }

    /// <summary>
    /// Beep Codes
    /// Please refer scanner PRGs for more information on beep codes.   
    /// </summary>
    public enum BeepCode
    {
        OneShortHigh = 0x00,
        TwoShortHigh = 0x01,
        ThreeShortHigh = 0x02,
        FourShortHigh = 0x03,
        FiveShortHigh = 0x04,

        OneShortLow = 0x05,
        TwoShortLow = 0x06,
        ThreeShortLow = 0x07,
        FourShortLow = 0x08,
        FiveShortLow = 0x09,

        OneLongHigh = 0x0a,
        TwoLongHigh = 0x0b,
        ThreeLongHigh = 0x0c,
        FourLongHigh = 0x0d,
        FiveLongHigh = 0x0e,

        OneLongLow = 0x0f,
        TwoLongLow = 0x10,
        ThreeLongLow = 0x11,
        FourLongLow = 0x12,
        FiveLongLow = 0x13,

        FastHighLowHighLow = 0x14,
        SlowHighLowHighLow = 0x15,
        HighLow = 0x16,
        LowHigh = 0x17,
        HighLowHigh = 0x18,
        LowHighLow = 0x19
    }

    /// <summary>
    /// LED Codes
    /// Please refer scanner PRGs for more information on LED codes.   
    /// </summary>
    public enum LEDCode
    {
        /// <summary>
        /// Green  Led On
        /// </summary>
        Led1On = 0x2B,

        /// <summary>
        /// Yellow  Led On
        /// </summary>
        Led2On = 0x2D,

        /// <summary>
        /// Red  Led On 
        /// </summary>
        Led3On = 0x2F,

        /// <summary>
        /// Green  Led Off 
        /// </summary>
        Led1Off = 0x2A,

        /// <summary>
        /// Yellow  Led Off 
        /// </summary>
        Led2Off = 0x2E,

        /// <summary>
        /// Red  Led Off
        /// </summary>
        Led3Off = 0x30
    }

    /// <summary>
    /// CoreScanner Opcodes
    /// Please refer Scanner SDK for Windows Developer Guide for more information on opcodes.   
    /// </summary>
    public enum Opcode
    {
        /// <summary>
        /// Gets the version of CoreScanner
        /// </summary>
        GetVersion = 1000,

        /// <summary>
        /// Register for API events
        /// </summary>
        RegisterForEvents = 1001,

        /// <summary>
        /// Unregister for API events
        /// </summary>
        UnregisterForEvents = 1002,

        /// <summary>
        /// Get Bluetooth scanner pairing bar code
        /// </summary>
        GetPairingBarcode = 1005,

        /// <summary>
        /// Claim a specific device
        /// </summary>
        ClaimDevice = 1500,

        /// <summary>
        /// Release a specific device
        /// </summary>
        ReleaseDevice = 1501,

        /// <summary>
        /// Abort MacroPDF of a specified scanner
        /// </summary>
        AbortMacroPdf = 2000,

        /// <summary>
        /// Abort firmware update process of a specified scanner, while in progress
        /// </summary>
        AbortUpdateFirmware = 2001,

        /// <summary>
        /// Turn Aim off
        /// </summary>
        DeviceAimOff = 2002,

        /// <summary>
        /// Turn Aim on
        /// </summary>
        DeviceAimOn = 2003,

        /// <summary>
        /// Flush MacroPDF of a specified scanner
        /// </summary>
        FlushMacroPdf = 2005,

        /// <summary>
        /// Pull the trigger of a specified scanner
        /// </summary>
        DevicePullTrigger = 2011,

        /// <summary>
        /// Release the trigger of a specified scanner
        /// </summary>
        DeviceReleaseTrigger = 2012,

        /// <summary>
        /// Disable scanning on a specified scanner
        /// </summary>
        DeviceScanDisable = 2013,

        /// <summary>
        /// Enable scanning on a specified scanner
        /// </summary>
        DeviceScanEnable = 2014,

        /// <summary>
        /// Set parameters to default values of a specified scanner
        /// </summary>
        SetParameterDefaults = 2015,

        /// <summary>
        /// Set parameters of a specified scanner
        /// </summary>
        DeviceSetParameters = 2016,

        /// <summary>
        /// Set and persist parameters of a specified scanner
        /// </summary>
        SetParameterPersistance = 2017,

        /// <summary>
        /// Reboot a specified scanner
        /// </summary>
        RebootScanner = 2019,

        /// <summary>
        /// Disconnect the specified Bluetooth scanner
        /// </summary>
        DisconnectBluetoothScanner = 2023,

        /// <summary>
        /// Change a specified scanner to snapshot mode 
        /// </summary>
        DeviceCaptureImage = 3000,

        /// <summary>
        /// Change a specified scanner to decode mode 
        /// </summary>
        DeviceCaptureBarcode = 3500,

        /// <summary>
        /// Change a specified scanner to video mode 
        /// </summary>
        DeviceCaptureVideo = 4000,

        /// <summary>
        /// Get all the attributes of a specified scanner
        /// </summary>
        RsmAttrGetAll = 5000,

        /// <summary>
        /// Get the attribute values(s) of specified scanner
        /// </summary>
        RsmAttrGet = 5001,

        /// <summary>
        /// Get the next attribute to a given attribute of specified scanner
        /// </summary>
        RsmAttrGetNext = 5002,

        /// <summary>
        /// Set the attribute values(s) of specified scanner
        /// </summary>
        RsmAttrSet = 5004,

        /// <summary>
        /// Store and persist the attribute values(s) of specified scanner
        /// </summary>
        RsmAttrStore = 5005,

        /// <summary>
        /// Get the topology of the connected devices
        /// </summary>
        GetDeviceTopology = 5006,

        /// <summary>
        /// Remove all Symbol device entries from registry
        /// </summary>
        UninstallSymbolDevices = 5010,

        /// <summary>
        /// Start (flashing) the updated firmware
        /// </summary>
        StartNewFirmware = 5014,

        /// <summary>
        /// Update the firmware to a specified scanner
        /// </summary>
        UpdateFirmware = 5016,

        /// <summary>
        /// Update the firmware to a specified scanner using a scanner plug-in
        /// </summary>
        UpdateFirmwareFromPlugin = 5017,

        /// <summary>
        /// Update good scan tone of the scanner with specified wav file
        /// </summary>
        UpdateDecodeTone = 5050,

        /// <summary>
        /// Erase good scan tone of the scanner
        /// </summary>
        EraseDecodeTone = 5051,

        /// <summary>
        /// Perform an action involving scanner beeper/LEDs
        /// </summary>
        SetAction = 6000,

        /// <summary>
        /// Set the serial port settings of a NIXDORF Mode-B scanner
        /// </summary>
        DeviceSetSerialPortSettings = 6101,

        /// <summary>
        /// Switch the USB host mode of a specified scanner
        /// </summary>
        DeviceSwitchHostMode = 6200,

        /// <summary>
        /// Switch CDC devices
        /// </summary>
        SwitchCdcDevices = 6201,

        /// <summary>
        /// Enable/Disable keyboard emulation mode
        /// </summary>
        KeyboardEmulatorEnable = 6300,

        /// <summary>
        /// Set the locale for keyboard emulation mode
        /// </summary>
        KeyboardEmulatorSetLocale = 6301,

        /// <summary>
        /// Get current configuration of the HID keyboard emulator
        /// </summary>
        KeyboardEmulatorGetConfig = 6302,

        /// <summary>
        ///  Configure Driver ADF
        /// </summary>
        ConfigureDADF = 6400,

        /// <summary>
        /// Reset Driver ADF
        /// </summary>
        ResetDADF = 6401,

        /// <summary>
        /// Measure the weight on the scanner's platter and get the value
        /// </summary>
        ScaleReadWeight = 7000,

        /// <summary>
        ///  Zero the scale
        /// </summary>
        ScaleZeroScale = 7002,

        /// <summary>
        /// Reset the scale
        /// </summary>
        ScaleSystemReset = 7015,
    }

    /// <summary>
    /// Code Types
    /// Please refer Scanner SDK for Windows Developer Guide for more information on code types.   
    /// </summary>
    public enum CodeType
    {
        Unknown = 0x00,
        Code39 = 0x01,
        Codabar = 0x02,
        Code128 = 0x03,
        Discrete2of5 = 0x04,
        Iata = 0x05,
        Interleaved2of5 = 0x06,
        Code93 = 0x07,
        UpcA = 0x08,
        UpcE0 = 0x09,
        Ean8 = 0x0A,
        Ean13 = 0x0B,
        Code11 = 0x0C,
        Code49 = 0x0D,
        Msi = 0x0E,
        Ean128 = 0x0F,
        UpcE1 = 0x10,
        Pdf417 = 0x11,
        Code16k = 0x12,
        Code39FullAscii = 0x13,
        UpcD = 0x14,
        Code39Trioptic = 0x15,
        Bookland = 0x16,
        UpcaWCode128 = 0x17, // For Upc-A W/Code 128 Supplemental
        Jan13WCode128 = 0x78, // For Ean/Jan-13 W/Code 128 Supplemental
        Nw7 = 0x18,
        Isbt128 = 0x19,
        MicroPdf = 0x1a,
        Datamatrix = 0x1b,
        Qrcode = 0x1c,
        MicroPdfCca = 0x1d,
        PostnetUs = 0x1e,
        PlanetCode = 0x1f,
        Code32 = 0x20,
        Isbt128Con = 0x21,
        JapanPostal = 0x22,
        AusPostal = 0x23,
        DutchPostal = 0x24,
        Maxicode = 0x25,
        CanadinPostal = 0x26,
        UkPostal = 0x27,
        MacroPdf = 0x28,
        MacroQrCode = 0x29,
        MicroQrCode = 0x2c,
        Aztec = 0x2d,
        AztecRune = 0x2e,
        Distance = 0x2f,
        Rss14 = 0x30,
        RssLimited = 0x31,
        RssExpanded = 0x32,
        Parameter = 0x33,
        Usps4c = 0x34,
        UpuFicsPostal = 0x35,
        Issn = 0x36,
        Scanlet = 0x37,
        Cuecode = 0x38,
        Matrix2of5 = 0x39,
        Upca_2 = 0x48,
        Upce0_2 = 0x49,
        Ean8_2 = 0x4a,
        Ean13_2 = 0x4b,
        Upce1_2 = 0x50,
        CcaEan128 = 0x51,
        CcaEan13 = 0x52,
        CcaEan8 = 0x53,
        CcaRssExpanded = 0x54,
        CcaRssLimited = 0x55,
        CcaRss14 = 0x56,
        CcaUpca = 0x57,
        CcaUpce = 0x58,
        CccEan128 = 0x59,
        Tlc39 = 0x5a,
        CcbEan128 = 0x61,
        CcbEan13 = 0x62,
        CcbEan8 = 0x63,
        CcbRssExpanded = 0x64,
        CcbRssLimited = 0x65,
        CcbRss14 = 0x66,
        CcbUpca = 0x67,
        CcbUpce = 0x68,
        SignatureCapture = 0x69,
        Moa = 0x6a,
        Pdf417Parameter = 0x70,
        Chinese2of5 = 0x72,
        Korean3Of5 = 0x73,
        DatamatrixParam = 0x74,
        CodeZ = 0x75,
        Upca_5 = 0x88,
        Upce0_5 = 0x89,
        Ean8_5 = 0x8a,
        Ean13_5 = 0x8b,
        Upce1_5 = 0x90,
        MacroMicroPdf = 0x9a,
        OcrB = 0xa0,
        OcrA = 0xa1,
        ParsedDriverLicense = 0xb1,
        ParsedUid = 0xb2,
        ParsedNdc = 0xb3,
        DatabarCoupon = 0xb4,
        ParsedXml = 0xb6,
        HanXinCode = 0xb7,
        Calibration = 0xc0,
        Gs1Datamatrix = 0xc1,
        Gs1Qr = 0xc2,
        Mainmark = 0xc3,
        Dotcode = 0xc4,
        GridMatrix = 0xc8,
    }

    /// <summary>
    /// RSM Data Types
    /// </summary>
    public enum RSMDataType
    {
        /// <summary>
        /// Byte – Unsigned char
        /// </summary>
        B,

        /// <summary>
        /// Char – Signed byte
        /// </summary>
        C,

        /// <summary>
        /// Bit flags
        /// </summary>
        F,

        /// <summary>
        /// Word – Short unsigned integer (16 Bits)
        /// </summary>
        W,

        /// <summary>
        /// Sword – Short signed integer (16 Bits)
        /// </summary>
        I,

        /// <summary>
        /// Dword – Long unsigned integer (32 Bits)
        /// </summary>
        D,

        /// <summary>
        /// Sdword – Long signed integer (32 Bits)
        /// </summary>
        L,

        /// <summary>
        /// Array
        /// </summary>
        A,

        /// <summary>
        /// String
        /// </summary>
        S,

        /// <summary>
        /// Action
        /// </summary>
        X
    }

    /// <summary>
    /// Common constants definition class
    /// </summary>
    public static class Constant
    {
        /// Triggered when update error or status
        public const int ScannerUfStatus = 16;

        /// Maximum number of scanners to be connected
        public const int MaxNumDevices = 255;

        /// Video View Finder paaram number
        public const ushort VideoViewFinderParamNum = 0x0144;

        /// Image Filter Type param number
        public const ushort ImageFilterTypeParamNum = 0x0130;  // These values may change with the scanner   

        /// Maximum buffer size
        public const int MaxBuffSize = 1024;

        /// Maximum number of bytes per parameter    
        public const int MaxParamLength = 2;

        /// Maximum number of bytes for serial number
        public const uint MaxSerialNumberLength = 255;

        /// Wave file buffer Size (Default file size Is 10kb)
        public const int WavFileMaxSize = 10240;

    }
}

