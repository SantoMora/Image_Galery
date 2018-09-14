#include<allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include<string.h>
#include "LdobleC.h"



void Galeria();char *Nombre(int opc);
int Imagenes(BITMAP *galeria,BITMAP *galeria2,BITMAP *galeria3,BITMAP *galeria4,BITMAP *buffer, char *nom,TnodoD *listaDC);

int main()
{
    Galeria();
}
END_OF_MAIN();

void Galeria()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,MAXANCHO, MAXALTO, 0, 0);


    BITMAP *buffer = create_bitmap(MAXANCHO,MAXALTO);
    BITMAP *menu1 = load_bitmap("Menus/logo_allegro1.bmp",NULL);
    BITMAP *menu2 = load_bitmap("Menus/logo_allegro2.bmp",NULL);
    BITMAP *menu3 = load_bitmap("Menus/logo_allegro3.bmp",NULL);
    BITMAP *carpetas = load_bitmap("Menus/carpetas.bmp",NULL);
    BITMAP *carpetas1 = load_bitmap("Menus/carpetas1.bmp",NULL);
    BITMAP *carpetas2 = load_bitmap("Menus/carpetas2.bmp",NULL);
    BITMAP *carpetas3 = load_bitmap("Menus/carpetas3.bmp",NULL);
    BITMAP *carpetas4 = load_bitmap("Menus/carpetas4.bmp",NULL);
    BITMAP *carpetas5 = load_bitmap("Menus/carpetas5.bmp",NULL);
    BITMAP *carpetas6 = load_bitmap("Menus/carpetas6.bmp",NULL);
    BITMAP *galeria = load_bitmap("Menus/galeria.bmp",NULL);
    BITMAP *galeria2 = load_bitmap("Menus/galeria2.bmp",NULL);
    BITMAP *galeria3 = load_bitmap("Menus/galeria3.bmp",NULL);
    BITMAP *galeria4 = load_bitmap("Menus/galeria4.bmp",NULL);
    int flag = 0,opc,arch;
    DIR *dir;
    struct dirent *ent;
    char nom[MAXDIR];
    TnodoD listaDC=NULL;

    flag = Menus(menu1,menu2,menu3,buffer);

    if( flag == 1 )
    {
        do{
            arch = 0;
            opc = Carpetas(buffer,carpetas,carpetas1,carpetas2,carpetas3,carpetas4,carpetas5,carpetas6);
            if( opc != 6 )
            {
                strcpy(nom,Nombre(opc));
                dir = opendir (nom);
                if(dir == NULL)
                error("No puedo abrir el directorio");

                while ((ent = readdir (dir)) != NULL)
                {
                    if ( (strcmp(ent->d_name, nom)!=0) && (strcmp(ent->d_name, "..")!=0) && arch == 1)
                    {
                        procesoArchivo(ent->d_name,&listaDC,nom);
                    }
                    arch=1;
                }
                opc = Imagenes(galeria,galeria2,galeria3,galeria4,buffer,nom,&listaDC);
                if(listaDC)
                {
                    printf("Archivos:\n");
                    ImprimirLDC(listaDC);
                    SalirLDC(&listaDC);
                }
                closedir (dir);
            }
            listaDC = NULL;
        }while( opc != 6 );
    }


    destroy_bitmap(buffer);
}

char *Nombre(int opc)
{
    char name[MAXDIR];
    switch(opc)
    {
        case 1:
            strcpy(name,"CARROS");
            break;
        case 2:
            strcpy(name,"PERROS");
            break;
        case 3:
            strcpy(name,"PLAYAS");
            break;
        case 4:
            strcpy(name,"COMIDA");
            break;
        case 5:
            strcpy(name,"ANIMALES");
            break;
    }
    return name;
}

int Imagenes(BITMAP *galeria,BITMAP *galeria2,BITMAP *galeria3,BITMAP *galeria4,BITMAP *buffer, char *nom,TnodoD *listaDC)
{
    int salida = 0;
    TnodoD temp=NULL,nodo=NULL,aux=NULL;

    temp = *listaDC;
    while(salida == 0)
    {
        if(temp)
            draw_sprite(galeria,temp->foto,302,151);
        if( mouse_x > 885 && mouse_x < 972 && mouse_y > 564 && mouse_y < 591 )
        {
            blit(galeria2,buffer,0,0,0,0,MAXANCHO,MAXALTO);
            draw_sprite(galeria2,temp->foto,302,151);
            if( mouse_b & 1 )
            {
                salida = 6;
            }
        }
        else
        {
            if( mouse_x > 948 && mouse_x < 1000 && mouse_y > 263 && mouse_y < 330)
            {
                if( mouse_b & 1 )
                {
                    rest(200);
                    temp = temp->sig;
                }
            }
            else
            {
                if( mouse_x > 0 && mouse_x < 53 && mouse_y > 263 && mouse_y < 330)
                {
                    if( mouse_b & 1 )
                    {
                        rest(200);
                        temp = temp->ant;
                    }
                }
                else
                {
                    if( mouse_x > 9 && mouse_x < 51 && mouse_y > 537 && mouse_y < 590)
                    {
                        if(temp)
                            blit(galeria3,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                        draw_sprite(galeria3,temp->foto,302,151);
                        if( mouse_b & 1 )
                        {
                            rest(200);
                            nodo = temp;
                            if(temp->sig == temp)
                            {
                                temp = NULL;
                                salida = 1;
                            }
                            else
                            {
                                temp = temp->sig;
                            }
                            aux = EliminarLDC(&*listaDC,&nodo);
                            free(aux);
                        }
                    }
                    else
                    {
                        if( mouse_x > 930 && mouse_x < 980 && mouse_y > 7 && mouse_y < 58)
                        {
                            blit(galeria4,buffer,0,0,0,0,MAXANCHO,MAXALTO);
                            draw_sprite(galeria4,temp->foto,302,151);
                            if(mouse_b & 1)
                            {
                                salida = 1;
                            }
                        }
                    }

                }
            }
            blit(galeria,buffer,0,0,0,0,MAXANCHO,MAXALTO);
        }
        show_mouse(screen);
        blit(buffer,screen,0,0,0,0,MAXANCHO,MAXALTO);
    }

    return salida;
}
