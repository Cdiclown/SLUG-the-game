#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

class Comandi
{
private:
    WINDOW *comandi;

public:
    Comandi() = default;
    Comandi(WINDOW *);
    void pulisci();
};