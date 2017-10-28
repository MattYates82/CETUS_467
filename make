Test:  main.cpp CETUS_data.cpp CETUS_Items.cpp CETUS_List.cpp CETUS_Player.cpp CETUS_Room.cpp 
	g++ -o test main.cpp CETUS_data.cpp CETUS_Items.cpp CETUS_List.cpp CETUS_Player.cpp CETUS_Room.cpp -std=c++11


clean:
	rm test
