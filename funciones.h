#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "funciones_enunciado.h"
#include <math.h>
#define TRUE 1
#define FALSE 0
#include "funciones.h"
#define DELTA 0.01 
typedef char booleano;

typedef struct
{
    t_coordenada pelota0;
    t_coordenada pelota1;
    t_coordenada pelota2;

}t_pelota;

/* aqu� deben declarar sus prototipos de funciones */
char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje);
void solucionTP(t_juego* juegos);
float alturaGolpe(float* hjugador);
float alturaPelotaTiempo_f(float tiempo, float *velocidadInicial);
float alturaMaximaPelota_f(float* alturaGolpe, float* alturaMaximaPelotaPie);
float alturaMaximaPelotaPie_f(float* velocidadInicial);
float tiempoAlcanceAlturaMaxima_f(float* velocidadInicial);
float velocidadInicialTiempo_f(float* tiempoEntreToques);
float velocidadInicialAltura_f(float* hmaxpelota, float* alturaGolpe);
float golpesPorMinuto_f(float* tiempoEntreToques);
float tiempoEntreToques_f(float* golpesPorMinuto);
void resolverTiempoEntreToques_f(t_juego* juegos, float* resolverTiempoEntreToques);
void resolverAlturaMaxPelota_f(t_juego* juegos, float* resolverAlturaMaxPelota);
void resolverGolpesPorMinuto_f(t_juego* juegos, float* resolverGolpesPorMinuto); //acordarse si trabajar en float o int
float distanciaRecorrida_f(float* alturaGolpe,float* alturaMaximaDeLaPelota,float* golpesPorMinuto, float duracionJuego);
float alturaEnTiempoResto_f(float* velocidadInicial, float tiempoTransformado, float* alturaGolpe);
void estanPuntosAlineados_f(t_pelota* pelotas, t_juego* juego, int* cantidadAlineaciones,int* banderaAlineado,const float currentTime);
void resolverAlineaciones_f(t_juego* juegos, int j);

#endif // FUNCIONES_H_INCLUDED
