#include <string>


#ifndef CETUS_ITEMS_HPP
#define CETUS_ITEMS_HPP

using std::string;

class Item {
	
	private:
	
		string	Name;
		string	Description;
		string 	roomDescription;
		int		Power;
		int		Healing;
		bool	weapon;
		bool	roomFeature;
		bool	collectible;
		
	public:
	
		Item();
		Item(string Name, string Description, string roomDesc, int Power, int Healing, bool weapon, bool feature, bool collect);
		~Item();
		int damageItem(int damage);
		string getName();
		string getDescription();
		string getRoomDescription();
		int getPower();
		int getHealing();
		bool getWeapon();
		bool getRoomFeature();
		bool getCollectible();
	
};
#endif