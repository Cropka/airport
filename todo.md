## BACKEND:

#### V1
* add several classes inheriting after agent and resource, respectively. Check out how the gateway class is written, just change type field value and you are (probably) ready to go.
	- added Passanger & Postal planes, Bus, RampStairs agents
	- added Gateway and Runway resources
* add signal-slot to change busy field in a resource by a controller
	- Controller now owns an airport reference to manipulate resources and query informations
* add signal-slot to ask about busy status in a resource by a controller
	- Done
* add signals-slots to add agents and resources to airport (from simulator and controller) and to change their positions (from the controller)
  (resource/agent don't need to know its position, it's suitable if airport knows that. And they can both know id of the agent/resource then.)
	- Done object creation by Simulator - let's see if we really need to create objects within the controller
	- Position manipulation for now is done by direct access to an airport instance.
* code the simulator and whole airport initialisation sequence. It can be hardcoded at the beginning (would be nice if it could be read from a textfile).
	- Simple (VERY simple) GUI menu has been made to create basic agents and resources. Textfile parser is still needed for more complex stuff.
* simulator need to construct events and send them somehow to the controller
	- For now simulator sends QT signals to the controller which then initializes appropriate event based upon slot called
* code the controller:
what it really does: get vector of events from the simulator, schedule them and perform (manage of locking/unlocking of resources, changes positions and adds new objects in the airport).
Fields: it need to have some vector of events to perform, events which are currently performed, vector of resources (maybe some information on how long each resource will be blocked? Maybe class resource should have it as field?)
	- Events are for now stored in priority queue with custom comparator (based upon timeOfOccurance). Priority queue may not be the best way to store them, but that is to be determined by the scheduling algorithm.
* scheduling algorithm to be prepared.

#### V2
* make simulator read test configuration from file
	- Done - added class ConfigParser. Description of the config file is in the header.
	- For now, filename is hardcoded as the "filename" field of simulator class. It should be read from the GUI.
* make simulator handle determining events timeOfOccurance (randomly?)
* add more events for handling within simulator & controller
* add rest of agents and resources (if needed, perhaps for now we can work with this basis)
* Make scheduling algorithm / expand controller logic
* Figure out:
	- on what basis do we change position of objects;
	- On what basis do we block resources for event handling (block for a certain amount of time? Might require multithreadding. Perhaps block until further event comes which will free the resource would be the best?)

## GUI:
* Each object, with information about its type and position (x,y) will be in the class airport.
