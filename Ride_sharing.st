Object subclass: #Ride
    instanceVariableNames: 'rideID pickupLocation dropoffLocation distance'.

Ride >> initializeWithID: id pickup: pickup dropoff: dropoff distance: dist
    rideID := id.
    pickupLocation := pickup.
    dropoffLocation := dropoff.
    distance := dist.

Ride >> rideDetails
    ^ 'Ride ID: ', rideID asString, ' | Pickup: ', pickupLocation, ' | Dropoff: ', dropoffLocation, ' | Distance: ', distance asString, ' miles'.

Ride >> fare
    self subclassResponsibility.


"Standard Ride subclass"
Ride subclass: #StandardRide
    instanceVariableNames: ''.

StandardRide >> fare
    ^ distance * 1.5. "$1.5 per mile"

StandardRide >> rideDetails
    ^ super rideDetails, ' | Ride Type: Standard | Fare: $', self fare asString.


"Premium Ride subclass"
Ride subclass: #PremiumRide
    instanceVariableNames: ''.

PremiumRide >> fare
    ^ distance * 3.0. "$3.0 per mile"

PremiumRide >> rideDetails
    ^ super rideDetails, ' | Ride Type: Premium | Fare: $', self fare asString.


"Driver Class"
Object subclass: #Driver
    instanceVariableNames: 'driverID name rating assignedRides'.

Driver >> initializeWithID: id name: n rating: r
    driverID := id.
    name := n.
    rating := r.
    assignedRides := OrderedCollection new.

Driver >> addRide: ride
    assignedRides add: ride.

Driver >> getDriverInfo
    ^ 'Driver ID: ', driverID asString, ' | Name: ', name, ' | Rating: ', rating asString, ' | Total Rides: ', assignedRides size asString.


"Rider Class"
Object subclass: #Rider
    instanceVariableNames: 'riderID name requestedRides'.

Rider >> initializeWithID: id name: n
    riderID := id.
    name := n.
    requestedRides := OrderedCollection new.

Rider >> requestRide: ride
    requestedRides add: ride.

Rider >> viewRides
    requestedRides do: [ :ride | Transcript show: ride rideDetails; cr ].


"Test Cases"
| ride1 ride2 rider driver |
ride1 := StandardRide new initializeWithID: 1 pickup: 'Downtown' dropoff: 'Airport' distance: 10.
ride2 := PremiumRide new initializeWithID: 2 pickup: 'Mall' dropoff: 'Hotel' distance: 5.

rider := Rider new initializeWithID: 1001 name: 'Alice'.
rider requestRide: ride1.
rider requestRide: ride2.

Transcript show: '--- Rider Details ---'; cr.
rider viewRides.


driver := Driver new initializeWithID: 2001 name: 'Bob' rating: 4.8.
driver addRide: ride1.
driver addRide: ride2.

Transcript show: '--- Driver Details ---'; cr.
Transcript show: driver getDriverInfo; cr.
