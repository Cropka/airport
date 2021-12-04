BACKEND:
* add several classes inheriting after agent and resource, respectively. Check out how the gateway class is written, just change type field value and you are (probably) ready to go.
* add signal-slot to change busy field in a resource by a controller
* add signal-slot to ask about busy status in a resource by a controller
* add signals-slots to add agents and resources to airport (from simulator and controller) and to change their positions (from the controller)
  (resource/agent don't need to know its position, it's suitable if airport knows that. And they can both know id of the agent/resource then.)
* code the simulator and whole airport initialisation sequence. It can be hardcoded at the beginning (would be nice if it could be read from a textfile).
* simulator need to construct events and send them somehow to the controller
* code the controller:
what it really does: get vector of events from the simulator, schedule them and perform (manage of locking/unlocking of resources, changes positions and adds new objects in the airport).
Fields: it need to have some vector of events to perform, events which are currently performed, vector of resources (maybe some information on how long each resource will be blocked? Maybe class resource should have it as field?)
* scheduling algorithm to be prepared.

GUI:
* Each object, with information about its type and position (x,y) will be in the class airport.
