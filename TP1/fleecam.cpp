#include "fleecam.h"

fleecam::fleecam() : posX(0.0),posY(0.0),posZ(0.0),pitchX(0.0),headingY(0.0),rollZ(0.0)
{

}

void fleecam::updatePosX(float i)
{
    posX += i;
}
void fleecam::updatePosY(float i)
{
    posY += i;
}
void fleecam::updatePosZ(float i)
{
    posZ += i;
}
void fleecam::updatePitchX(float i)
{
    pitchX = i;
}
void fleecam::updateHeadingY(float i)
{
    headingY = i;
}
void fleecam::updateRollZ(float i)
{
    rollZ = i;
}
