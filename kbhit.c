#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

int install_kbhit (void) {
    struct termios Term;
    //  enable raw mode
    tcgetattr (0, &Term);
    int Save__c_lflag = Term.c_lflag;
    Term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
    tcsetattr (0, TCSANOW, &Term);
    return Save__c_lflag;
}

    int console_kbhit (void) {
        int byteswaiting;
        ioctl (0, FIONREAD, &byteswaiting);
        return byteswaiting;
    }

        int console_getkey (void) { //  2018.10.18 читать надо все 1-2-3 байта за раз, вот так %/
            int iCount = console_kbhit();
            int iResult = 0;
            fread (&iResult,(iCount<sizeof(iResult)?iCount:sizeof(iResult)),1,stdin);
            return iResult;
        }

void close_kbhit (int Save__c_lflag) {
    //  restore mode
    struct termios Term;
    tcgetattr (0, &Term);
    Term.c_lflag = Save__c_lflag;
    tcsetattr (0, TCSANOW, &Term);
}
