#pragma once


class MCOL // My Colors definition from RGB
{
public:
	inline static const sf::Color placeHolder  = sf::Color(1, 1, 1);


	inline static const sf::Color grey		   = sf::Color(105, 105, 105);
	inline static const sf::Color slatGrey	   = sf::Color(119, 136, 153);

	inline static const sf::Color brown		   = sf::Color(160, 82, 45);

	inline static const sf::Color yellowLight  = sf::Color(255, 255, 153);

	inline static const sf::Color limeGreen = sf::Color(50, 205, 50);
	inline static const sf::Color lawnGreen = sf::Color(124, 252, 0);
	inline static const sf::Color paleGreen = sf::Color(152, 251, 152);

	inline static const sf::Color indianaRed = sf::Color(205, 92, 92);
	inline static const sf::Color lightSalmon = sf::Color(255, 160, 122);
	inline static const sf::Color crimson = sf::Color(220, 20, 60);

	inline static const sf::Color hotPink = sf::Color(255, 105, 180);

	// HP COLORS
	inline static sf::Color hpProc100 = limeGreen;
	inline static sf::Color hpProc80  = lawnGreen;
	inline static sf::Color hpProc60  = paleGreen;
	inline static sf::Color hpProc40  = sf::Color::Yellow;
	inline static sf::Color hpProc20  = indianaRed;
	inline static sf::Color hpProc0   = crimson;


};
