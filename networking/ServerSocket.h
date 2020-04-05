#pragma once

#include "../common/Include.h"

class ServerSocket {
private:
	SOCKET m_socket = INVALID_SOCKET;

	std::vector<SOCKET> m_clients;

public:
	ServerSocket();

	~ServerSocket();

	void Bind(const unsigned int port);

	[[nodiscard]] int Accept() noexcept;

	void Send(const int clientID, const char* data, int length = -1);

	[[nodiscard]] std::pair<std::array<char, 1024u>, size_t> Receive(const int clientID);

	void Disconnect() noexcept;
};