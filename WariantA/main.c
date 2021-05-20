#include "data.h"


int iter = 1;
//tworzymy most jako zmienną globalną, ponieważ ma być
//dostępny dla każdego samochodu
pthread_mutex_t bridge;


int minSleepTime = 10000;
int maxSleepTime = 100000;
int carsInA=0;
int carsInB=0;
int carOnBridge=0;
int carsBeforeBridgeA=0;
int carsBeforeBridgeB=0;
char *direction;

//Funkcja do wyświetlania statusu w postaci:
//A-5 10>>> [>> 4 >>] <<<4 6-B

void PrintStatus()
{
    printf("A-%d %d>>> [%s %d %s] <<< %d %d-B\n",carsInA, carsBeforeBridgeA,
    direction, carOnBridge, direction,carsBeforeBridgeB, carsInB);
}

void *CarRoutine(void *args)
{
    int vehicleNo = iter;
    iter++;
	while(1)
	{
		//printf("Samochód %d załatwia swoje sprawy w mieście A\n",vehicleNo);
        carsInA++;
        PrintStatus();
		ClockSleep(minSleepTime,maxSleepTime);
        carsInA--;
        carsBeforeBridgeA++;
        PrintStatus();
		//printf("Samochód %d zatankował i wyjeżdza do miasta B\n",vehicleNo);
		
		//przejazd przez most, który zajmuje do 5 s czasu
		//most jest wtedy zablokowany i nie przejezdny
		pthread_mutex_lock(&bridge);
        carsBeforeBridgeA++;
        carOnBridge = vehicleNo;
        direction=">>";
        PrintStatus();
		//printf("Samochód %d przejeżdza przez most\n",vehicleNo);
		ClockSleep(minSleepTime,maxSleepTime);
        //printf("Samochód %d przejechał przez most\n",vehicleNo);
		pthread_mutex_unlock(&bridge);

        carsInB++;
        PrintStatus();
		//printf("Samochód %d załatwia swoje sprawy na mieście B\n",vehicleNo);
		ClockSleep(minSleepTime,maxSleepTime);
        carsInB--;
		//printf("Samochód %d zatankował i wyjeżdza do miasta A\n",vehicleNo);

		//przejazd przez most, który zajmuje do 5 s czasu
		//most jest wtedy zablokowany i nie przejezdny
        carsBeforeBridgeB++;
        PrintStatus();
		pthread_mutex_lock(&bridge);
        carOnBridge = vehicleNo;
        direction="<<";
        PrintStatus();
		//printf("Samochód %d przejeżdza przez most\n",vehicleNo);
		ClockSleep(minSleepTime,maxSleepTime);
        //printf("Samochód %d przejechał przez most\n",vehicleNo);
		pthread_mutex_unlock(&bridge);
	}
}



int main(int argc, char* argv[])
{
    if(ValidateData(argc,argv) == false)
    {
        printf("Błąd danych wejściowych, anulowanie\n");
        exit(EXIT_FAILURE);
    }

    int CarNumber = atoi(argv[1]);

    //Samochody
    pthread_t car[CarNumber];

    //zmienna iteracyjna, pomaga przy tworzeniu wątków
    int i;

    if(0 != pthread_mutex_init(&bridge,NULL))
    {
        printf("Bląd inicjalizacji mostu!\n");
        errno=-1;
        exit(EXIT_FAILURE);
    }

    for(i = 0; i<CarNumber; i++)
    {
        if(0 != pthread_create(&car[i], NULL, CarRoutine,&i))
        {
            printf("Blad inicjalizacji %d filozofa\n",i);
            errno=1;
            exit(EXIT_FAILURE);
        }
    }

	for(i=0;i<CarNumber;i++)
    {
        pthread_join(car[i], NULL);
    }
    return 0;
}
