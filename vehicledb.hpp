#pragma once
#include <exception>
#include <fstream>
#include "datamodels/vehicle.hpp"
#include "datastructures/maxheap.hpp"
#include "datastructures/date.hpp"

using namespace std;

class VehicleDB
{
    struct Collection
    {
        MaxHeap<int, Vehicle> car,bike;
    } veh;

public:
    VehicleDB()
    {
        // populating the collection for demo.

        MaxHeap<int, Vehicle> *heaps[] = {&veh.car, &veh.bike};
        string fnames[] = {"VehicleDB_car.txt", "VehicleDB_bike.txt"};
        for (int i = 0; i < 2; i++)
        {
            ifstream file("data/" + fnames[i], ios::in);
            if (!file)
                continue;
            MaxHeap<int, Vehicle> *heap = heaps[i];
            string record;
            while (std::getline(file, record))
            {
                Vehicle *vehicle = new Vehicle(record);
                heap->insert(getInterval(vehicle->lastImportDate), *vehicle);
            }
            file.close();
        }
    }

    ~VehicleDB()
    {
        // saving the collection
        MaxHeap<int, Vehicle> *heaps[] = {&veh.car, &veh.bike};
        string fnames[] = {"VehicleDB_car.txt", "VehicleDB_bike.txt"};
        for (int i = 0; i < 2; i++)
        {
            ofstream file("data/" + fnames[i], ios::out);
            if (!file)
            {
                cout << "Error writing to file." << endl;
                continue;
            }
            MaxHeap<int, Vehicle> *heap = heaps[i];
            while (!heap->isEmpty())
            {
                Vehicle *vehicle = heap->getMax();
                heap->deleteMax();
                string ser = vehicle->Serialize() + "\n";
                file << ser;
            }
        }
    }

    class VehicleNotFoundException : public exception
    {
        const char *what()
        {
            return "Error: Vehicle for the requested type not found.";
        };
    };

    Vehicle *getVehicle(std::string vtype)
    {
        Collection *col;
        col = &veh;
        MaxHeap<int, Vehicle> *heap;
        if (vtype == "car")
            heap = &col->car;
        if (vtype == "bike")
            heap = &col->bike;

        if (heap->isEmpty())
            throw VehicleNotFoundException();
        Vehicle *temp = heap->getMax();
        heap->deleteMax();
        return temp;
    }

    void addVehicle(Vehicle d)
    {
        Collection *col;
        col = &veh;
        MaxHeap<int, Vehicle> *heap;
        if (d.vtype == "car")
            heap = &col->car;
        if (d.vtype == "bike")
            heap = &col->bike;
            
        heap->insert(getInterval(d.lastImportDate), d);
    }
};