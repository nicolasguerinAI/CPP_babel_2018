/*
** EPITECH PROJECT, 2018
** Babel
** File description:
** Protocol
*/

#pragma once

#include <string>
#include <cstdint>

namespace protocol {

enum header {
	CONNECT,
	DISCONNECT,
	REQUEST_CALL,
	NO_REPLY,
	END_CALL,
	SERVER_RESPONSE
};

enum messageType {
	CONNECTION,
	CALL,
	SERVER,
	UNDEFINED
};

struct connectionMessage {
	header headerId;
	char clientName[12];
	char ip[15];
	unsigned short port;
};

struct callMessage {
	header headerId;
	char clientName[12];
	char contactName[12];
};

struct serverMessage {
	header headerId;
	char response;
	char ip[15];
	unsigned short port;
};

enum state {
	AVAILABLE,
	UNAVAILABLE
};

typedef uint8_t UINT8;
typedef UINT8* PACKET;
typedef UINT8 PACKET_BUFFER[1024];

#define NAME_LENGTH 12
#define IP_LENGTH 15

class Protocol {
	public:
		Protocol();
		~Protocol();

		PACKET encode(connectionMessage&) const noexcept;
		PACKET encode(callMessage&) const noexcept;
		PACKET encode(serverMessage&) const noexcept;

		messageType getMessageType(PACKET_BUFFER&) const noexcept;
		connectionMessage decodeConnectionMessage(PACKET_BUFFER&) const noexcept;
		callMessage decodeCallMessage(PACKET_BUFFER&) const noexcept;
		serverMessage decodeServerMessage(PACKET_BUFFER&) const noexcept;

	private:
		UINT8 *encodeHeader(UINT8*, header&) const noexcept;
		UINT8 *encodeChar(UINT8*, char&) const noexcept;
		UINT8 *encodeCharArray(UINT8*, char*, char) const noexcept;
		UINT8 *encodeUShort(UINT8*, unsigned short&) const noexcept;

		UINT8 *decodeHeader(UINT8*, header*) const noexcept;
		UINT8 *decodeChar(UINT8*, char*) const noexcept;
		UINT8 *decodeCharArray(UINT8*, char*, char) const noexcept;
		UINT8 *decodeUShort(UINT8*, unsigned short*) const noexcept;
};

}