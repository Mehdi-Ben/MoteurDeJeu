#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif
#include "camera.h"

camera::camera(): phi(0.0), theta(0.0), orientation(), axeVerti(0, 0, 1), depLat(), position(), pointCible(), sensi(0.0),vitesse(0.0)
{

}

camera::camera(QVector3D position, QVector3D pointCible, QVector3D axeVerti,float sensibilite, float vitesse) : phi(0), theta(0), orientation(), axeVerti(axeVerti),
                                                                          depLat(), position(position), pointCible(pointCible), sensi(sensibilite), vitesse(vitesse)
{

    setPointcible(pointCible);

}

void camera::orienter(int xRel, int yRel)
{
    // Récupération des angles

    phi += -yRel * sensi;
    theta += -xRel * sensi;


    // Limitation de l'angle phi

    if(phi > 89.0)
        phi = 89.0;

    else if(phi < -89.0)
        phi = -89.0;


    // Conversion des angles en radian

    float phiRadian = phi * M_PI / 180;
    float thetaRadian = theta * M_PI / 180;


    // Si l'axe vertical est l'axe X

    if(axeVerti.x() == 1.0)
    {
        // Calcul des coordonnées sphériques

        orientation.setX(sin(phiRadian));
        orientation.setY(cos(phiRadian) * cos(thetaRadian));
        orientation.setZ(cos(phiRadian) * sin(thetaRadian));
    }


    // Si c'est l'axe Y

    else if(axeVerti.y() == 1.0)
    {
        // Calcul des coordonnées sphériques

        orientation.setX(cos(phiRadian) * sin(thetaRadian));
        orientation.setY(sin(phiRadian));
        orientation.setZ(cos(phiRadian) * cos(thetaRadian));
    }


    // Sinon c'est l'axe Z

    else
    {
        // Calcul des coordonnées sphériques

        orientation.setX(cos(phiRadian) * cos(thetaRadian));
        orientation.setY(cos(phiRadian) * sin(thetaRadian));
        orientation.setZ(sin(phiRadian));
    }


    // Calcul de la normale

    depLat.crossProduct(axeVerti, orientation);
    depLat.normalize();


    // Calcul du point ciblé pour OpenGL

    pointCible = position + orientation;
}

void camera::deplacer(QKeyEvent* event)
{
    // Gestion de l'orientation

    //if(input.mouvementSouris())
      //  orienter(input.getXRel(), input.getYRel());


    // Avancée de la caméra
    if(event->key() == Qt::Key_Up)
    {
        position = position + orientation * vitesse;
        pointCible = position + orientation;
    }


    // Recul de la caméra

    if(event->key() == Qt::Key_Down)
    {
        position = position - orientation * vitesse;
        pointCible = position + orientation;
    }


    // Déplacement vers la gauche

    if(event->key() == Qt::Key_Left)
    {
        position = position + depLat * vitesse;
        pointCible = position + orientation;
    }


    // Déplacement vers la droite

    if(event->key() == Qt::Key_Right)
    {
        position = position - depLat * vitesse;
        pointCible = position + orientation;
    }
}

void camera::lookAt(QMatrix4x4 &modelview)
{
    // Actualisation de la vue dans la matrice

    modelview.lookAt(position, pointCible, axeVerti);
}

void camera::setPointcible(QVector3D pointCible)
{
    // Calcul du vecteur orientation

    orientation = pointCible - position;
    orientation.normalize();

    // Si l'axe vertical est l'axe X

        if(axeVerti.x() == 1.0)
        {
            // Calcul des angles

            phi = asin(orientation.x());
            theta = acos(orientation.y() / cos(phi));

            if(orientation.y() < 0)
                theta *= -1;
        }


        // Si c'est l'axe Y

        else if(axeVerti.y() == 1.0)
        {
            // Calcul des angles

            phi = asin(orientation.y());
            theta = acos(orientation.z() / cos(phi));

            if(orientation.z() < 0)
                theta *= -1;
        }


        // Sinon c'est l'axe Z

        else
        {
            // Calcul des angles

            phi = asin(orientation.x());
            theta = acos(orientation.z() / cos(phi));

            if(orientation.z() < 0)
                theta *= -1;
        }


        // Conversion en degrés

        phi = phi * 180 / M_PI;
        theta = theta * 180 / M_PI;
}

float camera::getSensibilite() const
{
    return sensi;
}


float camera::getVitesse() const
{
    return vitesse;
}


void camera::setSensibilite(float sensibilite)
{
    sensi = sensibilite;
}


void camera::setVitesse(float vite)
{
    vitesse = vite;
}

void camera::setPosition(QVector3D pos)
{
    // Mise à jour de la position

    position = pos;


    // Actualisation du point ciblé

    pointCible = position + orientation;
}

