#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Base class Ride
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;

public:
    Ride(int id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    virtual double fare() const = 0; // Pure virtual function for polymorphism
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID << "\nPickup: " << pickupLocation << "\nDropoff: " << dropoffLocation << "\nDistance: " << distance << " miles\n";
    }
    virtual ~Ride() {}
};

// StandardRide subclass
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 1.5; // $1.5 per mile
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Ride Type: Standard\nFare: $" << fare() << "\n";
    }
};

// PremiumRide subclass
class PremiumRide : public Ride {
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 3.0; // $3.0 per mile
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Ride Type: Premium\nFare: $" << fare() << "\n";
    }
};

// Driver class
class Driver {
private:
    int driverID;
    string name;
    double rating;
    vector<shared_ptr<Ride>> assignedRides;

public:
    Driver(int id, string n, double r) : driverID(id), name(n), rating(r) {}
    
    void addRide(shared_ptr<Ride> ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "Driver ID: " << driverID << "\nName: " << name << "\nRating: " << rating << "\nRides: " << assignedRides.size() << "\n";
    }
};

// Rider class
class Rider {
private:
    int riderID;
    string name;
    vector<shared_ptr<Ride>> requestedRides;

public:
    Rider(int id, string n) : riderID(id), name(n) {}
    
    void requestRide(shared_ptr<Ride> ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        cout << "Rider: " << name << "\nRide History:\n";
        for (const auto& ride : requestedRides) {
            ride->rideDetails();
            cout << "------------------\n";
        }
    }
};

// Main function for testing
int main() {
    shared_ptr<Ride> ride1 = make_shared<StandardRide>(1, "Downtown", "Airport", 10);
    shared_ptr<Ride> ride2 = make_shared<PremiumRide>(2, "Mall", "Hotel", 5);
    
    Rider rider(1001, "Alice");
    rider.requestRide(ride1);
    rider.requestRide(ride2);
    
    Driver driver(2001, "Bob", 4.8);
    driver.addRide(ride1);
    driver.addRide(ride2);
    
    cout << "--- Rider Details ---\n";
    rider.viewRides();
    
    cout << "--- Driver Details ---\n";
    driver.getDriverInfo();
    
    return 0;
}
