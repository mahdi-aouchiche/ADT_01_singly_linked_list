#include <iostream>
#include <iomanip>
#include "../header/playlist.hpp"
using namespace std;

int main() {
  string playlistTitle;
  
  // Prompt user for playlist title
  cout << "Enter playlist's title:" << endl;
  getline(cin, playlistTitle);
  cout << endl;
  
  // Output play list menu options
  manage_playlist(playlistTitle);
  return 0;
}