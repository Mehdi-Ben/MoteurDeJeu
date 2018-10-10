#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QVector3D>
#include <QMatrix4x4>
#include <QKeyEvent>
class camera
{
public:
    camera();
    camera(QVector3D position, QVector3D pointCible, QVector3D axeVertical,float sensibilite, float vitesse);
    void orienter(int xRel, int yRel);
    void deplacer(QKeyEvent* event);
    void lookAt(QMatrix4x4 &modelview);
    void setPointcible(QVector3D pointCible);
    void setPosition(QVector3D position);
    // Getters et Setters

    float getSensibilite() const;
    float getVitesse() const;

    void setSensibilite(float sensibilite);
    void setVitesse(float vitesse);

private:

    float phi;
    float theta;
    QVector3D orientation;

    QVector3D axeVerti;
    QVector3D depLat;

    QVector3D position;
    QVector3D pointCible;

    float sensi;
    float vitesse;
};

#endif // CAMERA_H
