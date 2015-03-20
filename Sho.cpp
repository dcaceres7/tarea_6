#include "Sho.h"

Sho::Sho(SDL_Renderer* renderer,list<Personaje*> *personajes)
{
    ifstream in("personaje_sho.txt");
    if(!in)
    {
        cout<<"Error no se encontro el archivo!"<<endl;
        return;
    }

    string animacion;
    while(in>>animacion)
    {
        string llave;
        in>>llave;
        string path;
        in>>path;
        mapa_texturas[enumStringToInt(animacion)] = new vector<SDL_Texture*>();
        while(path!="}")
        {
            mapa_texturas[enumStringToInt(animacion)]->push_back(IMG_LoadTexture(renderer,path.c_str()));
            in>>path;
        }
    }

    estado_actual = DERECHA;

    rect.x = 0;
    rect.y = 0;

    estado = INICIO;
    frame_estado = 0;

    init(renderer,personajes);
    frames_atacando=0;
    trigger_atacar=false;
}

void Sho::setAttackingStartup()
{
    if(orientacion=='r')
    {
        setAnimacion(ANIMACION_ATACANDO_STARTUP_RIGHT);
    }else
    {
        setAnimacion(ANIMACION_ATACANDO_STARTUP_LEFT);
    }
}

void Sho::setAttackingActive()
{
    if(orientacion=='r')
    {
        setAnimacion(ANIMACION_ATACANDO_ACTIVE_RIGHT);
    }else
    {
        setAnimacion(ANIMACION_ATACANDO_ACTIVE_LEFT);
    }
    atacando=true;
}

void Sho::setAttackingRecovery()
{
    if(orientacion=='r')
    {
        setAnimacion(ANIMACION_ATACANDO_RECOVERY_RIGHT);
    }else
    {
        setAnimacion(ANIMACION_ATACANDO_RECOVERY_LEFT);
    }
    atacando=false;
}

void Sho::setIdle()
{
    if(orientacion=='r')
    {
        setAnimacion(ANIMACION_IDLE_RIGHT);
    }else
    {
        setAnimacion(ANIMACION_IDLE_LEFT);
    }
    trigger_atacar=false;
}


void Sho::cambiarEstado(int estado)
{
    this->estado = estado;
    frame_estado = 0;
}

void Sho::actMoving()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates[SDL_SCANCODE_SPACE])
    {
        trigger_atacar = true;
        frames_atacando=0;
        setAttackingStartup();
    }
    else
    {
        if(currentKeyStates[SDL_SCANCODE_W])
        {
            rect.y--;
        }
        else if(currentKeyStates[SDL_SCANCODE_S])
        {
            rect.y++;
        }

        if(currentKeyStates[SDL_SCANCODE_D])
        {
            orientacion='r';
            rect.x++;
            setAnimacion(ANIMACION_WALKING_RIGHT);
        }
        else if(currentKeyStates[SDL_SCANCODE_A])
        {
            orientacion='l';
            rect.x--;
            setAnimacion(ANIMACION_WALKING_LEFT);
        }
        else
        {
            if(orientacion=='r')
            {
                setAnimacion(ANIMACION_IDLE_RIGHT);
            }
            else
            {
                setAnimacion(ANIMACION_IDLE_LEFT);
            }
        }
    }
}


void Sho::actAttacking()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    frames_atacando++;
    if(frames_atacando==30)
    {
        setAttackingActive();
    }
    if(frames_atacando==60)
    {
        setAttackingRecovery();
    }
    if(frames_atacando==90)
    {
        setIdle();
    }

 switch(estado)
    {


        case ATACANDO_STARTUP:
            if(frame_estado%200==0)
            {
                atacando = true;
                cambiarEstado(ATACANDO_ACTIVE);
                if(orientacion=='r')
                    setAnimacion(ANIMACION_ATACANDO_ACTIVE_RIGHT);
                else
                    setAnimacion(ANIMACION_ATACANDO_ACTIVE_LEFT);
            }
        break;

        case ATACANDO_ACTIVE:
            if(frame_estado%200==0)
            {
                atacando = false;
                cambiarEstado(ATACANDO_RECOVERY);
                if(orientacion=='r')
                    setAnimacion(ANIMACION_ATACANDO_RECOVERY_RIGHT);
                else
                    setAnimacion(ANIMACION_ATACANDO_RECOVERY_LEFT);
            }
        break;

        case ATACANDO_RECOVERY:
            if(frame_estado%200==0)
            {
                cambiarEstado(INICIO);
                setAnimacion(ANIMACION_IDLE_RIGHT);
            }
        break;

    }


    attackCheck();
}



void Sho::act()
{
    if(trigger_atacar)
    {
        actAttacking();
    }
    else
    {
        actMoving();
    }
}

Sho::~Sho()
{
    //dtor
}

bool Sho::soySho()
{
    return true;
}
