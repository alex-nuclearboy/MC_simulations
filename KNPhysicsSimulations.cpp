#include <iostream>
#include <TRandom3.h>
#include <TMath.h>
#include <TH1D.h>
#include <TCanvas.h>

using namespace std;

// Klein-Nishina differential cross-section
double kleinNishina(double theta, double E)
{
    double alpha = E / 0.511; // E in MeV, rest energy of the electron is 0.511 MeV
    double cosTheta = TMath::Cos(theta);
    double term1 = 1.0 / (1.0 + alpha * (1.0 - cosTheta)); // Scattered photon's energy fraction
    double term2 = TMath::Power(term1, 2);                 // Squared energy term
    double term3 = term1 + 1.0 / term1 - 1.0 + TMath::Power(cosTheta, 2); // Angular dependency
    return term2 * term3;
}

// Function to simulate Klein-Nishina distributed energies
double simulateKleinNishina(double E)
{
    gRandom->SetSeed(0);
    double theta, y, fmax, value;

    fmax = kleinNishina(0, E); // Maximum value of the Klein-Nishina formula
    bool flag = false;

    while (!flag)
    {
        theta = gRandom->Uniform(0, TMath::Pi()); // Random angle in [0, π]
        y = gRandom->Uniform(0, fmax);            // Random vertical axis value

        if (y < kleinNishina(theta, E))
        {
            flag = true;
            value = theta;
        }
    }
    return value;
}

void KNPhysicsSimulations()
{
    cout << "Enter the initial photon energy in MeV: ";
    double E;
    cin >> E;

    cout << "Enter the number of random events to simulate: ";
    int n;
    cin >> n;

    TH1D *histogram = new TH1D("Histogram", "Klein-Nishina Distribution; Scattering Angle (rad); Events", 100, 0, TMath::Pi());

    for (int i = 0; i < n; ++i)
    {
        double theta = simulateKleinNishina(E); // Simulate scattering angles
        histogram->Fill(theta);
    }

    TCanvas *canvas = new TCanvas("Canvas", "Klein-Nishina Simulation", 900, 600);
    histogram->Draw();
}
