#include<iostream>
#include<TRandom3.h>
#include<TMath.h>
#include<TH1D.h>
#include<TCanvas.h>

using namespace std;

double exponential()
{
    gRandom->SetSeed(0);

    double E, y;

    int flag = 0;

    double fmax = 1.;
    double Emax = 10.;

    while(flag == 0)
    {
        E = gRandom->Uniform(0., Emax);
        y = gRandom->Uniform(0., 1.) * fmax;

        if(y < TMath::Exp(-E))
        {
            flag = 1;
        }
    }
    return E;
}

void physicsMCSimulations()
{
    TH1D *histogram = new TH1D( "Histogram", "Exponential Distribution; E; Events", 100, 0., 10. );    //Initialization of a histogram with 100 bins in range 0 to 10

    cout << "Give a natural number of random numbers to simulate: ";
    int n;
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        double value;
        value = exponential();
        histogram -> Fill( value );    //Filling the histogram with the random number from uniform distribution from range 0 to 1
    }

    TCanvas *canva = new TCanvas( "Canvas", "Exponential Simulation", 900, 600 );   //Initialization of a canva on which the histogram will be drawn
    histogram -> Draw();                                            //Plotting of the histogram
}
