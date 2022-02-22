# TP1

Developed with Unreal Engine 4
Lab 01 : REALE Lucas

###Launch project :
Download from Git, go in Folder and right click on TP1 (Unreal Engine Project File) and Select Generate Visual Studio Project Files.
Then you can start the game by clicking twice on TP1, Rebuild if asked, all project code will be available in TP1.sln

### Project:
Base Map contains multiple Ai each using different steering method.
You can create your own by :
	-Going in the content explorer Content -> Blueprint 
	-Drag and drop BPAIPawn2 in the world
	-Select it
	-In the detail panel while the Pawn is selected (not the Root Scene or MeshComp) :
		-Go under Movement Type and select the Steering Method you want,
		-Go under Target and :
			For Seek / Flee / Pursuit / Evade / Arrival : Select a Target by using either the dropdown menu or the Select Tool and cliking on an actor in the world, then Start the game;
			For Circuit / OneWay / TwoWays : Select the first Target (not optimal / bug) and in Path Array click on the little cross as many time as you wish and for each element added in the array selet an actor in the world using the same method as above, then Start the game;

### Code:
Every class is split in two files a .h and .cpp, .h are located under Source/TP1/Public and .cpp are under Source/TP1/Private.
The AIPawn Movement works as followed :
	Depending on the value of the Enum EMovementType the Steering Force Vector is calculated in the proper way using the BaseMovement::Movement() function of class objects derived from the BaseMovment class.
	Each Movement Class compute the Steering_Direction to match the movement we want then the Velocity,Acceleartion and Postion are computed in AIPawn.
	The Rotation is set using only the normalised Velocity vector (called NewForward) with FVector::Rotation(), So NewSide and NewUp are never used.
	Seek / Flee / Pursuit / Evade / Arrival each have their own Class derived from BaseMovement or one of its Subclass
	Circuit and OneWay also have their own Class but they are not used as the logic for swaping Target is done in the AIPawn class instead ( this can be considered a bug or a probleme in polymorphism )
	Circuit / OneWay / TwoWays All use a TArray and swap the Target when getting close to their current Target

### Bugs:
Circuit / OneWay / TwoWays Targets swap is not done in their own Class
Putting the same Actor twice in the Array will cause unwanted behaviour such as looping ingnoring element located farther in the Array
Arrival does not instantly stop when reaching the Target, instead slows down a lot and keep moving/turning really slow for a moment
Other Array issues.

### Movement class hierarchy

MovementBase  
    FleeMovment  
        EvasionMovement  
        ArrivalMovement  
            CircuitMovement  
            OneWayMovement  
            TwoWaysMovement  
        SeekMovement  
            PursuitMovement  
	
