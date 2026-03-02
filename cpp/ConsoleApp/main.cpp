#include <iostream>
#include <string>

#include "../Models/ScalarResults.h"
#include "../RiskSystem/ParallelPricer.h"
#include "../RiskSystem/ScreenResultPrinter.h"
#include "../RiskSystem/SerialPricer.h"
#include "../RiskSystem/SerialTradeLoader.h"
#include "../RiskSystem/StreamingTradeLoader.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int _getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

int main(int argc, char* argv[])
{

    SerialTradeLoader tradeLoader;
    auto allTrades = tradeLoader.loadTrades();
    ScalarResults results;
    ParallelPricer pricer;
    // SerialPricer pricer;
    pricer.price(allTrades, &results);

    // StreamingTradeLoader tradeLoader;
    // ScalarResults results;
    // // SerialPricer pricer;
    // ParallelPricer pricer;
    // tradeLoader.loadAndPrice(&results);

    ScreenResultPrinter screenPrinter;
    screenPrinter.printResults(results);

    std::cout << "Press any key to exit.." << std::endl;
    _getch();

    return 0;
}
