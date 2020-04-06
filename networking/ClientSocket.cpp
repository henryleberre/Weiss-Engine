#include "ClientSocket.h"

ClientSocket::ClientSocket()
{
#ifdef __WEISS__OS_WINDOWS
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif // __WEISS__OS_WINDOWS
}

ClientSocket::~ClientSocket() { this->Disconnect(); }

void ClientSocket::Connect(const char* host, const unsigned int port)
{
	sockaddr_in sockAddr;
	sockAddr.sin_addr.s_addr = inet_addr(host);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(port);

	this->m_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (this->m_socket == INVALID_SOCKET)
		throw std::runtime_error("[CLIENT SOCKET] Creation Failed");

	if (connect(this->m_socket, (sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
		throw std::runtime_error("[CLIENT SOCKET] Failed To Connect");
}

void ClientSocket::Send(const char* data, int length)
{
	if (length < 0)
		length = static_cast<int>(strlen(data) + 1u);

	if (send(this->m_socket, data, length, 0) == SOCKET_ERROR)
		throw std::runtime_error("[CLIENT SOCKET] Error While Sending Data");
}

[[nodiscard]] std::pair<std::array<char, 1024u>, size_t> ClientSocket::Receive()
{
	std::array<char, 1024u> buffer;

	const int iResult = recv(this->m_socket, buffer.data(), 1024u, 0);

	if (iResult == 0 || iResult == SOCKET_ERROR)
		throw std::runtime_error("[CLIENT SOCKET] Error While Receiving Data");

	return { buffer, (size_t)iResult };
}

void ClientSocket::Disconnect() noexcept
{
	this->m_socket = INVALID_SOCKET;

	closesocket(this->m_socket);

#ifdef __WEISS__OS_WINDOWS
	WSACleanup();
#endif // __WEISS__OS_WINDOWS
}