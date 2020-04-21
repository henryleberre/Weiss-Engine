#include "ServerSocket.h"

namespace WS {

	ServerSocket::ServerSocket()
	{
#ifdef __WEISS__OS_WINDOWS
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif // __WEISS__OS_WINDOWS
	}

	ServerSocket::~ServerSocket() { this->Disconnect(); }

	void ServerSocket::Bind(const unsigned int port)
	{
		this->m_socket = socket(AF_INET, SOCK_STREAM, 0);

		if (this->m_socket == INVALID_SOCKET)
			throw std::runtime_error("[SERVER SOCKET] Creation Failed");

		sockaddr_in sockAddr;
		sockAddr.sin_addr.s_addr = INADDR_ANY;
		sockAddr.sin_family      = AF_INET;
		sockAddr.sin_port        = htons(5555);

		if (bind(this->m_socket, (sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
			throw std::runtime_error("[SERVER SOCKET] Binding Failed");

		if (listen(this->m_socket, 0) == SOCKET_ERROR)
			throw std::runtime_error("[SERVER SOCKET] Listening Failed");
	}

	[[nodiscard]] int ServerSocket::Accept() noexcept
	{
		sockaddr_in clientAddr;
		int clientAddrSize = 0;

		const SOCKET client = accept(this->m_socket, (SOCKADDR*)&clientAddr, &clientAddrSize);

		if (client != INVALID_SOCKET)
		{
			this->m_clients.push_back(client);

			return static_cast<int>(this->m_clients.size() - 1u);
		}

		return -1;
	}

	void ServerSocket::Send(const int clientID, const char* data, int length)
	{
		if (length < 0)
			length = static_cast<int>(strlen(data) + 1);

		if (send(this->m_clients[clientID], data, length, 0) == SOCKET_ERROR)
			throw std::runtime_error("[SERVER SOCKET] Could Not Send Data To Client");
	}

	[[nodiscard]] std::pair<std::array<char, 1024u>, size_t> ServerSocket::Receive(const int clientID)
	{
		std::array<char, 1024u> buffer;

		const int iResult = recv(this->m_clients[clientID], buffer.data(), 1024u, 0);

		if (iResult == 0 || iResult == SOCKET_ERROR)
			throw std::runtime_error("[SERVER SOCKET] Error While Receiving Data From Client");

		return { buffer, (size_t)iResult };
	}

	void ServerSocket::Disconnect() noexcept
	{
		this->m_socket = INVALID_SOCKET;

		closesocket(this->m_socket);

#ifdef __WEISS__OS_WINDOWS
		WSACleanup();
#endif // __WEISS__OS_WINDOWS
	}

};