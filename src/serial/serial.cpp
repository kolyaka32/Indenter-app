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
    timeouts.ReadIntervalTimeout =         3;
    timeouts.ReadTotalTimeoutConstant =    3;
    timeouts.ReadTotalTimeoutMultiplier =  1;
    timeouts.WriteTotalTimeoutConstant =   3;
    timeouts.WriteTotalTimeoutMultiplier = 1;
    if (!SetCommTimeouts(handle, &timeouts)) {
        logger.important("Can't set timeouts: %d", GetLastError());
        return false;
    }
    logger.additional("Correctly oppened serial reader at %s", _port.getName());
    logger.additional("Serial reader: BaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d",
        dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);
    return true;
    #endif
    #if (SDL_PLATFORM_UNIX)
    // Trying openning tty port
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if  (fd == -1) {
        // Handle the error
        // ! Add check on type of error
        //logger.important("Can't set state: %d", stderr());
        perror("Failed to open serial port");
        return false;
    }
    // Get current settings
    tcgetattr(fd, &portSettings);
    portSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // Enable NON CANONICAL Mode for Serial Port Comm
    portSettings.c_cflag |=  CREAD | CLOCAL;  // Turn ON  the receiver of the serial port (CREAD)
    portSettings.c_cflag &= ~CRTSCTS;     // Turn OFF Hardware based flow control RTS/CTS
    // Set 8N1 (8 bits, no parity, 1 stop bit)
    portSettings.c_cflag &= ~PARENB;      // No parity
    portSettings.c_cflag &= ~CSTOPB;      // One stop bit
    portSettings.c_cflag &= ~CSIZE;       
    portSettings.c_cflag |=  CS8;         // 8 bits
    cfsetispeed(&portSettings, 57600);
    cfsetospeed(&portSettings, 57600);
    // Update new settings to termios structure now
    tcsetattr(fd, TCSANOW, &portSettings);

    // ! Add tty setup
    logger.additional("Correctly oppened serial reader at %s", _port.getName());
    /*logger.additional("Serial reader: BaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d",
        dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);*/
    return true;
    #endif
}

void Serial::reset() {
    close(fd);
    /*CloseHandle(handle);*/
    logger.additional("Closed serial port");
}

const void* Serial::readData(unsigned* _length) {
    static char buffer[100];

    /*if (ReadFile(handle, buffer, sizeof(buffer), _length, nullptr) && *_length) {
        static int i=0;  // Counter
        logger.additional("%4d Read from serial: %d %d", i, *_length, buffer[0]);
        i++;
        return buffer;
    }*/
    return nullptr;
}

void Serial::writeData(const char* _data, int _length) {
    /*DWORD length = 0;
    if (WriteFile(handle, _data, _length, &length, nullptr)) {
        logger.additional("Send %1d bytes", length);
    } else {
        logger.additional("Can't send data: %d", GetLastError());
    }*/
}


// Global object implementation
Serial serial;
