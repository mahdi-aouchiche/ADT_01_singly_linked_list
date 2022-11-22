#include "../header/playlist.hpp"

PlaylistNode::PlaylistNode() 
{
  uniqueID    = "none" ;       // Initialized to "none" in default constructor
  songName    = "none" ;       // Initialized to "none" in default constructor
  artistName  = "none" ;       // Initialized to "none" in default constructor
  songLength  = 0  ;           // Initialized to 0 in default constructor
  nextNodePtr = 0  ;           // Initialized to 0 in default constructor
}

PlaylistNode::PlaylistNode( string uniqueID, string songName, string artistName, int songLength, PlaylistNode* nextLoc) 
{
  this->uniqueID    = uniqueID;
  this->songName    = songName; 
  this->artistName  = artistName;
  this->songLength  = songLength;
  this->nextNodePtr = nextLoc; 
}

void PlaylistNode::InsertAfter(PlaylistNode* currLoc) {
  PlaylistNode* temp = nextNodePtr;      // keep track of the rest of the list
  this->nextNodePtr = currLoc;           // point the inserted node
  currLoc->nextNodePtr = temp;           // point the inserted node to the rest of the list   
}

void PlaylistNode::SetNext(PlaylistNode* nodePtr){
  this->nextNodePtr = nodePtr;          // make the given node as next in the list
}

string PlaylistNode::GetID() const {
  return this->uniqueID;
}

string PlaylistNode::GetSongName() {
  return this->songName;
}

string PlaylistNode::GetArtistName() const {
  return this->artistName;
}

int PlaylistNode::GetSongLength() const {
  return this->songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
  return this->nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() {
  cout << "Unique ID: " << GetID() << endl;                           
  cout << "Song Name: " << GetSongName() << endl;                     
  cout << "Artist Name: " << GetArtistName() << endl;                 
  cout << "Song Length (in seconds): " << GetSongLength() << endl;    
}

void manage_playlist(const string playlistTitle) {
  char menuOp = ' ';
  string uniqueID;
  string songName;
  string artistName;
  int songLength = 0;
  int numNodes = 0;
  int songPosition = 0;
  int newPosition = 0;
  int totalTime;
  PlaylistNode* newSong = 0;
  PlaylistNode* currNode = 0;
  PlaylistNode* songNode = 0;
  PlaylistNode* prevNode = 0;
  PlaylistNode* insertPosNode = 0;
  PlaylistNode* headNode = 0;
  PlaylistNode* tailNode = 0;
  PlaylistNode* currPrintNode = 0;
  
  // Output menu option, prompt users for valid selection
  while (menuOp != 'q') {
    menuOp = ' ';
    display_menu(playlistTitle);

    // prompt users for valid selection  
    while (menuOp != 'a' && menuOp != 'd' && menuOp != 'c' && menuOp != 's' && menuOp != 't' && menuOp != 'o' && menuOp != 'q') {
      cout << "Choose an option: ";
      cin >> menuOp;
    }
    
    // Call corresponding menu action
    switch (menuOp) {
      
      case 'a':       // Add Song
      {    
        // Prompt user for song information
        cout << "ADD SONG:" << endl;

        cout << "Enter song's unique ID: ";
        cin >> uniqueID;
         
        cout << "Enter song's name: ";

        cin.ignore();
        getline(cin, songName);
         
        cout << "Enter artist's name: ";
        getline(cin, artistName);
        
        cout << "Enter song's length (in seconds): ";
        cin >> songLength;

        cout << endl;

        // Create a new Node for the Song and add it to Playlist
        newSong = new PlaylistNode(uniqueID, songName, artistName, songLength, 0);

        // If song is first in playlist, update head/tail
        // Otherwise insert to end of playlist and update tail
        if (headNode == 0) {
          headNode = newSong;
          tailNode = newSong;
        } else {
          tailNode->InsertAfter(newSong);
          tailNode = tailNode->GetNext();
        }

        ++numNodes;   // update the amount of songs in the Playlist
        
        break;
      }

      case 'd':       // Remove Song  
      {  
        if(headNode == 0) {
          cout << playlistTitle << " playlist is empty." << endl;    // if Playlist is empty
        } 
        else {
          cout << "REMOVE SONG" << endl;
          cout << "Enter song's unique ID: ";
          cin >> uniqueID;
          cin.ignore(); 

          currNode = headNode;            // pass in the headNode
          prevNode = headNode;
          songNode = headNode;

          bool flag = false;              // used to check if uniqueID is valid

          for (unsigned i = 1 ; i <= numNodes; ++i) {

            if(uniqueID == currNode->GetID()) {
              songNode = currNode;
              flag = true; 
              break;
            } 
            else {
              prevNode = currNode;
            }
            currNode = currNode->GetNext();    // go to the next node 
          }

          if(flag) {
            songName = songNode->GetSongName();        // Get the song title

            // deal with 1 Node playlist 
            if( (songNode == headNode) && (songNode == tailNode) ) {
              delete headNode;    // avoid memory leak
              headNode = 0;       
              tailNode = 0;
            }
            // deal with the last Node of the playlist
            else if( (songNode != headNode) && (songNode == tailNode) ) {
              tailNode = prevNode; 
              prevNode->SetNext(0);
              delete songNode;  
            }
            // deal with the middle of the list
            else {
              // if we are deleting the first node of the list change headNode otherwise  prevNode
              if(songNode == prevNode) {
                headNode = songNode->GetNext();
              } else {
                prevNode->SetNext( songNode->GetNext() );      
              } 
              delete songNode;                    // avoid memory leaks
            }

            cout << "\"" << songName << "\" removed." << endl << endl;
            --numNodes;   // update the amount of songs in the Playlist 
          } 
          else {
            cout << "Invalid unique ID, no song is removed" << endl; 
          }

          // avoid dangling pointers
          currNode = 0;                                
          prevNode = 0;
          songNode = 0;
        }
        break;
      }

      case 'c':       // Change position of song
      {
        //deal with empty playlist
        if( numNodes == 0 ) {
          cout << playlistTitle << " playlist is empty" << endl << endl;
          break;
        }

        cout << "CHANGE POSITION OF SONG" << endl;

        cout << "Enter song's current position: ";
        cin >> songPosition;

        //deal with non existing songPosition
        if( ((songPosition < 1) || (songPosition > numNodes)) ) {
          cout << playlistTitle << " playlist does not have a song in position " << songPosition << endl << endl;
          break;
        }

        cout << "Enter new position for song: ";
        cin >> newPosition; 

        // deal with newPosition extreme cases
        if(newPosition <= 1) {
          newPosition = 1;
        } 
        if(newPosition >= numNodes) {
          newPosition = numNodes; 
        }

        // pass in the headNode
        songNode      = headNode;   // Node to move position     
        prevNode      = headNode;   // previous Node of the Node to move

        insertPosNode = headNode;   // insert after this Node
        currNode = headNode;        // previous Node of newPosition's Node  

        // find the Node to move 
        for (unsigned i = 1 ; i < songPosition; ++i) {
          prevNode = songNode;                          // song's previous Node
          songNode = songNode->GetNext();               // song's Node
        }

        // find the node of the newPosition
        for (unsigned i = 1 ; i < newPosition; ++i) {
          currNode = insertPosNode;                     // previous Node from newPosition
          insertPosNode = insertPosNode->GetNext();     // newPosition Node 
        }

        songName = songNode->GetSongName();             // get the songName
        
        // Change a headNode 
        if( (songPosition == 1) && (newPosition != 1) ) {

          headNode = headNode->GetNext();           // move the headNode to the next node 
          insertPosNode->InsertAfter(songNode);

          // if the Head is moved to the tail, update tailNode
          if(newPosition == numNodes) {
            tailNode = songNode;
            tailNode->SetNext(0);    
          }
        }

        // Change a tailNode
        else if( (songPosition == numNodes) && (newPosition != numNodes) ) {
  
          // if moving the tailNode to the headNode
          if(newPosition == 1) {
            songNode->SetNext(headNode) ;   // make the tailNode point to headNode
            headNode = songNode;            // make the tail as a the headNode
            tailNode = prevNode;            // move tailNode to the last node 
            tailNode->SetNext(0);           // set tail to point to 0 
          }

          // if moving the tailNode to any other Node 
          else {
            tailNode = prevNode;
            tailNode->SetNext(0);           // set tail to point to 0
            currNode->InsertAfter(songNode);
          }
        }

        // Change a Node to the headNode
        else if ( (newPosition == 1) && (songPosition != numNodes) ) {
          prevNode->SetNext(songNode->GetNext());    // point previous node to next
          songNode->SetNext(headNode);                // the noode points to the headNode
          headNode = songNode;                        // make the node as the head   
        }

        // Change a Node to the tailNode
        else if ( (newPosition == numNodes) && (songPosition != numNodes) ) {
          prevNode->SetNext(songNode->GetNext());    // point previous node to next 
          insertPosNode->InsertAfter(songNode);   // move songNode to the end
          tailNode = songNode;                    // point tailNode to the last Node 
          tailNode->SetNext(0);                   // set the tail pointer to nullptr
        }

        // moving songNode upwards
        else if( (songPosition < newPosition) && (songPosition != 1) && (songPosition != numNodes) && (newPosition != 1) && (newPosition != numNodes)) {
          prevNode->SetNext(songNode->GetNext() );    // point previous node to next
          insertPosNode->InsertAfter(songNode);
        }

        // moving songNode downwards
        else if( (songPosition > newPosition) && (songPosition != 1) && (songPosition != numNodes) && (newPosition != 1) && (newPosition != numNodes) ) {
          prevNode->SetNext(songNode->GetNext() );    // point previous node to next
          currNode->InsertAfter(songNode); 
        }
 
        cout << "\"" << songName << "\" moved to position " << newPosition << endl << endl;

        break;
      }

      case 's':       // Output songs by specific artist
      {
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name: ";
        cin.ignore();
        getline(cin, artistName);
        
        currNode = headNode;  // pass in the headNode
        bool artist_flag = false;

        for(unsigned i = 1; i <= numNodes; ++i) {
          if(artistName == currNode->GetArtistName()) {
            cout << i << "." << endl;
            currNode->PrintPlaylistNode();
            cout << endl;
            artist_flag = true;
          }
          currNode = currNode->GetNext();    // move to the next node
        }

        if(!artist_flag) {
          cout << "There are no songs by this artist in the playlist." << endl << endl;
        }

        break;
      }

      case 't':       // Output total time of playlist (in seconds)
      {
        totalTime = 0;           // reset totalTime to 0
        songNode = headNode;     

        // go through the play list and add each song lenght to totaltime
        for(unsigned i = 1; i <= numNodes; ++i) {
          totalTime += songNode->GetSongLength();  // update total time in the playlist.
          songNode = songNode->GetNext();
        }
        
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS):" << endl;
        cout << "Total time: " << totalTime << " seconds." << endl << endl;
         
         break; 
      }

      case 'o':       // Output full playlist
      {
        cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl; 
        if (headNode == 0) {
          cout << "Playlist is empty" << endl;         // if Playlist is empty
        } else {
          currPrintNode = headNode;                    // pass the head Node to currPrintNode
          
          for (unsigned i = 1 ; i <= numNodes; ++i) {
            cout << i << "." << endl;
            currPrintNode->PrintPlaylistNode();         // print the Node information
            currPrintNode = currPrintNode->GetNext();   // go to the next Node
            if(i < numNodes) {
              cout << endl;                             // output a newline between Nodes
            }
          }
        }
        cout << endl;
        break;
      }

      case 'q':       // Quit
        break; 
    }
  }
}

void display_menu(const string playlistTitle){
  cout << playlistTitle << " PLAYLIST MENU" << endl;
  cout << "a - Add song." << endl;
  cout << "d - Remove song." << endl;
  cout << "c - Change position of song." << endl;
  cout << "s - Output songs by specific artist." << endl;
  cout << "t - Output total time of playlist (in seconds)." << endl;
  cout << "o - Output full playlist." << endl;
  cout << "q - Quit." << endl << endl;
}

