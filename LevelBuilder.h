#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Stone.h"

class LevelBuilder {
public:
    struct Settings {
        int   columns    = 8;
        int   rows       = 10;
        float gap        = 2.f;
        float topOffset  = 50.f;
        float blockH     = 25.f;
    };

    static std::vector<Stone> buildDefault(unsigned int windowW, const Settings& s);
    static float blockWidth(unsigned int windowW, const Settings& s);
};