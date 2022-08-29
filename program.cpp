#include <string>
#include <iostream>
#include "vehicledb.hpp"

using namespace std;

int main()
{
    cout << "VEHICLE MANAGEMENT SYSTEM" << endl;

    VehicleDB vehicles;
    int choice = 0;

    while (choice != 3)
    {
        cout << "Enter your choice: \n\t1.Add New Vehicle \n\t2.Check/BUY Vehicle \n\t3.QUIT" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int price, count;
            string modelname, vtype;
            cout << "Enter your following details please (Modelname, Price, Type of Vehicle(car/bike):\n";
            cin >> modelname >> price >> vtype;
            Vehicle vehicle(modelname, price, vtype);
            vehicles.addVehicle(vehicle);
            cout << "Successfully Added!" << endl;
            break;
        }
        case 2:
        {
            std::string vtype;
            cout << "PLEASE ENTER THE TYPE OF VEHICLE (CAR/BIKE): ";
            cin >> vtype;
            cout << "CHECKING FOR AVAILABILITY..." << endl;

            // IF AVAILABLE
            Vehicle *vehicle = vehicles.getVehicle(vtype);
            cout << "\tModel Name: " << vehicle->modelname << endl;
            cout << "\tCar/Bike: " << vehicle->vtype<< endl;
            cout << "\tLast import date: " << vehicle->lastImportDate << endl;
            cout << "\tPrice: " << vehicle->price << endl;
            vehicle->lastImportDate = Date();
            vehicles.addVehicle(*vehicle);
            break;
        }
        case 3: 
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "PLEASE ENTER A VALID CHOICE...";
        }
    }
    return 0;
}