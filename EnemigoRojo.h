#ifndef ENEMIGOROJO_H
#define ENEMIGOROJO_H

#include "Enemigo.h"

class EnemigoRojo : public Enemigo
{
    public:
        int estado;
        int frame_estado;
        int estadoRandom();
        bool estoyCerca();
        void cambiarEstado(int estado);
        EnemigoRojo(SDL_Renderer* renderer,list<Personaje*> *personajes);
        virtual ~EnemigoRojo();

        void act();
    protected:
    private:
};

#endif // ENEMIGOROJO_H
