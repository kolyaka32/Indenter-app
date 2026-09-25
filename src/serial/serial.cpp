/*
 * Copyright (C) 2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "serial.hpp"


Serial::Serial() {
    #if (SDL_PLATFORM_WINDOWS)
    // Initialize the DCB structure.
    SecureZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);
    #endif
}

bool Serial::tryConnectTo(const ComPort& _port) {
    #if (SDL_PLATFORM_WINDOWS)
    // Open a handle to the specified com port.
    handle = CreateFile(_port.name,
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
    timeouts.ReadIntervalTimeout =         3;
    timeouts.ReadTotalTimeoutConstant =    3;
    timeouts.ReadTotalTimeoutMultiplier =  1;
    timeouts.WriteTotalTimeoutConstant =   3;
    timeouts.WriteTotalTimeoutMultiplier = 1;
    if (!SetCommTimeouts(handle, &timeouts)) {
        logger.important("Can't set timeouts: %d", GetLastError());
        return false;
    }
    logger.additional("Serial reader: BaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d",
        dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);
    #endif
    #if (SDL_PLATFORM_UNIX)
    // Check, if file avaliable for interaction (read and write)
    if (access(_port.name, R_OK | W_OK) == -1) {
        logger.important("Doesn't have permission to open file");
        return false;
    }
    // Trying openning as file
    fd = open(_port.name, O_RDWR | O_NOCTTY);
    if  (fd == -1) {
        logger.important("Can't open file");
        return false;
    }
    // Get current settings
    tcgetattr(fd, &portSettings);
    // Enable NON CANONICAL Mode for Serial Port Comm
    portSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    portSettings.c_cflag |=  CREAD | CLOCAL;  // Turn ON  the receiver of the serial port (CREAD)
    portSettings.c_cflag &= ~CRTSCTS;  // Turn OFF Hardware based flow control RTS/CTS
    // Set 8N1 (8 bits, no parity, 1 stop bit)
    portSettings.c_cflag &= ~PARENB;
    portSettings.c_cflag &= ~CSTOPB;
    portSettings.c_cflag &= ~CSIZE;
    portSettings.c_cflag |=  CS8;
    cfsetispeed(&portSettings, 57600);
    cfsetospeed(&portSettings, 57600);
    // Update new settings to termios structure now
    tcsetattr(fd, TCSANOW, &portSettings);

    // Setting to non-blocking mode
    fcntl(fd, F_SETFL, FNDELAY);

    logger.additional("Serial reader: BaudRate = %d, lflag = %d, cflag = %d",
        portSettings.c_ospeed, portSettings.c_lflag, portSettings.c_cflag);
    #endif
    logger.additional("Correctly oppened serial reader at %s", _port.name);
    return true;
}

void Serial::reset() {
    #if (SDL_PLATFORM_WINDOWS)
    CloseHandle(handle);
    #endif
    #if (SDL_PLATFORM_UNIX)
    close(fd);
    #endif
    logger.additional("Closed serial port");
}

const void* Serial::readData(unsigned long* _length) {
    static char buffer[100];
    static unsigned count=0;
    #if (SDL_PLATFORM_WINDOWS)
    if (ReadFile(handle, buffer, sizeof(buffer), _length, nullptr) && *_length) {
        logger.additional("%4u Read from serial: %d %d", count, *_length, buffer[0]);
        count++;
        return buffer;
    }
    #endif
    #if (SDL_PLATFORM_UNIX)
    if (int length = read(fd, buffer, sizeof(buffer)) > 0) {
        logger.additional("%4u Read from serial: %d %d", count, length, buffer[0]);
        *_length = length;
        count++;
        return buffer;
    }
    #endif
    return nullptr;
}

void Serial::writeData(const char* _data, int _length) {
    #if (SDL_PLATFORM_WINDOWS)
    DWORD length = 0;
    if (WriteFile(handle, _data, _length, &length, nullptr)) {
        logger.additional("Send %2d bytes", length);
    } else {
        logger.additional("Can't send data: %d", GetLastError());
    }
    #endif
    #if (SDL_PLATFORM_UNIX)
    if (int length = write(fd, _data, _length) > 0) {
        logger.additional("Send %2d bytes", length);
    } else {
        logger.additional("Can't send data");
    }
    #endif
}


// Global object implementation
Serial serial;
