#ifndef __PLAYLIST_HPP__
#define __PLAYLIST_HPP__

#include <string>
#include <iostream>
using namespace std;

void manage_playlist(const string playlistTitle);
void display_menu(const string playlistTitle);

class PlaylistNode 
{
  public:
    PlaylistNode();                           
    PlaylistNode(
      string uniqueID,
      string songName,
      string artistName,
      int songLength,
      PlaylistNode* nextLoc = 0
    );
    void InsertAfter(PlaylistNode* currLoc);      
    void SetNext(PlaylistNode* nodePtr);        // Mutator
    string GetID() const;                       // Accessor
    string GetSongName();                       // Accessor
    string GetArtistName() const;               // Accessor
    int GetSongLength() const;                  // Accessor
    PlaylistNode* GetNext();                    // Accessor
    void PrintPlaylistNode();                   // Print Node 
    
  private:
    string uniqueID;            // Initialized to "none" in default constructor
    string songName;            // Initialized to "none" in default constructor
    string artistName;          // Initialized to "none" in default constructor
    int songLength;             // Initialized to 0 in default constructor
    PlaylistNode* nextNodePtr;  // Initialized to 0 in default constructor
};

#endif // __PLAYLIST_HPP__