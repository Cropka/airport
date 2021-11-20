# Describtion 


#### Class agent with ability to communicate and take some orders from the supervisory control
- plane : agent
    - passangerPlane : plane
    - postalPlane : plane
    - avionette : plane
- car : agent
    - bus : car
    - stairsVehicle : car
     


#### Class controller for the supervisory control
* array with resources and indicator if free/taken (the controller changes that value! It just mark it if it commands some resource to some event. And if event is over, agent tells sends to controller some signal and controller change its status
* problem is, how to calculate which runway is the best for our plane? Controller need to have some map of the airport built in..

#### Class resource
- freeway : resource
- gateway : resource
- securityTeam : resource
- //how to manage other staff members??
- baggage // how to call it?

#### Class airport with all the resources as fields (vector for each class of resources) 

Class event with unspecified vector <resource> (and deadline maybe? so analogue to a real time scheduler)
      it should also have boolean field ifCompleted
      heritaged classes will initialize vector<resource> with resources they need. Then it will be easy to make the whole program modular.
      each event class DON'T NEED TO have any identifier field, THE CONTROLLER NEEDS ONLY TO KNOW RESOURCES AND PRIORITY, IT DOES NOT NEED TO      KNOW WHAT EVENT IT IS!
      so priority indicator field is also needed
      There need to be three vectors: one with needed resource from first to latest for each subevent, second with each subevent priority
      third with time lenght of each subevent. And this three vectors should be signaled to the controller.

Class eventGenerator to generate events queque for the simulator - the best would be to download the data from some real airport and add
      some random delays, so probability density function would be like normal, but maybe not very high, flatter one more

#### WORKFLOW:
* eventGenerator generates some events and put them in the event queque, with specified time of occuring.
* controller takes events from the queque, manage resources to them, signaling the resource .
* each event should have subevent correlated with each needed resource (ex. it needs bus to carry on passagers, we know it will last 30 minuts (with some probability also) and that bus would be unavailable during it. After that phase event signals the controller that resource is free again. 
* after each subevent is completed, event calls the controller and says its completed (does it need to though?)
* event is taken of the queque
* many of that events (or even at subevent level) would be scheduled concurrently. So the plane could land, passangers go to the airport main hall, then bus could go to reload some other plane and does not need to wait more. So concurrency should be at the subevent level! This would give us much more flexability.
* and that's the end of loop I guess, goes around now.
