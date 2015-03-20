#ifndef SHO_H
#define SHO_H

#include "Personaje.h"

class Sho : public Personaje
{
    public:
        int frames_atacando,estado,frame_estado;
        bool trigger_atacar;
        Sho(SDL_Renderer* renderer,list<Personaje*> *personajes);
        void act();
        void cambiarEstado(int estado);
        void actMoving();
        void actAttacking();
        void setAttackingStartup();
        void setAttackingActive();
        void setAttackingRecovery();
        void setIdle();
        virtual ~Sho();
        bool soySho();
    protected:
    private:
};

#endif // SHO_H
