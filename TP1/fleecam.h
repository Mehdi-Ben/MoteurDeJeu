#ifndef FLEECAM_H
#define FLEECAM_H

#include <QWidget>
#include <QVector3D>
#include <QMatrix4x4>
#include <QKeyEvent>

class fleecam
{
public:
    fleecam();
    void updatePosX(float i);
    void updatePosY(float i);
    void updatePosZ(float i);
    void updatePitchX(float i);
    void updateHeadingY(float i);
    void updateRollZ(float i);
    float posX;
    float posY;
    float posZ;

    float pitchX;
    float headingY;
    float rollZ;

private:


};

#endif // FLEECAM_H
