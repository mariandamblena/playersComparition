#include "funciones.h"


char obtenerValorPorTeclado(const char *opcionesValidas, const char *primerMensaje, const char *segundoMensaje) {
    char c;
    int i = 0;

    while (1) {
        printf("%s", primerMensaje);
        scanf(" %c", &c); // Usamos " %c" para eliminar cualquier carácter en blanco o salto de línea previo.

        while (opcionesValidas[i] != '\0') {
            if (c == opcionesValidas[i]) {
                return c;
            }
            i++;
        }

        i = 0; // Reiniciamos i para la siguiente iteración.
        printf("%s\n", segundoMensaje);
    }
}

void solucionTP(t_juego* juegos)
{

    float resolverTiempoEntreToques[3]={1.5,3,5}, resolverGolpesPorMinuto[3]={10,15,30}, resolverAlturaMaxPelota[3]={3,11.11,14.14};


    int  i, j;


        for (i = 0; i < 3; i++)  // Este bucle recorre los juegos y le asigna a cada jugador el valor que necesita para calcular las demas variables
        {
            resolverTiempoEntreToques_f(&(juegos[i]), &resolverTiempoEntreToques[i]);
            resolverGolpesPorMinuto_f(&(juegos[i]), &resolverGolpesPorMinuto[i]);
            resolverAlturaMaxPelota_f(&(juegos[i]), &resolverAlturaMaxPelota[i]);

        }

        for (j = 0; j < 3; j++)  // Este bucle recorre los juegos y le asigna a cada juego las alineaciones
        {
            resolverAlineaciones_f(&(juegos[j]), j);
        }


}

float alturaGolpe_f(float* hjugador) //EN CM
{
    if (*hjugador > 1.50) {
        return (*hjugador) * 0.15;
    } else if (*hjugador < 1.50) {
        return (*hjugador) * 0.1;
    } else {
        // Maneja el caso cuando hmaxpelota es igual o menor que 0
        return 00.0; // definir que valor pasar.
    }

}

float alturaPelotaTiempo_f(float tiempo, float *velocidadInicial) //calcula la altura de la pelota en un momento dado h(t) // EN M
{
    float altura = (*velocidadInicial) * (tiempo) + 0.5f * 9.8 * (tiempo) * (tiempo);
    return altura;
}

float alturaMaximaPelota_f(float* alturaGolpe, float* alturaMaximaPelotaPie) //calcula la altura maxima de pelota //EN M
{
    return ((*alturaGolpe)+(*alturaMaximaPelotaPie));
}

float alturaMaximaPelotaPie_f(float* velocidadInicial) //calcula la altura maxima de pelota //EN M
{
    float v02 = pow(*velocidadInicial, 2);
    float hmaxpelota = v02 / (2 * 9.8);
    return hmaxpelota;
}

float tiempoAlcanceAlturaMaxima_f(float* velocidadInicial) // EN SEG
{
    float tiempo = (*velocidadInicial / 9.8);
    return tiempo;
}

float velocidadInicialTiempo_f(float* tiempoEntreToques) //EN M/S entra el tiempo que tarda en subir y bajar
{
    return ((*tiempoEntreToques / 2)*9.8);
}

float velocidadInicialAltura_f(float* hmaxpelota, float* alturaGolpe) {
    float g = 9.8; // Aceleración debida a la gravedad en m/s^2
    return sqrt(2 * g * ((*hmaxpelota)-(*alturaGolpe)));
}

float golpesPorMinuto_f(float* tiempoEntreToques) //
{
    float golpesPorMin = (60 / (*tiempoEntreToques));
    return golpesPorMin;

}

float tiempoEntreToques_f(float* golpesPorMinuto) //EN SEGUNDOS
{
    float tiempoEntreToques = (60 / *golpesPorMinuto);
    return tiempoEntreToques;

}

float distanciaRecorrida_f(float* alturaGolpe,float* alturaMaximaDeLaPelota,float* golpesPorMinuto, float duracionJuego)
{
    return ((*alturaMaximaDeLaPelota - *alturaGolpe)*2*(*golpesPorMinuto)*duracionJuego); // duracionJuego es en minutos
}

void resolverTiempoEntreToques_f(t_juego* juegos, float* resolverTiempoEntreToques) // funcion que calcula los parametros de punto 1,2,3,4,5 en base al tiempo entre toques
{
    float alturaMaxPelotaPie;

    juegos->jugadores[0].velocidadInicial = velocidadInicialTiempo_f(resolverTiempoEntreToques);
    alturaMaxPelotaPie = alturaMaximaPelotaPie_f(&juegos->jugadores[0].velocidadInicial);
    juegos->jugadores[0].golpesPorMinuto = golpesPorMinuto_f(resolverTiempoEntreToques);
    juegos->jugadores[0].alturaGolpe = alturaGolpe_f(&juegos->jugadores[0].estatura);
    juegos->jugadores[0].alturaMaximaDeLaPelota = alturaMaximaPelota_f(&juegos->jugadores[0].alturaGolpe, &alturaMaxPelotaPie);
    juegos->jugadores[0].distanciaRecorrida = distanciaRecorrida_f(&juegos->jugadores[0].alturaGolpe, &juegos->jugadores[0].alturaMaximaDeLaPelota, &juegos->jugadores[0].golpesPorMinuto,3);
}

void resolverGolpesPorMinuto_f(t_juego* juegos, float* resolverGolpesPorMinuto) // funcion que calcula los parametros de punto 1,2,3,4,5 en base a golpes por minuto
{
    float tiempoEntreToques, alturaMaxPelotaPie;

    juegos->jugadores[1].golpesPorMinuto = *resolverGolpesPorMinuto;
    tiempoEntreToques = tiempoEntreToques_f(resolverGolpesPorMinuto);
    juegos->jugadores[1].velocidadInicial = velocidadInicialTiempo_f(&tiempoEntreToques);
    alturaMaxPelotaPie = alturaMaximaPelotaPie_f(&juegos->jugadores[1].velocidadInicial);
    juegos->jugadores[1].alturaGolpe = alturaGolpe_f(&juegos->jugadores[1].estatura);
    juegos->jugadores[1].alturaMaximaDeLaPelota = alturaMaximaPelota_f(&juegos->jugadores[1].alturaGolpe, &alturaMaxPelotaPie);
    juegos->jugadores[1].distanciaRecorrida = distanciaRecorrida_f(&juegos->jugadores[1].alturaGolpe, &juegos->jugadores[1].alturaMaximaDeLaPelota, &juegos->jugadores[1].golpesPorMinuto,3);
}

void resolverAlturaMaxPelota_f(t_juego* juegos, float* resolverAlturaMaxPelota) // funcion que calcula los parametros de punto 1,2,3,4,5 en base altura maxima 
{
    float tiempoAlturaMaxPelota, tiempoEntreToques, alturaMaxPelotaPie;

    juegos->jugadores[2].alturaGolpe = alturaGolpe_f(&juegos->jugadores[2].estatura);
    juegos->jugadores[2].alturaMaximaDeLaPelota = *resolverAlturaMaxPelota;
    juegos->jugadores[2].velocidadInicial = velocidadInicialAltura_f(resolverAlturaMaxPelota,&juegos->jugadores[2].alturaGolpe);
    alturaMaxPelotaPie = alturaMaximaPelotaPie_f(&juegos->jugadores[2].velocidadInicial);
    tiempoAlturaMaxPelota = tiempoAlcanceAlturaMaxima_f(&juegos->jugadores[2].velocidadInicial);
    tiempoEntreToques = tiempoAlturaMaxPelota * 2;
    juegos->jugadores[2].golpesPorMinuto = golpesPorMinuto_f(&tiempoEntreToques);
    juegos->jugadores[2].distanciaRecorrida = distanciaRecorrida_f(&juegos->jugadores[2].alturaGolpe, &juegos->jugadores[2].alturaMaximaDeLaPelota, &juegos->jugadores[2].golpesPorMinuto,3);

}

float alturaEnTiempoResto_f(float* velocidadInicial, float tiempoTransformado, float* alturaGolpe)
{
    float altura = (((*alturaGolpe)/100)+((*velocidadInicial) * (tiempoTransformado)) - ((0.5) * (9.81) * (powf((tiempoTransformado), 2))));
    return fabs(altura); // Devolver el valor absoluto de la altura
}

void estanPuntosAlineados_f(t_pelota* pelotas, t_juego* juego, int* cantidadAlineaciones,int* banderaAlineado,const float currentTime)
{
    // Calcula las pendientes entre a y b, y entre b y c
    float pendiente1 = (pelotas->pelota1.y - pelotas->pelota0.y) / (pelotas->pelota1.x - pelotas->pelota0.x);
    float pendiente2 = (pelotas->pelota2.y - pelotas->pelota1.y) / (pelotas->pelota2.x - pelotas->pelota1.x);
    float pendiente = ((pendiente1 + pendiente2)/2);
    float tms = 0;

    // Compara las pendientes utilizando el valor DELTA
    if (fabs(pendiente1 - pendiente2) < DELTA)
    {
        if(*banderaAlineado == 0) //si es la primera vez q se alinea
        {
            *banderaAlineado = 1;
            juego->alineamientos[*cantidadAlineaciones].pendiente = pendiente; //cantidad de alineaciones es el numero que entra de afuera, que cuenta las cantidades de alineaciones del jguego (3min)
            juego->alineamientos[*cantidadAlineaciones].instanteInicial.minuto = (currentTime / 60);
            juego->alineamientos[*cantidadAlineaciones].instanteInicial.segundo = fmodf(currentTime, 60 );
            juego->alineamientos[*cantidadAlineaciones].instanteInicial.milisegundo = fmodf((currentTime*1000), 1000 );
            juego->alineamientos[*cantidadAlineaciones].pos1.x = pelotas->pelota0.x;
            juego->alineamientos[*cantidadAlineaciones].pos1.y = pelotas->pelota0.y;
            juego->alineamientos[*cantidadAlineaciones].pos2.x = pelotas->pelota1.x;
            juego->alineamientos[*cantidadAlineaciones].pos2.y = pelotas->pelota1.y;
            juego->alineamientos[*cantidadAlineaciones].pos3.x = pelotas->pelota2.x;
            juego->alineamientos[*cantidadAlineaciones].pos3.y = pelotas->pelota2.y;
            juego->alineamientos[*cantidadAlineaciones].duracion = 0;
            (*cantidadAlineaciones)++;
            tms = currentTime;
        }
        else
        {
             if ((fabs(juego->alineamientos[*cantidadAlineaciones-1].pendiente) - pendiente) < DELTA )//si siguen alineadas
             {
                // tengo que sumar el tiempo acumulado
                juego->alineamientos[*cantidadAlineaciones].duracion = tms-currentTime;
             }
             else{
                juego->alineamientos[*cantidadAlineaciones].pendiente = pendiente; //cantidad de alineaciones es el numero que entra de afuera, que cuenta las cantidades de alineaciones del jguego (3min)
                juego->alineamientos[*cantidadAlineaciones].instanteInicial.minuto = (currentTime / 60);
                juego->alineamientos[*cantidadAlineaciones].instanteInicial.segundo = fmodf(currentTime, 60 );
                juego->alineamientos[*cantidadAlineaciones].instanteInicial.milisegundo = fmodf((currentTime*1000), 1000 );
                juego->alineamientos[*cantidadAlineaciones].pos1.x = pelotas->pelota0.x;
                juego->alineamientos[*cantidadAlineaciones].pos1.y = pelotas->pelota0.y;
                juego->alineamientos[*cantidadAlineaciones].pos2.x = pelotas->pelota1.x;
                juego->alineamientos[*cantidadAlineaciones].pos2.y = pelotas->pelota1.y;
                juego->alineamientos[*cantidadAlineaciones].pos3.x = pelotas->pelota2.x;
                juego->alineamientos[*cantidadAlineaciones].pos3.y = pelotas->pelota2.y;
                juego->alineamientos[*cantidadAlineaciones].duracion = 0;
                (*cantidadAlineaciones)++;
             }

        }

    }
    else
    {
        *banderaAlineado = 0; // no estan alineado
    }

}

void resolverAlineaciones_f(t_juego* juegos, int j) {
    const float stepTime = 0.001;
    float t = 180, tiempoTransformado[3]={0,0,0},tiempoJugador[3]={0,0,0};
    int banderaAlineado = 0, cantidadAlineaciones = 0;
    float posicionJugador0[3]={1.5,1.6,3},posicionJugador1[3]={0.5,0.8,1}, posicionJugador2[3]={0,0,0}; //messi jugador0, dimaria jugador1, acunia jugador2
    t_pelota pelotas;

    for (float currentTime = 0.0; currentTime <= t; currentTime += stepTime) {

        tiempoJugador[0]= tiempoEntreToques_f(&juegos->jugadores[0].golpesPorMinuto); //calculo el periodo de cada jugador
        tiempoJugador[1]= tiempoEntreToques_f(&juegos->jugadores[1].golpesPorMinuto);
        tiempoJugador[2]= tiempoEntreToques_f(&juegos->jugadores[2].golpesPorMinuto);

        tiempoTransformado[0] = fmodf(currentTime, tiempoJugador[0]); // hago el resto de la division para obtener siempre positivos
        tiempoTransformado[1] = fmodf(currentTime, tiempoJugador[1]);
        tiempoTransformado[2] = fmodf(currentTime, tiempoJugador[2]);

        pelotas.pelota0.y = alturaEnTiempoResto_f(&juegos->jugadores[2].velocidadInicial,tiempoTransformado[2],&juegos->jugadores[2].alturaGolpe);
        pelotas.pelota0.x = posicionJugador2[j];
        pelotas.pelota1.y = alturaEnTiempoResto_f(&juegos->jugadores[1].velocidadInicial,tiempoTransformado[1],&juegos->jugadores[1].alturaGolpe);
        pelotas.pelota1.x = posicionJugador1[j];
        pelotas.pelota2.y = alturaEnTiempoResto_f(&juegos->jugadores[0].velocidadInicial,tiempoTransformado[0],&juegos->jugadores[0].alturaGolpe);
        pelotas.pelota2.x = posicionJugador0[j];

        // cargo datos de jugadores si estan alineados
        estanPuntosAlineados_f(&pelotas ,juegos, &cantidadAlineaciones, &banderaAlineado,currentTime);
        juegos->cantidadAlineamientos = cantidadAlineaciones;

    }

}
