#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstring>

int main(int argc, char** argv) {

    if (argc < 3) {
        printf("usage: %s MAC BROADCAST_IP\nexample: %s AA:BB:CC:DD:EE:FF 192.168.1.255\n", argv[0], argv[0]);
        return 1;
    }

    //parse mac adress into 6 bytes 
    unsigned m[6];
    sscanf(argv[1], "%x:%x:%x:%x:%x:%x", m, m + 1, m + 2, m + 3, m + 4, m + 5);

    //magic packet
    unsigned char pkt[102];
    memset(pkt, 0xff, 6);
    for (int i = 6; i < 102; i++) pkt[i] = m[i % 6];


    //destination on port 9
    sockaddr_in a{};
    a.sin_family = AF_INET;
    a.sin_port = htons(9);
    inet_pton(AF_INET, argv[2], &a.sin_addr);

    //SO_BROADCAST
    int s = socket(AF_INET, SOCK_DGRAM, 0), on = 1;
    setsockopt(s, SOL_SOCKET, SO_BROADCAST, &on, sizeof on);
    sendto(s, pkt, sizeof pkt, 0, (sockaddr*)&a, sizeof a);
}