#ifndef FLANK_H
#define FLANK_H


using typeSpeed = uint8_t;
using typeTime = uint16_t;

struct Flank{
    typeSpeed sideSpeed{50};
    typeTime sideTime{10};
    typeSpeed towardsSideSpeed{10};
    typeSpeed oppositeSideSpeed{90};
    typeTime diagonalTime{10};
    typeSpeed frontSpeed{70};
    typeTime frontTime{10};
    typeSpeed fullFrontSpeed{100};
    typeTime fullFrontTime{10};

    Flank()
    {}
};

extern Flank flank;

#endif