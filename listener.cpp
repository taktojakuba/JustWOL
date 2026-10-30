// listener.cpp
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstdio>

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9);
    if (bind(s, reinterpret_cast<sockaddr*>(&addr), sizeof addr) < 0) {
        std::perror("bind");
        return 1;
    }

    unsigned char d[1024];
    sockaddr_in from;
    for (;;) {
        socklen_t len = sizeof from;
        ssize_t n = recvfrom(s, d, sizeof d, 0, reinterpret_cast<sockaddr*>(&from), &len);
        bool ok = n == 102;
        for (int i = 0; ok && i < 6; i++) ok = d[i] == 0xff;
        for (int i = 6; ok && i < 102; i++) ok = d[i] == d[6 + i % 6];
        std::printf("%s %s %02x:%02x:%02x:%02x:%02x:%02x\n", inet_ntoa(from.sin_addr),
                    ok ? "OK" : "BAD", d[6], d[7], d[8], d[9], d[10], d[11]);
        std::fflush(stdout);
    }
}