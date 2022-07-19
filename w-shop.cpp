#include <iostream>
#include <iomanip> //this library is needed for setw
#include <algorithm> //needed to make uppercase string
#include <chrono> //time delay
#include <thread> //time unit
#include <string> 
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using namespace std;
string choice, name_of_customer, find_item;
string size_c, size_sh;
int input_category, error, input_item, id_number;
int item_cost, total_sum = 0;
int decision = 0, y, ind = -1;
string cart_list[100][4];


int int_debug(string txt) //debugging integer
{
	do
	{
		cout << txt;
		int input;
		error = 0;
		cin >> input;
		if (cin.fail())
		{
			cout << "\nunfortunately, there is not room for creativity here,\n" <<
				"please try one more time\n\n" << endl;
			error = 1;
			cin.clear(); // to clear the internal state of stream
			cin.ignore(10000, '\n'); // remove 10000 characters (just in case) until '\n' is met (ENTER)
		}
		else {
			return input;
		}

	} while (error == 1);
}



/*Hey!Lets talk*/


//CATEGORIES
string categorie_list[4]{
	"shoes",
	"up clothes",
	"down clothes",
	"accessories",
};

string lists[4][12][2]{
{
		//SHOES_LIST          index = 0

		{"sneakers",        "400000" },
		{"platforms",       "600000" },
		{"boots",           "560000" },
		{"sandal",          "200000" },
		{"ballet-flat",     "350000" },
		{"oxford-shoes",    "420000" },
		{"loafers",         "400000" },
		{"mary-janes",      "540000" },
		{"flip-flops",      "150000" },
		{"wedges",          "400000" },
		{"brouges",         "380000" },
		{"mocassin",        "340000" }

	},
	{
		//UP_LIST                index = 1

		{"hoodie",         "250000" },
		{"blouse",         "150000" },
		{"t-shirt",        "130000" },
		{"sweater",        "210000" },
		{"coat",           "730000" },
		{"dress",          "600000" },
		{"blazer",         "200000" },
		{"slip",           "300000" },
		{"crop-top",       "500000" },
		{"cardigan",       "450000" },
		{"jacket",         "230000" },
		{"shirt",          "120000" }
	},
	{
		//DOWN_LIST              index = 2

		{"jeans",                  "200000" }, //0
		{"lulu-leggins",           "150000" },
		{"shorts",                 "100000" },
		{"pants",                  "210000" },
		{"skirt",                  "120000" },
		{"bootcut-jeans",          "210000" }, //5
		{"denim-shorts",           "130000" },
		{"skinny-jeans",           "230000" }, //7
		{"ur-toys",                "250000" },
		{"stretch-jeans",          "230000" }, //9
		{"yoga-pants",             "150000" },
		{"flare-jeans",            "180000" } //11
	},
	{
		//ACCESSOIRES_LIST       index = 3

		{"backpack",           "200000" },
		{"belt",               "150000" },
		{"hat",                "100000" },
		{"wallet",             "210000" },
		{"scarve",             "120000" },
		{"sunglasses",         "210000" },
		{"gloves",             "130000" },
		{"ID-number",          "230000" },
		{"e-password",         "250000" },
		{"neackle",            "230000" },
		{"head-fan",           "150000" },
		{"keyring",            "180000" }
	}

};

void total_cost();

int main_menu();

void sizeofshoes();

void sizeofclothes();

void quantity();

void cart();

void goback(string where);


string make_space(string price);

int module_search() {
	system("CLS");
	cout << "Item to search or '0' to quit: ";
	cin >> find_item;
	if (find_item == "0") {
		system("CLS");
		main_menu();
	}
	else {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\n";
		decision = 0;
		for (int ctgr_indx = 0; ctgr_indx < 4; ctgr_indx++) {
			for (int itm_indx = 0; itm_indx < 12; itm_indx++) {
				if (find_item == lists[ctgr_indx][itm_indx][0]) {
					input_category = ctgr_indx + 1;
					input_item = itm_indx + 1;
					cout << "\n\'" << find_item << "\'" << " is available\n";
					cout << "\nPrice: " << make_space(lists[ctgr_indx][itm_indx][1]) << " sums" << endl;
					decision = int_debug("\n1) add to cart \n2) again \n3) back\n\nselect a respective number: ");
					cin.clear();
					cin.ignore(10000, '\n');

					if (decision == 1) {
						ind++;
						if (input_category == 1) {
							sizeofshoes();
						}
						else if (input_category == 2 or input_category == 3) {
							sizeofclothes();
						}
						quantity();
						total_cost();
						cart();
						cout << "\n'" << find_item << "'" << " is added to cart\n";
						sleep_for(milliseconds(2000));
						goback("search");
						return 0;
						break;
					}
					else if (decision == 2) {
						system("CLS");
						module_search();
						return 0;
						break;
					}
					else if (decision == 3) {
						system("CLS");
						main_menu();
						return 0;
						break;
					}
					else {
						cout << "\I guess you gotta go to main menu -.-\n\n";
						sleep_for(milliseconds(2500));
						system("CLS");
						main_menu();
						return 0;
					}
				}
				else {
					continue;
				}

			}
		}
		if (decision == 0) {
			int sub_select;
			cout << "\nno such item found\n"; //No such item found
			while (true) {
				cout << "\n1. try again \n2. back\n\n";
				sub_select = int_debug("Select: ");
				cin.clear();
				cin.ignore(10000, '\n');
				if (sub_select == 1) {
					system("CLS");
					module_search();
					return 0;
					break;
				}
				else if (sub_select == 2) {
					system("CLS");
					main_menu();
					return 0;
				}
				else {
					cout << "\nglad u checked! thought u already CALMED DOWN\n\n";
					continue;
				}
			}
		}
		else if (decision == 2) {
			module_search();
			return 0;
		}
	}
}



string make_space(string price) { //function adds space between numbers to make it clear
	for (int uwu = 3; uwu < price.length(); uwu += 4) {
		if (price.length() <= 3) {
			break;
		}
		else {
			price.insert(price.length() - uwu, " "); //str.insert(index, string)[adds string to given position in another string]
		}
	}
	return price;
}


//Prints list
void show_list(string list[4][12][2], int list_index) {
	for (int item_index = 0; item_index < 12; item_index++) {
		cout << item_index + 1 << ") " << list[list_index][item_index][0] << " - " << make_space(list[list_index][item_index][1]) << " sums" << endl;
	}
}
void show_array(string list[4]) {
	for (int categ_index = 0; categ_index < 4; categ_index++) {
		cout << categ_index + 1 << ") " << list[categ_index] << endl;
	}
}

int show_cart(string list[100][4]) {
	while (true) {
		for (int cart_index = 0; cart_index < 100; cart_index++) {
			if (list[cart_index][0] == "") {
				break;
			}
			else if (list[cart_index][0] == " ") {
				for (int moving_item = cart_index; moving_item < 99; moving_item++) {
					for (int moving_details = 0; moving_details < 4; moving_details++) {
						list[moving_item][moving_details] = list[moving_item + 1][moving_details];
					}
				}
			}
			cout << cart_index + 1 << ") " << list[cart_index][0] << " - " << make_space(list[cart_index][1]) << " sums\n" << "Quantity: " << list[cart_index][2] << endl;
			cout << "Size: " << list[cart_index][3] << "\n\n";
		}
		cout << "\nTotal cost: " << make_space(to_string(total_sum)) << " sums\n\n";
		int back_not;
		back_not = int_debug("1. remove \n0. back\n\nSelect: ");
		cin.clear();
		cin.ignore(10000, '\n');
		if (back_not == 1) {
			if (cart_list[0][0] == "") {
				cout << "\nNothing to remove\n\n"; //nothing to remove
				sleep_for(milliseconds(1500));
			}
			else {

				int remove_index;
				remove_index = int_debug("\nElement number: ");
				cin.clear();
				cin.ignore(10000, '\n');
				if (remove_index <= 0 or remove_index > 99 or list[remove_index - 1][0] == "") {
					cout << "\n\nInvalid index\n\n";
					continue;
				}
				total_sum -= (stoi(list[remove_index - 1][1]) * stoi(list[remove_index - 1][2]));
				for (int index_4 = 0; index_4 < 4; index_4++) {
					list[remove_index - 1][index_4] = " ";
				}
				cout << "\nElement is removed\n\n";
				sleep_for(milliseconds(1500));
			}
			system("CLS");
			show_cart(list);
			return 0;
		}
		else if (back_not == 0) {
			system("CLS");
			main_menu();
			return 0;
		}
		else {
			setlocale(LC_ALL, "Russian");
			cout << "\nГИГАНТ МЫСЛИ\n";
			cout << "отец узбекской демократии\n";
			cout << "\none more time pls\n\n";
			sleep_for(milliseconds(2500));
			continue;
		}
	}
	return 0;
}






//Texts "You selected 'item_name'"
void selected(int list_index, int item_index1) {
	system("CLS");
	cout << "\nYou selected " << "'" << lists[list_index][input_item - 1][0] << "'\n\n";
	ind++;   //for cart
}



void sizeofclothes()
{
	system("CLS");
	while (true) {

		cout << "What is your size?(xs, s, m, l, xl)  ";
		cin >> size_c;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\n";


		if (size_c == "xs" || size_c == "s" || size_c == "m" || size_c == "l" || size_c == "xl")
		{
			cout << "Fortunately, all sizes are available\n\n";
			break;
		}
		else if (size_c == "xxs" || size_c == "xxl" || size_c == "xxxl")
		{
			cout << "\ninput size is currently not available\n\n\n";
		}
		else
		{
			cout << "\nspelling mistake have been made by yourself\nconsider to fix it\n\n"; //wrong input
		}

	}
}

void sizeofshoes()
{
	system("CLS");
	while (true) {
		cout << "What is your size?(from 33 to 44) ";
		cin >> size_sh;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\n";

		if (size_sh >= "33" && size_sh <= "44")
		{
			cout << "Fortunately, all sizes are available\n\n";
			break;
		}
		else if (size_sh < "33" && size_sh>"20")
		{
			cout << "\nsaid apologizes, that he had no ability to add a line of code in order not to make this condition\n\n\n";
		}
		else if (size_sh < "50" && size_sh>"44")
		{
			cout << "\nasad apologizes, that said was not able to add a line of code\n\n\n";
		}
		else
		{
			cout << "\nchoice were that complicated, that u picked non-existent\n\n\n"; //Wrong input for size, please try again 
		}
	}
}




int customer_details()
{
	int birth_year = 0, birth_month = 0, birth_day = 0;
	int birthday[3]{ birth_year, birth_month, birth_day };


	cout << "Enter your name: ";
	getline(cin, name_of_customer);
	transform(name_of_customer.begin(), name_of_customer.end(), name_of_customer.begin(), toupper);

	if (name_of_customer == "KIRTI" || name_of_customer == "SAID" || name_of_customer == "ASADULLA" || name_of_customer == "ASAD" || name_of_customer == "ASD") {
		return 0;
	}




	cout << "\nWe need to know your birthday for optimization\n\n";
	while (true) { //year
		birth_year = int_debug("Year: \n\n");
		cin.clear();
		cin.ignore(10000, '\n');
		if (birth_year < 1900) {
			system("CLS");
			cout << "\nHUGE CAP\n\n";
			sleep_for(milliseconds(1000));
			continue;
		}
		else if (birth_year < 1960) {
			system("CLS");
			cout << "\nBig CAP\n\n";
			sleep_for(milliseconds(1000));
			continue;
		}
		else if (birth_year < 1970) {
			system("CLS");
			cout << "\ncap\n\n";
			sleep_for(milliseconds(1000));
			continue;
		}
		else if (birth_year > 2006) {
			system("CLS");
			cout << "\ncap\n\n";
			sleep_for(milliseconds(1000));
			continue;
		}
		else if (birth_year > 2010) {
			system("CLS");
			cout << "\nBig CAP\n\n";
			sleep_for(milliseconds(1000));
			continue;
		}
		else if (birth_year > 2020) {
			system("CLS");
			cout << "\nHUGE CAP\n\n";
			sleep_for(milliseconds(1000));
			continue;
		}
		else {
			break;
		}
	}


	while (true) { //month
		birth_month = int_debug("\nMonth: \n\n");
		cin.clear();
		cin.ignore(10000, '\n');
		if (birth_month < 1 || birth_month > 12) {
			system("CLS");
			cout << "\n\nwe know it's bugcheck\n\n";
			sleep_for(milliseconds(1500));
			continue;
		}
		else {
			break;
		}
	}


	while (true) { //day
		birth_day = int_debug("\nDay: \n\n");
		cin.clear();
		cin.ignore(10000, '\n');
		if (birth_day > 31 || birth_day < 0) {
			system("CLS");
			cout << "\n\nwaiting for failure? it would be longer than Miromonovich's presidency\n\n";
			sleep_for(milliseconds(2000));
			continue;
		}
		if (birth_year % 4 == 0) {
			if (birth_month == 2) { //February
				if (birth_day > 29) {
					system("CLS");
					cout << "\ntesting again? catch my response\n\n";
					sleep_for(milliseconds(1500));
					continue;
				}
				else {
					break;
				}

			}
			else {
				break;
			}
		}
		else if (birth_year % 4 != 0) {
			if (birth_month == 2) { //February
				if (birth_day > 28) {
					system("CLS");
					cout << "\ntesting again? catch my response\n\n";
					sleep_for(milliseconds(1500));
					continue;
				}
				else {
					break;
				}
			}
		}
		if (birth_day < 1 || birth_day > 31) {
			system("CLS");
			cout << "\ntest? here is your debug\n\n";
			sleep_for(milliseconds(2000));
			continue;
		}
		else if (birth_month == 4 || birth_month == 6 || birth_month == 9 || birth_month == 11) { //30 day months
			if (birth_day > 30) {
				system("CLS");
				cout << "\n\nwaiting for failure? it would be longer than Miromonovich's presidency\n\n";
				sleep_for(milliseconds(2000));
				continue;
			}
			else {
				break;
			}
		}
		else { //31 day months
			break;
		}

	}



	//ID
	while (true) {
		id_number = int_debug("\nEnter last 3-digits of your ID: \n\n");
		cin.clear();
		cin.ignore(10000, '\n');
		if (id_number >= 1 and id_number <= 330)
		{
			break;
		}
		else if (id_number < 1 or id_number > 330) {
			cout << "\nTry again with glasses on -.-\n\n" << endl;
		}
		else
		{
			cout << "digits are required! \n";
		}
	}
	return 0;
}

void greeting() {
	//Greeting
	system("CLS");
	cout << setw(60);
	cout << "WELCOME " << name_of_customer;
	cout << "\n\n";
	sleep_for(milliseconds(2000));

}

int q = 0;


void quantity()
{

	while (true)
	{
		q = int_debug("\nHow many items would you like to get?\n\n");
		cin.clear();
		cin.ignore(10000, '\n');

		if (q >= 1 && q <= 30)
		{
			cout << "\n";
			break;
		}

		else if (q <= 0)
		{
			cout << "\nQuantity is always a positive number\n\n";
		}

		else if (q > 30)
		{
			cout << "\nUnfortunately, our shop does not have such a big number of this item\n\n";
		}

		else
		{
			cout << "\nWrong input, please try one more time\n\n";
		}
	}

}




void item_selection()
{
	while (true)
	{
		input_item = int_debug("Select a respective item: ");
		cin.clear();
		cin.ignore(10000, '\n');

		if (input_item < 1 || input_item > 12) {
			cout << "\nlength was not asked, enter an object number!\n\n";
			continue;
		}

		else {
			selected(input_category - 1, input_item - 1);
			break;
		}
	}
}



void number_of_item()
{
	cout << "\n";
	item_selection();
	quantity();
	cart();
}



void cart() {
	cart_list[ind][0] = lists[input_category - 1][input_item - 1][0];
	cart_list[ind][1] = lists[input_category - 1][input_item - 1][1];
	cart_list[ind][2] = to_string(q);
	if (input_category == 1) {
		cart_list[ind][3] = size_sh;
	}
	else if (input_category == 2 or input_category == 3) {
		cart_list[ind][3] = size_c;
	}
	else if (input_category == 4) {
		cart_list[ind][3] = "None";
	}
}




void total_cost() {
	item_cost = stoi(lists[input_category - 1][input_item - 1][1]) * q;
	total_sum += stoi(lists[input_category - 1][input_item - 1][1]) * q;
	cout << "Price: " << make_space(to_string(item_cost)) << " sums \n\n";
}


void main_categories();


void goback(string where) {
	int back_not;
	if (where == "buy") {
		back_not = int_debug("\n\n1. main menu\n2. selecting items\n\nSelect: ");
		cin.clear();
		cin.ignore(10000, '\n');
	}
	else if (where == "search") {
		back_not = int_debug("\n\n1. main menu\n2. searching items\n\nSelect: ");
		cin.clear();
		cin.ignore(10000, '\n');
	}

	if (back_not == 1) {
		system("CLS");
		main_menu();
	}
	else if (back_not == 2) {
		if (where == "buy") {
			main_categories();
		}
		else if (where == "search") {
			module_search();
		}
	}
	else if (back_not > 2 || back_not < 1) {
		cout << "\n\nError\n\n";
		goback(where);
	}
}


void main_categories()
{
	system("CLS");
	cout << "\nHere are categories: \n\n";
	show_array(categorie_list);
	cout << "\n5) main menu\n\n";
	input_category = int_debug("\nWhich one would you like to choose?(from 1-5)\n\n");



	if (input_category >= 1 && input_category <= 4)
	{
		switch (input_category)
		{
		case 1:
			sizeofshoes();
			show_list(lists, 0);
			number_of_item();
			total_cost();
			goback("buy");
			break;
		case 2:
			sizeofclothes();
			show_list(lists, 1);
			number_of_item();
			total_cost();
			goback("buy");
			break;
		case 3:
			sizeofclothes();
			show_list(lists, 2);
			number_of_item();
			total_cost();
			goback("buy");
			break;
		case 4:
			system("CLS");
			show_list(lists, 3);
			number_of_item();
			total_cost();

			goback("buy");
			break;

		default: cout << " Wrong input, please try again\n\n";
			break;
		}
	}
	else if (input_category == 5) {
		system("CLS");
		main_menu();
	}
	else
	{
		main_categories();
	}
}


int change_name()
{
	cout << "Enter name or '0' to go back: ";
	cin >> name_of_customer;
	cin.clear();
	cin.ignore(10000, '\n');
	if (name_of_customer == "0") {
		system("CLS");
		main_menu();
		return 0;
	}
	else {
		transform(name_of_customer.begin(), name_of_customer.end(), name_of_customer.begin(), toupper);
		cout << "\n\nName is successfully changed to " << name_of_customer << "\n\n";
	}
	sleep_for(milliseconds(2500));
	system("CLS");
	cout << setw(60);
	cout << "Welcome " << name_of_customer << "\n\n";
	main_menu();
	return 0;
}

int quit_not;

void sales()
{
	quit_not = int_debug("\n0.back\n1.continue (p.s. want to read 200 words essay?)\n\noption: ");
	cin.clear();
	cin.ignore(10000, '\n');
	if (quit_not == 0) {
		system("CLS");
		main_menu();
	}
	else if (quit_not == 1) {
		sleep_for(milliseconds(2000));
		cout << "\nIn our shop there is a special offer for every piece of clothing\n\n";
		sleep_for(milliseconds(2000));
		cout << "Discount 20% for every item (all prices are already with discount in site)\n\n";
		sleep_for(milliseconds(2000));
		cout << "On top of that, when buying any sort of  \n\n";
		sleep_for(milliseconds(1000));
		cout << "     Accessories in our site   \n\n";
		sleep_for(milliseconds(1000));
		cout << "                       The second is\n\n ";
		sleep_for(milliseconds(1000));
		cout << "                                  Completely FREEE\n\n";
		sleep_for(milliseconds(2000));
		cout << "Unfortunately, the special offer does not apply to backpacks\n\n";
		sleep_for(milliseconds(3000));
		cout << name_of_customer << ", Just bear in mind that the offer is just until December 10, 2021\n\n\n";
		sleep_for(milliseconds(2000));
		cout << setw(80);
		cout << " Wish you the best online shopping experience\n\n";
		sleep_for(milliseconds(3000));
		system("CLS");
		main_menu();
	}
	else {
		sleep_for(milliseconds(1000));
		cout << "\nohhh my, an Error\n";
		sleep_for(milliseconds(1000));
		sales();
	}

}


void creators()
{
	cout << " \"How to fail project successfully\" starter pack: \n\n";
	sleep_for(milliseconds(2000));
	cout << setw(80) << "\nAsadulla, or shy guy with big brains\n\n";
	sleep_for(milliseconds(2000));
	cout << setw(80) << "\nAlisher, the most reliable partner\n\n";
	sleep_for(milliseconds(2000));
	cout << setw(80) << "\nMiraziz, [pls don't forget to add description]\n\n"; //oops forgot to add, what an accident
	sleep_for(milliseconds(2000));
	cout << setw(80) << "\nSaid, why so many strange questions?(weird staring 0_0)\n\n";
	sleep_for(milliseconds(3000));
	system("CLS");
	main_menu();
}


void phylosophy()
{
	quit_not = int_debug("\n0.back\n1.continue (p.s. want to read 200 words essay?)\n\noption: ");
	cin.clear();
	cin.ignore(10000, '\n');
	if (quit_not == 0) {
		system("CLS");
		main_menu();
	}
	else if (quit_not == 1) {
		cout << "\nIf you are questioning this,\n\n";
		sleep_for(milliseconds(2000));
		cout << "Probably you have some problems or your are just \n\n";
		sleep_for(milliseconds(2000));
		cout << "Interested in investigating this project, even may be\n\n";
		sleep_for(milliseconds(2000));
		cout << "You are just a funny guy that loves weird questions  \n\n";
		sleep_for(milliseconds(2000));
		cout << "Just like the code writer of this text\n\n";
		sleep_for(milliseconds(2000));
		cout << "I do not have any ideas,\n\n";
		sleep_for(milliseconds(2000));
		cout << "But hope you decided to go to this page because either you are funny or curious about this project)\n\n";
		sleep_for(milliseconds(3000));
		cout << "                           ******          *         *          ******\n";
		sleep_for(milliseconds(500));
		cout << "                                 *        *   )  )    *        *\n";
		sleep_for(milliseconds(500));
		cout << "                                  *       *           *       *\n";
		sleep_for(milliseconds(500));
		cout << "                                   *      *    _ _ /  *      *\n";
		sleep_for(milliseconds(500));
		cout << "                                    ****** *         * ******\n\n\n";
		sleep_for(milliseconds(3000));
		system("CLS");
		main_menu();
	}
	else {
		sleep_for(milliseconds(1000));
		cout << "\nohhh my, an Error\n";
		sleep_for(milliseconds(1000));
		phylosophy();
	}
}




int quit() {
	system("CLS");
	cout << "input variations:\n"
		<< "* yes or y\n"
		<< "* no or n\n"
		<< "do you want to print a cheque? ";
	cin >> choice;
	cin.clear();
	cin.ignore(10000, '\n');
	transform(choice.begin(), choice.end(), choice.begin(), toupper);
	cout << "\n";
	if (choice == "Y" || choice == "YES")
	{
		system("CLS");

		if (cart_list[0][0] == "") {
			cout << "\n\nempty\n\n";
			sleep_for(milliseconds(3000));
			cout << "Thank you for choosing us, " << name_of_customer << "\nxayr >.<\n" << "Hope you will come again.\n\n";
			return 0;
		}
		cout << "________________________________________________________________________________________\n";
		cout << "________________________________________________________________________________________\n\n";
		cout << "Item:                 Cost:                   Quantity:                Size:\n\n";
		for (int item_cart1 = 0; item_cart1 < 100; item_cart1++) {
			int space_size;
			for (int aspects = 0; aspects < 4; aspects++) {
				space_size = 25 - cart_list[item_cart1][aspects].length();
				string space(space_size, ' ');
				if (aspects == 1) {
					cout << make_space(cart_list[item_cart1][aspects]) << space;
					continue;
				}
				cout << cart_list[item_cart1][aspects] << space;
				if (aspects == 3) {
					cout << endl;
				}
			}
			if (cart_list[item_cart1 + 1][0] == "") {
				cout << "________________________________________________________________________________________\n";
				cout << "________________________________________________________________________________________\n\n";
				cout << "\nTotal cost:   " << make_space(to_string(total_sum)) << " sums\n" << endl;
				sleep_for(milliseconds(3000));
				cout << "Thank you for choosing us, " << name_of_customer << "\nxayr >.<\n" << "Hope you will come again.\n\n";
				break;
			}
		}
	}
	else if (choice == "N" || choice == "NO")
	{
		cout << "\nnah u tweakin\n\n";
		sleep_for(milliseconds(1000));
		cout << "Thank you for choosing us, " << name_of_customer << "\nxayr >.<\n" << "Hope you will come again.\n\n";
		return 0;

	}
	else
	{
		cout << "really?\n";
		sleep_for(milliseconds(1000));
		cout << "one more time, please\n" << endl;
		sleep_for(milliseconds(1000));
		quit();
	}

	return 0;
}

int main_menu() {


	cout << "Here are options:\n\n"
		<< "1.buy items\n"
		<< "2.change name\n"
		<< "3.show cart\n"
		<< "4.info\n"
		<< "5.sales\n"
		<< "6.contacts\n"
		<< "7.item search\n\n"
		<< "\n8.quit\n\n";
	y = int_debug("Which one would you like to choose?(from 1-8) ");

	if (y >= 1 && y <= 8)
	{
		switch (y)
		{
		case 1: system("CLS"); main_categories(); break;
		case 2: system("CLS"); change_name(); break;
		case 3: system("CLS"); show_cart(cart_list); break;
		case 4: system("CLS"); phylosophy(); break;
		case 5: system("CLS"); sales(); break;
		case 6: system("CLS"); creators(); break;
		case 7: system("CLS"); module_search(); break;
		case 8: system("CLS"); quit(); break;
		default: cout << " Wrong input, please try again\n\n";
			break;
		}
		return 0;
	}
	else if (input_category > 8 || input_category < 1)
	{
		cout << "really?\n";
		sleep_for(milliseconds(1000));
		cout << "one more time, please\n" << endl;
		sleep_for(milliseconds(1000));
		system("CLS");
		main_menu();
	}

	else if (y > 8 || y < 1)
	{
		cout << "really?\n";
		sleep_for(milliseconds(1000));
		cout << "one more time, please\n" << endl;
		sleep_for(milliseconds(1000));
		system("CLS");
		main_menu();
	}

	return 0;
}


int main()
{
	cout << setw(59) << "---HELLO---" << endl;
	cout << setw(73) << "you are right now on the women's side\n";
	cout << setw(77) << " wish you the best online shopping experience\n\n";
	customer_details();
	greeting();

	main_menu();

	system("pause");
	return 0;
}