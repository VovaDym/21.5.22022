#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

enum buildings
{
	GARAGE = 1,	
	BARN,			
	BATHHOUSE,
	COUNT_BUILDINGS = 3
};

enum rooms
{
	BEDROOM = 1,	
	KITCHEN,		
	CHILDRENS_ROOM,	
	LIVING_ROOM,	
	BATHROOM,		
	COUNT_ROOMS = 5
};

struct Room
{
	rooms purpose;
	int square = 0;
};

struct Floor
{
	int ceilingHeight = 0;
	std::vector <Room> roomsV;
};


struct Piece {

	std::string ID;

	struct House
	{
		bool furnace = false;
		std::vector <Floor> floorsV;
	} house;

	struct Garage
	{
		bool select = false;
		int square = 0;
	} garage;

	struct Barn
	{
		bool select = false;
		int square = 0;
	} barn;

	struct Bathhouse
	{
		bool select = false;
		int square = 0;
		bool furnace = false;
	} bathhouse;
};

int fillingSquare(const std::string& buildings)
{
	int tmp;
	std::cout << "What is the area " << buildings << "?: ";
	std::cin >> tmp;
	return tmp;
}

void wait()
{
	std::cout << std::endl << "Enter 0 to continue: ";
	std::string answer;
	do
		std::cin >> answer;
	while (answer != "0");
}



Floor fillingFloor()
{
	Floor floorCompleted;
	int roomCount;
	int roomType;
	Room currentRoom;
	std::cout << "What is the ceiling height?: ";
	std::cin >> floorCompleted.ceilingHeight;

	std::cout << "How many rooms are there on the floor?: ";
	std::cin >> roomCount;
	for (int i = 1; i <= roomCount; ++i)
	{
		system("cls");
		std::cout << "What is the purpose of room type " << i << "?" << std::endl;
		std::cout << BEDROOM << ". Bedroom;" << std::endl;
		std::cout << KITCHEN << ". Kitchen;" << std::endl;
		std::cout << CHILDRENS_ROOM << ". Childrens room;" << std::endl;
		std::cout << LIVING_ROOM << ". Living room;" << std::endl;
		std::cout << BATHROOM << ". Bathroom;" << std::endl;
		do
		{
           std::cin >> roomType;
		}	
		while (roomType < 1 || roomType > COUNT_ROOMS);

		std::cout << "What is the area of the room?: ";
		std::cin >> currentRoom.square;

		switch (roomType)
		{
		case BEDROOM:
			currentRoom.purpose = BEDROOM; break;
		case KITCHEN:
			currentRoom.purpose = KITCHEN;	break;
		case CHILDRENS_ROOM:
			currentRoom.purpose = CHILDRENS_ROOM; break;
		case LIVING_ROOM:
			currentRoom.purpose = LIVING_ROOM; break;
		case BATHROOM:
			currentRoom.purpose = BATHROOM; break;
		}
		floorCompleted.roomsV.push_back(currentRoom);
	}
	return floorCompleted;
}

void fillingHouse(Piece& piece)
{
	char answer = false;
	int floorCount;
	system("cls");
	std::cout << "Is there a furnace in the building? (y/n): ";
	std::cin >> answer;
	if (answer == 'y')
		piece.house.furnace = true;

	std::system("cls");

	std::cout << "How many floors on your house? " << std::endl;
	std::cout << "Enter from 1 to 3: ";
	std::cin >> floorCount;

	for (int i = 1; i <= floorCount; ++i)
	{
		std::system("cls");
		std::cout << "Filling " << i << " floor of " << floorCount << std::endl;
		piece.house.floorsV.push_back(fillingFloor());
	}
}


void fillingGarage(Piece& piece)
{
	piece.garage.select = true;
	piece.garage.square = fillingSquare("garage");

	system("cls");

	if (piece.garage.square == 0)
	{
		piece.garage.select = false;
		std::cout << "Plot without garage" << std::endl;
	}
	else
		std::cout << "There is a garage on the plot" << std::endl;

	wait();
}

void fillingBarn(Piece& piece)
{
	piece.barn.select = true;
	piece.barn.square = fillingSquare("barn");

	system("cls");

	if (piece.barn.square == 0)
	{
		piece.barn.select = false;
		std::cout << "Plot without barn" << std::endl;
	}
	else
		std::cout << "There is a barn on the plot" << std::endl;

	wait();
}

void fillingBathhouse(Piece& piece)
{
	char answer;
	piece.bathhouse.select = true;
	piece.bathhouse.square = fillingSquare("bathhouse");

	system("cls");

	if (piece.bathhouse.square == 0)
	{
		piece.bathhouse.select = false;
		std::cout << "Plot without bathhouse" << std::endl;
	}
	else
	{
		std::cout << "There is a bathhouse on the plot" << std::endl;
		std::cout << "Does you bathhouse has chimney? (y/n): ";
		std::cin >> answer;
		if (answer == 'y')
			piece.bathhouse.furnace = true;
	}

	wait();
}

Piece fillingPiece()
{
	Piece pieceCompleted;
	std::cout << "Enter unique number of your piece of land: ";
	std::cin >> pieceCompleted.ID;

	fillingHouse(pieceCompleted);

	bool next = false;
	char answer;
	int roomType;
	do
	{
		system("cls");
		std::cout << "Besides the house, are there any other buildings on your site? (y/n): ";
		std::cin >> answer;

		if (answer == 'y')
		{

			do
			{
				system("cls");
				std::cout << "Choose one of this:" << std::endl;
				std::cout << GARAGE << ". Garage;" << std::endl;
				std::cout << BARN << ". Barn;" << std::endl;
				std::cout << BATHHOUSE << ". Bathhouse." << std::endl;
				std::cout << "0. Exit from this piece of land" << std::endl;
				std::cin >> roomType;
			} while (roomType < 0 || roomType > COUNT_BUILDINGS);

			switch (roomType)
			{
			case GARAGE:
				fillingGarage(pieceCompleted); break;
			case BARN:
				fillingBarn(pieceCompleted); break;
			case BATHHOUSE:
				fillingBathhouse(pieceCompleted); break;
			case 0: next = true; break;
			}
		}
		else next = true;
	} while (!next);

	return pieceCompleted;
}

void showing(std::vector <Piece>& piecesCompleted);



int totalPieces;

int main()
{
	
	std::cout << "Enter total piece of land: ";
	std::cin >> totalPieces;
	std::vector <Piece> piecesCompleted;

	for (int i = 1; i <= totalPieces; ++i)
	{
		system("cls");
		std::cout << "Filling " << i << " piece of land " << std::endl << std::endl;
		piecesCompleted.push_back(fillingPiece());
	}

	showing(piecesCompleted);
}

void showing(std::vector <Piece>& piecesCompleted)
{
	int totalSquare = 0;
	int totalBuildings = totalPieces;
	int totalRooms = 0;
	int totalBedrooms = 0;
	int totalKitchens = 0;
	int totalChildrenRooms = 0;
	int totalLivingRooms = 0;
	int totalBathrooms = 0;


	for (int i = 0; i < totalPieces; ++i)
	{
		if (piecesCompleted[i].barn.select)
		{
			totalSquare += piecesCompleted[i].barn.square;
			++totalBuildings;
		}
		if (piecesCompleted[i].bathhouse.select)
		{
			totalSquare += piecesCompleted[i].bathhouse.square;
			++totalBuildings;
		}
		if (piecesCompleted[i].garage.select)
		{
			totalSquare += piecesCompleted[i].garage.square;
			++totalBuildings;
		}

		for (int j = 0; j < piecesCompleted[i].house.floorsV.size(); ++j)
		{
			totalRooms += piecesCompleted[i].house.floorsV[j].roomsV.size();
			for (int k = 0; k < piecesCompleted[i].house.floorsV[j].roomsV.size(); ++k)
				switch (piecesCompleted[i].house.floorsV[j].roomsV[k].purpose)
				{
				case BEDROOM:
					++totalBedrooms; break;
				case KITCHEN:
					++totalKitchens; break;
				case CHILDRENS_ROOM:
					++totalChildrenRooms; break;
				case LIVING_ROOM:
					++totalLivingRooms; break;
				case BATHROOM:
					++totalBathrooms; break;
				}
		}

	}

	system("cls");
	std::cout << "Total count of buildings is  " << totalBuildings << std::endl;
	std::cout << "Total square of buildings is " << totalSquare << std::endl;
	std::cout << "Total count of rooms is " << totalRooms << std::endl;
	std::cout.width(20);
	std::cout << "bedrooms: " << totalBedrooms << std::endl;
	std::cout.width(20);
	std::cout << "kitchens: " << totalKitchens << std::endl;
	std::cout.width(20);
	std::cout << "children rooms: " << totalChildrenRooms << std::endl;
	std::cout.width(20);
	std::cout << "living rooms: " << totalLivingRooms << std::endl;
	std::cout.width(20);
	std::cout << "bathrooms: " << totalBathrooms << std::endl;
}