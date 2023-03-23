#ifndef _PRE_HEADER_H_
#define _PRE_HEADER_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#if defined(__linux__)
#include <termio.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define gets_s gets

int _getch(void) {
    struct termios tm, tm_old;
    int            fd = 0, ch;

    if(tcgetattr(fd, &tm) < 0) {  // Save the current terminal settings
        return -1;
    }

    tm_old = tm;
    cfmakeraw(&tm);                        // Change the terminal settings to raw mode, in which all input data is processed in bytes
    if(tcsetattr(fd, TCSANOW, &tm) < 0) {  // Settings after changes on settings
        return -1;
    }

    ch = getchar();
    if(tcsetattr(fd, TCSANOW, &tm_old) < 0) {  // Change the settings to what they were originally
        return -1;
    }

    return ch;
}

int _kbhit(void) {
    struct termios oldt, newt;
    int            ch;
    int            oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
#else
#include <conio.h>
#endif

#define ESC_KEY 27

#define TRY_EXECUTE try
#define CATCH_EXCEPTIONS()                                                               \
    catch(const std::logic_error &e) {                                                   \
        std::cerr << "A logic error ocurred! msg=" << e.what() << std::endl;             \
        std::cout << "Press any key to exit!";                                           \
        _getch();                                                                        \
        return -1;                                                                       \
    }                                                                                    \
    catch(const std::runtime_error &e) {                                                 \
        std::cerr << "A runtime error ocurred! msg=" << e.what() << std::endl;           \
        std::cout << "Press any key to exit!";                                           \
        _getch();                                                                        \
        return -1;                                                                       \
    }                                                                                    \
    catch(const std::exception &e) {                                                     \
        std::cerr << "A unknown exception error ocurred! msg=" << e.what() << std::endl; \
        std::cout << "Press any key to exit!";                                           \
        _getch();                                                                        \
        return -1;                                                                       \
    }                                                                                    \
    catch(...) {                                                                         \
        std::cerr << "A unknown exception error ocurred!" << std::endl;                  \
        std::cout << "Press any key to exit!";                                           \
        _getch();                                                                        \
        return -1;                                                                       \
    }

#ifdef WIN32
#define sleepMs(msec) Sleep(msec);
#else
#define sleepMs(msec) sleep((double)msec / 1000);
#endif

#endif  // _PRE_HEADER_H_
