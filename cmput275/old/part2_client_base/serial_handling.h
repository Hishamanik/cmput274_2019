#ifndef __SERIAL_HANDLING_H
#define __SERIAL_HANDLING_H

#include "map_drawing.h"

#include "consts_and_types.h"

// communication characters
const char routing_flag = 'R';
const char space = ' ';
const char newline = '\n';
const char end_flag = 'E';

// buffer
const uint16_t buffer_size = 256;

// timeout in seconds
const int routing_timeout = 10000;
const int timeout = 1000;

// function declarations
void routingRequest(const lon_lat_32& start, const lon_lat_32&end);
void desktopCommunication(shared_vars& shared, const lon_lat_32& start, const lon_lat_32& end);
bool readResponse(char* buffer, uint16_t& buffer_len, const unsigned long timeout);

#endif
