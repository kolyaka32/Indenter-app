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

bool ComPort::updateState() {
    static char lpTargetPath[1000];
    bool previousAvaliable = avaliable;
    avaliable = QueryDosDevice(name, lpTargetPath, 100);

    // Returning true, if changed
    return avaliable != previousAvaliable;
}

bool ComPort::isAvaliable() const {
    return avaliable;
}

const char* ComPort::getName() const {
    return name;
}


Serial::Serial() {
    // Initialize the DCB structure.
    SecureZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);
}

bool Serial::tryConnectTo(const ComPort _port) {
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
    // 57,600 bps, 8 data bits, no parity, and 1 stop bit.
    dcb.BaudRate = 57600;       // baud rate
    dcb.ByteSize = 8;           // data size, xmit and rcv
    dcb.Parity   = NOPARITY;    // parity bit
    dcb.StopBits = ONESTOPBIT;  // stop bit
    if (!SetCommState(handle, &dcb)) {
        // Handle the error.
        logger.additional("Can't set state: %d", GetLastError());
        return false;
    }
    // Setting timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout =         10;
    timeouts.ReadTotalTimeoutConstant =    10;
    timeouts.ReadTotalTimeoutMultiplier =  1;
    timeouts.WriteTotalTimeoutConstant =   10;
    timeouts.WriteTotalTimeoutMultiplier = 1;
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

const void* Serial::readData() {
    //
    DWORD length = 20;
    static char buffer[100];

    if (ReadFile(handle, buffer, sizeof(buffer), &length, nullptr)) {
        static int i=0;  // Counter
        logger.additional("%4d Read from serial", i);
        i++;
        return buffer;
    }
    return nullptr;
}

void Serial::writeData(const char* _data, int _length) {
    DWORD length = 0;
    if (WriteFile(handle, _data, _length, &length, nullptr)) {
        logger.additional("Can't write data: %d", GetLastError());
        return;
    }
}


// Global object implementation
Serial serial;
