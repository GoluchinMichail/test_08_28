#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "ring_buffer.h"
#include "received-processed.h"

void* Processed (void* args) {

    _Param_Processed *param = args;

    //puts ("Thread start ...");

    while (!param->booStop) {

        // ждать сигнал о пополнении буфера
        sem_wait (&param->semaRing);

        _Packet Packet;
        while (ReadFromRingBuffer (&param->Ring, &Packet)) {

            int imd5 = Calc_MD5 (&Packet);

            printf ("Processed: %4i  %lu  %s\n", Packet.Head.iNumber, clock(), (!imd5 ? "PASS" : "FAIL"));

            // печать начала и окончания пакета (подразумевается кириллица UTF-8)
            uint16_t *str = Packet.aBuffer;
            printf ("  >");
            for (int i=0;i<16;i++) {
                putchar (htons(str[i])>>8);
                putchar (htons(str[i]));
            }
            printf ("...");
            str = &Packet.aBuffer[Packet.Head.iWords-16];
            for (int i=0;i<16;i++) {
                putchar (htons(str[i])>>8);
                putchar (htons(str[i]));
            }
            puts ("<");

            // сон на указанное время
            usleep (param->iSleep_ms *1000);
        }
        
    } // while () ...

    //puts ("Thread exit");
}
