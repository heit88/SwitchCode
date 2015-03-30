/* General single node program
I am starting with a general outline, trying to avoid specifics
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>


RF24 radio(9,10);                          // CE,CSN Pins. Create Radio Object
RF24Network network(radio);                // Create Network
uint16_t channelNumber = 1;                // Assign initial channel number (Octal format)
uint16_t nodeAddress = 00;                 // Assign initial node address   (Octal format)


struct payloadStruct {
  byte state;
  byte commandSet;
  unsigned int power;
  byte temperature;
};


void setup(void) {
  // Start the radios and network
  SPI.begin();
  radio.begin();
  network.begin(channelNumber,nodeAddress);        
  // set if the node can give user feedback
  bool canIndicate = 1; // Later to be replaced by a function that somehow (address?) knows the node has user feedback.
}

void loop() 
{
  // Update the network
  network.update();
  
  // Define variables for the incomming data
  RF24NetworkHeader header;        // header of the incoming data
  payloadStruct payload;           // payload of the incoming data
  

  // While something is available on the network to read in
  while ( network.available() ) 
  {
    // Read in the data. I think the .read takes care of addressing
    network.read( header, &payload, /* if all we need is the state we can just read that*/ sizeof(payload) );
    
    // Parse out the data
    changeState(payload.state);
    executeCommand(payload.commandSet);
  }
  
  // If the node needs to communicate out
  if stateChange || command || updatePower || updateTemperature
  {
    
    
    // Create the payload structure to write
    payload = {getState(), getCommand(), getPower(), getTemperature()};
    // Write out the payload structure
    bool writeSuccessful = network.write( header, &payload, sizeof(payload));
    // If the node could not send the payload successfully, give userfeedback;
    if (~writeSuccessful)
      userFeedback(0,canIndicate);
  }
}

//**********************************************************************
// Get Commands
//**********************************************************************
byte getState()
{  
  return 0;
}


byte getCommand()
{
  return 0;
}


unsigned int getPower()
{
  return 0;
}

byte getTemperature()
{
  return 0;
}

//*********************************************************************
// Data Parse Commands
//*********************************************************************
void changeState(byte state)
{ 
  // Check the current state of the node
  // Compare it against the incoming requested state
  // If the state needs to change, change the state and send an update back to the master
  // If the state is already in that position, send a comfermation back that the node is already at that state.
}


void executeCommand(byte command)
{
  // This could be used for querying the the temperature or current power consumption, things like that.
  
  // I am not sure quite yet how this will work in general. 
  // But if a specific command, that is not a state change is sent for a node to execute we will parse it out and execute it here. 
  // We need to somehow keep this general, so we don't end up with 256 if conditions.
  
}


//********************************************************************
// User Feedback
//********************************************************************
void userFeedback(bool success, bool canIndicate)
{
  if (canIndicate)
  {
    if success
    {
       // Give the user some indication of success 
    }
    else
    {
      // Give the user some indication of failure
    }
  }
}









