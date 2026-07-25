/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "serial.hpp"


Serial::Serial() {
    // Initialize the DCB structure.
    SecureZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);
}

bool Serial::tryConnectTo(const ComPort& _port) {
    // Open a handle to the specified com port.
    handle = CreateFile(_port.getName(),
        GENERIC_READ | GENERIC_WRITE,
        0,      //  must be opened with exclusive-access
        NULL,   //  default security attributes
        OPEN_EXISTING, //  must use OPEN_EXISTING
        0,      //  not overlapped I/O
        NULL);  //  hTemplate must be NULL for comm devices

    // Checking on creation
    if (handle == INVALID_HANDLE_VALUE) {
        //  Handle the error.
        logger.important("Can't open port %d", GetLastError());
        return false;
    }
    // Fill in some DCB values and set the com state:
    dcb.BaudRate = 57600;       // baud rate
    dcb.ByteSize = 8;           // data size, xmit and rcv
    dcb.Parity   = NOPARITY;    // parity bit
    dcb.StopBits = ONESTOPBIT;  // stop bit
    if (!SetCommState(handle, &dcb)) {
        // Handle the error
        logger.important("Can't set state: %d", GetLastError());
        return false;
    }
    // Setting timeouts
    COMMTIMEOUTS timeouts = {0};
    // ! Set up timings properly
    timeouts.ReadIntervalTimeout =         20;
    timeouts.ReadTotalTimeoutConstant =    20;
    timeouts.ReadTotalTimeoutMultiplier =  2;
    timeouts.WriteTotalTimeoutConstant =   20;
    timeouts.WriteTotalTimeoutMultiplier = 2;
    if (!SetCommTimeouts(handle, &timeouts)) {
        logger.important("Can't set timeouts: %d", GetLastError());
        return false;
    }

    logger.additional("Correctly oppened serial reader at %s", _port.getName());
    logger.additional("Serial reader: BaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d",
        dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);
    return true;
}

void Serial::reset() {
    CloseHandle(handle);
    logger.additional("Closed serial port");
}

const void* Serial::readData(unsigned long* _length) {
    static char buffer[100];

    if (ReadFile(handle, buffer, sizeof(buffer), _length, nullptr) && *_length) {
        static int i=0;  // Counter
        logger.additional("%4d Read from serial: %d", i, *_length);
        i++;
        return buffer;
    }
    return nullptr;
}

void Serial::writeData(const char* _data, int _length) {
    DWORD length = 0;
    if (WriteFile(handle, _data, _length, &length, nullptr)) {
        logger.additional("Send %1d bytes", length);
    } else {
        logger.additional("Can't send data: %d", GetLastError());
    }
}


// Global object implementation
Serial serial;
