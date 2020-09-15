#include 	<iostream>
#include 	<string>
#include 	<map>

static long						rome_to_arabic(std::string name){
	std::string 				decimal[5] = {"X", "XX", "XXX", "XL", "L"};
	std::string 				digit[9] = {"I", "II", "III", "IV", "V",
							 "VI", "VII", "VIII", "IX"};
	std::string 				sum;

	for (int i = 0; i < 9; i++){
		if (name == digit[i])
			return (i + 1);
	}
	for (int i = 0 ;i < 5; i++){
		if (i != 4){
			for (int j = 0; j < 9; j++) {
				sum = decimal[i] + digit[j];
				if (sum == name) {
					return ((i + 1) * 10 + j + 1);
				}
			}
		}
		else
			return (50);
	}
}

static long						name_to_arabic(std::string name){
	std::string 				alpha = "abcdefghijklmnopqrstuvwxyz";
	std::string 				res = "";
	for (int i = 0; i < name.size(); i ++)
		res +=  std::to_string(alpha.find(::tolower(name[i])) + 1);
	return (stoi(res));
}


int 							main(){
	int 						num_king;
	std::string 				king;
	std::string 				rome_num;
	std::map<int, std::string> m;

	std::cin >> num_king;
	for (int i = 0; i < num_king; i++)
	{
		std::cin >> king;
		std::cin >> rome_num;
		m[name_to_arabic(king) + rome_to_arabic(rome_num)] = king + " " +
				rome_num;
	}
	for (std::map<int, std::string> :: iterator it = m.begin(); it != m.end()
	; it++)
		std::cout << it->second << std::endl;
}
