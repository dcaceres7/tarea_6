#ifndef ENEMIGOVERDE_H
#define ENEMIGOVERDE_H

#include "Enemigo.h"

class EnemigoVerde : public Enemigo
{
    public:
    int estado;
        int frame_estado;
        int estadoRandom();
        bool estoyCerca();
        void cambiarEstado(int estado);

        EnemigoVerde(SDL_Renderer* renderer,list<Personaje*> *personajes);
        virtual ~EnemigoVerde();
        void act();
    protected:
    private:
};

#endif // ENEMIGOVERDE_H
