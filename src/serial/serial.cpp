/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "serial.hpp"


ComPort::ComPort(int _number)
: avaliable(false) {
    // Changing number in name to correct
    name[3] = '0' + _number;
}

bool ComPort::tryOpen() {
    //  Open a handle to the specified com port.
    handle = CreateFile( name,
        GENERIC_READ | GENERIC_WRITE,
        0,      //  must be opened with exclusive-access
        NULL,   //  default security attributes
        OPEN_EXISTING, //  must use OPEN_EXISTING
        0,      //  not overlapped I/O
        NULL ); //  hTemplate must be NULL for comm devices

    if (handle == INVALID_HANDLE_VALUE) {
        //  Handle the error.
        logger.additional("CreateFile failed with error %d", GetLastError());
        return false;
    }
    logger.additional("Correctly oppened at %s", name);
    return true;
}

Serial::Serial()
: ports {
    {{3}, {4}, {5}, {6}}
} {
    // Initialize the DCB structure.
    SecureZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);

    // Build on the current configuration by first retrieving all current
    /*if (!GetCommState(hCom, &dcb)) {
        // Handle the error
        logger.additional("GetCommState failed with error %d", GetLastError());
        return;
    }

    printCommState(dcb);  //  Output to console

    //  Fill in some DCB values and set the com state: 
    //  57,600 bps, 8 data bits, no parity, and 1 stop bit.
    dcb.BaudRate = 57600;     //  baud rate
    dcb.ByteSize = 8;             //  data size, xmit and rcv
    dcb.Parity   = NOPARITY;      //  parity bit
    dcb.StopBits = ONESTOPBIT;    //  stop bit

    if (!SetCommState(hCom, &dcb)) {
        //  Handle the error.
        logger.additional("SetCommState failed with error %d", GetLastError());
        return;
    }

    //  Get the comm config again.
    /*if (!GetCommState(hCom, &dcb)) {
       //  Handle the error.
       logger.additional("GetCommState failed with error %d.\n", GetLastError());
       return;
    }

    printCommState(dcb);  //  Output to console*/
    /*DWORD length = 20;
    char buffer[20];

    if (ReadFile(hCom, buffer, sizeof(buffer), &length, nullptr)) {
        logger.additional("Read: %s", buffer);
    }

    /*logger.additional("Serial port %s successfully reconfigured", pcCommPort);*/
}

Serial::~Serial() {

}

void Serial::printCommState(DCB dcb) {
    //  Print some of the DCB structure values
    logger.additional("BaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d",
        dcb.BaudRate,
        dcb.ByteSize,
        dcb.Parity,
        dcb.StopBits);
}

void Serial::updateConnections() {
    char lpTargetPath[1000];
    for (int i=0; i < ports.size(); ++i) {
        //ports[i].avaliable = QueryDosDevice(ports[i].name, lpTargetPath, 100);
        /*if (ports[i].avaliable) {
            logger.additional("%s:%s avaliable", ports[i].name, lpTargetPath);
        }*/
    }
}

void Serial::tryConnectTo(int _port) {

}


// Global object implementation
Serial serial;
