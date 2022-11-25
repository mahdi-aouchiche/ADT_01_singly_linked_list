#ifndef __PLAYLIST_UNIT_TEST_HPP__
#define __PLAYLIST_UNIT_TEST_HPP__

#include "gtest/gtest.h"
#include "../src/playlist.cpp"

string playlistTitle = "Test Playlist";

TEST(Playlist, Default_Constructor_Test) {
    PlaylistNode* empty_record = new PlaylistNode();
    
    EXPECT_EQ(empty_record->GetID(), "none");
    EXPECT_EQ(empty_record->GetSongName(), "none");
    EXPECT_EQ(empty_record->GetArtistName(), "none");
    EXPECT_EQ(empty_record->GetSongLength(), 0);
    EXPECT_EQ(empty_record->GetNext(), nullptr);
}

TEST(Playlist, Parameterized_Constructor_Test) {

    PlaylistNode* song_record = new PlaylistNode("0001", "my song", "artist name", 300);
    
    EXPECT_EQ(song_record->GetID(), "0001");
    EXPECT_EQ(song_record->GetSongName(), "my song");
    EXPECT_EQ(song_record->GetArtistName(), "artist name");
    EXPECT_EQ(song_record->GetSongLength(), 300);
    EXPECT_EQ(song_record->GetNext(), nullptr);
}

TEST(Playlist, GetNext_Test) {
    PlaylistNode* song_1 = new PlaylistNode("0001", "song 1", "artist 1", 100);
    PlaylistNode* song_2 = new PlaylistNode("0002", "song 2", "artist 2", 200, song_1);

    EXPECT_EQ(song_2->GetNext(), song_1);
}

TEST(Playlist, SetNext_Test) {
    PlaylistNode* song_1 = new PlaylistNode("0001", "song 1", "artist 1", 100);
    PlaylistNode* song_2 = new PlaylistNode("0002", "song 2", "artist 2", 200);
    song_1->SetNext(song_2);

    EXPECT_EQ(song_1->GetNext(), song_2);
}

TEST(Playlist, InsertAfter_Test) {
    PlaylistNode* song_1 = new PlaylistNode("0001", "song 1", "artist 1", 100);
    PlaylistNode* song_2 = new PlaylistNode("0002", "song 2", "artist 2", 200);
    PlaylistNode* song_3 = new PlaylistNode("0003", "song 3", "artist 3", 300);
    song_1->SetNext(song_2);
    song_1->InsertAfter(song_3);
     
    EXPECT_EQ(song_1->GetNext(), song_3);
    EXPECT_EQ(song_3->GetNext(), song_2);
}

#endif // __PLAYLIST_UNIT_TEST_HPP__