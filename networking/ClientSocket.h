#pragma once

#include "../common/Include.h"

namespace WS {

	class ClientSocket {
	private:
		SOCKET m_socket = INVALID_SOCKET;

	public:
		ClientSocket();

		~ClientSocket();

		void Connect(const char* host, const unsigned int port);

		void Send(const char* data, int length = -1);

		[[nodiscard]] std::pair<std::array<char, 1024u>, size_t> Receive();

		void Disconnect() noexcept;
	};

}; // WS