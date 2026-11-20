
#ifndef CONFIG_H
#define CONFIG_H

using typeSpeed = uint8_t;
using typeTime = uint16_t;

struct Config{
    const typeTime motionDelay{1};
    const typeTime reverseTime{400}; // detect linie/mansalier full
    const typeSpeed  reverseSpeed{50}; // detect linie/mansalier
    const typeSpeed  leftSpeed{50}; // detect linie/mansalier
    const typeSpeed  rightSpeed{50}; // detect linie/mansalier
    const typeTime universalTime{400}; // detect linie/mansalier timp
    const typeSpeed  fullFrontSpeed{100};
    const typeTime fullFrontTime{1};
    const typeSpeed  frontSpeed{70}; // senzor central
    const typeTime frontTime{1}; // senzor central
    const typeSpeed  towardsDiagonalSideSpeed{10}; // diagonal lateral
    const typeSpeed  oppositeDiagonalSideSpeed{100}; // diagonal lateral
    const typeTime diagonalTime{1}; // diagonal lateral timp
    const typeSpeed sideSpeed{70}; // full lateral
    const typeTime sideTime{1}; // full lateral
    const typeSpeed nothingSeenSpeed{30}; // default/start
    const typeTime nothingSeenTime{1}; // default/start
    const typeSpeed diagonalAndMiddleSpeed{5}; // diagonal+middle
    const typeSpeed oppositeDiagonalAndMiddleSpeed{100}; // diagonal+middle
    const typeTime diagonalAndMiddleTime{1}; // diagonal+middle
    const typeSpeed sideAndDiagonalSpeed{0}; // diagonal+side
    const typeSpeed oppositeSideAndDiagonalSpeed{90}; // diagonal+side
    const typeTime sideAndDiagonalTime{1}; // diagonal+side
    const typeTime sideFlagTime{300};
    const typeSpeed sideFlagSpeed{60};



    Config()

    {}
};

extern Config config;



#endif