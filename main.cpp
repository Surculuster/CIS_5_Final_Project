#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Show Tracker

struct Show {
	string title;
	string genre;
	string author;
	int episodes;
	int episodesWatched;
	int year;
	float rating;
	bool isCompleted;


	Show(string t, string g, string a, int e, int ew, int y, float r)
		: title(t), genre(g), author(a), episodes(e), episodesWatched(ew), year(y), rating(r), isCompleted(false) {
		
		if (rating < 0.0) {
			rating = 0.0;
		}
		else if (rating > 10.0) {
			rating = 10.0;
		}
		if (episodes < 0) {
			episodes = 0;
		}
		if (episodesWatched < 0) {
			episodesWatched = 0;
		}
		if (episodesWatched >= episodes) {
			isCompleted = true;
		}
	}

	Show() : title("Unknown"), genre("Unknown"), author("Unknown"), episodes(0), episodesWatched(0), year(0), rating(0.0), isCompleted(false) {}
};

void printMenu() {
	cout << "======| Show Tracker Menu |====== " << endl;
	cout << "1. Display all shows" << endl;
	cout << "2. Add a new show" << endl;
	cout << "3. Search for a show" << endl;
	cout << "4. Edit a show" << endl;
	cout << "5. Exit" << endl;
}

void titleAdd(Show& show, string* title) {
	string word;
	cout << "TITLE:\nEnter the title of the show: ";
	cin >> *title;
	cin.ignore();
	cout << "Would you like to add another word? (y/n): ";
	char choice;
	cin >> choice;
	cin.ignore();
	while (choice == 'y' || choice == 'Y') {
		cout << "Enter the additional word: ";
		cin >> word;
		*title += " " + word;
		cin.ignore();
		cout << "Would you like to add another word? (y/n): ";
		cin >> choice;
		cin.ignore();
	}
	cout << endl;
}
void genreAdd(Show& show, string* genre) {
	string word;
	cout << "GENRE:\nEnter the genre of the show: ";
	cin >> *genre;
	cin.ignore();
	cout << "Would you like to add another word? (y/n): ";
	char choice;
	cin >> choice;
	cin.ignore();
	while (choice == 'y' || choice == 'Y') {
		*genre += ", ";
		cout << "Enter the additional word: ";
		cin >> word;
		*genre += word;
		cin.ignore();
		cout << "Would you like to add another word? (y/n): ";
		cin >> choice;
		cin.ignore();
	}
	cout << endl;
}
void authorAdd(Show& show, string* author) {
	string word;
	cout << "AUTHOR:\nEnter the author of the show: " ;
	cin >> *author;
	cin.ignore();
	cout <<	"Would you like to add another word? (y/n): ";
	char choice;
	cin >> choice;
	cin.ignore();
	while (choice == 'y' || choice == 'Y') {
		cout << "Enter the additional word: ";
		cin >> word;
		*author += " " + word;
		cin.ignore();
		cout << "Would you like to add another word? (y/n): ";
		cin >> choice;
		cin.ignore();
	}
	cout << endl;
}

void displaySingleShow(const Show& show) {
	cout << endl << "====| " << show.title << " |====" << endl;
	cout << left << setw(20) << "Genre: " << show.genre << endl;
	cout << left << setw(20) << "Author: " << show.author << endl;
	cout << left << setw(20) << "Episodes: " << show.episodes << endl;
	cout << left << setw(20) << "Episodes Watched: " << show.episodesWatched << fixed << setprecision(1) << " (" << (show.episodesWatched * 1.0) / show.episodes * 100 << "%)" << endl;
	cout << left << setw(20) << "Year: " << show.year << endl;
	cout << fixed << setprecision(1);
	cout << left << setw(20) << "Rating: " << show.rating << "/10" << endl;
	cout << left << setw(20) << "Completed: " << (show.isCompleted ? "Yes" : "No") << endl;
	cout << "------------------------" << endl;
}
void displayMultipleShows(const Show shows[], int count) {
	for (int i = count; i < count + 5; i++) {
		cout << "Show " << i + 1 << ":" << endl;
		displaySingleShow(shows[i]);
	}
}
void displayAllShows(const Show shows[], int count, const int MAX_SHOWS) {
	if (count == 0) {
		cout << "No shows to display." << endl;
		return;
	}
	int page = 1;
	cout << endl << "Displaying shows (" << (page - 1) * 5 + 1 << "-" << page * 5 << "): " << endl << "------------------------" << endl;
	for (int i = 0; i < 5; i++) {
		cout << endl << "Show " << i + 1 << ":" << endl;
		displaySingleShow(shows[i]);
	}
	int pageChoice;
	do {
		cout << "Press 1 to go to previous page, 2 to go to next page, 0 to exit: ";
		cin >> pageChoice;
		cin.ignore();
		switch (pageChoice) {
		case 1:
			if (page != 1) {
				page--;
				cout << "Displaying shows (" << (page - 1) * 5 + 1 << "-" << page * 5 << "): " << endl;
				displayMultipleShows(shows, (page - 1) * 5);
			}
			else cout << "You are on the first page." << endl << endl;
			break;
		case 2:
			if ((page + 1) * 5 <= MAX_SHOWS) {
				page++;
				cout << "Displaying shows (" << (page - 1) * 5 + 1 << "-" << page * 5 << "): " << endl;
				displayMultipleShows(shows, (page - 1) * 5);
			}
			else cout << "You are on the last page." << endl << endl;
			break;
		case 0:
			cout << "Exiting..." << endl << endl;
			break;
		}
	} while (pageChoice != 0);
}

void addShow(Show shows[], int& count, const Show& newShow) {
	if (count < 100) {
		count++;
		string title, genre, author;
		int episodes, episodesWatched, year;
		float rating;
		cout << "Adding a new show (ONE WORD at a time): " << endl << endl;
		titleAdd(shows[count - 1], &title);
		genreAdd(shows[count - 1], &genre);
		authorAdd(shows[count - 1], &author);
		cout << "Enter the number of episodes: " << endl;
		cin >> episodes;
		cin.ignore();
		cout << "Enter the number of episodes watched: " << endl;
		cin >> episodesWatched;
		cin.ignore();
		if (episodesWatched < 0) episodesWatched = 0;
		else if (episodesWatched > episodes) episodesWatched = episodes;
		cout << "Enter the year of release: " << endl;
		cin >> year;
		cin.ignore();
		cout << "Enter the rating (0-10): " << endl;
		cin >> rating;
		cin.ignore();
		if (rating < 0.0) rating = 0.0;
		else if (rating > 10.0) rating = 10.0;

		shows[count - 1] = Show(title, genre, author, episodes, episodesWatched, year, rating);
		cout << endl <<"Show added successfully!" << endl << endl;
	}
	else {
		cout << "Cannot add more shows. Maximum limit reached." << endl;
	}
}
void editShow(Show& show) {
	int editChoice;
	displaySingleShow(show);
	do {
		cout << "\n====| Editing Show: " << show.title << " |==== " << endl;
		cout << "1. Edit title" << endl;
		cout << "2. Edit genre" << endl;
		cout << "3. Edit author" << endl;
		cout << "4. Edit number of episodes" << endl;
		cout << "5. Edit number of episodes watched" << endl;
		cout << "6. Edit year of release" << endl;
		cout << "7. Edit rating" << endl;
		cout << "8. Exit editing" << endl << endl;
		cout << "Enter your choice: ";
		cin >> editChoice;
		cin.ignore();

		switch (editChoice) {
		case 1: // Edit title ";
			cout << "(Enter ONE WORD at a time)" << endl;
			titleAdd(show, &show.title);
			break;
		case 2: // Edit genre
			cout << "(Enter ONE WORD at a time)" << endl;
			genreAdd(show, &show.genre);
			break;
		case 3: // Edit author
			cout << "(Enter ONE WORD at a time)" << endl;
			authorAdd(show, &show.author);
			break;
		case 4: // Edit number of episodes
			cout << "Enter new number of episodes: " << endl;
			cin >> show.episodes;
			cin.ignore();
			break;
		case 5: // Edit number of episodes watched
			cout << "Enter new number of episodes watched: " << endl;
			cin >> show.episodesWatched;
			cin.ignore();
			if (show.episodesWatched < 0) show.episodesWatched = 0;
			else if (show.episodesWatched > show.episodes) show.episodesWatched = show.episodes;
			if (show.episodesWatched >= show.episodes) show.isCompleted = true;
			else show.isCompleted = false;
			break;
		case 6: // Edit year of release
			cout << "Enter new year of release: " << endl;
			cin >> show.year;
			cin.ignore();
			break;
		case 7: // Edit rating
			cout << "Enter new rating (0-10): " << endl;
			cin >> show.rating;
			cin.ignore();
			if (show.rating < 0.0) show.rating = 0.0;
			else if (show.rating > 10.0) show.rating = 10.0;
			break;
		case 8: // Exit editing
			cout << "Exiting editing..." << endl << endl;
			break;
		default:
			cout << "Invalid choice." << endl;
		}
	} while (editChoice != 8);
}

int main() {
	const int MAX_SHOWS = 100;
	Show shows[MAX_SHOWS];
	int choice;

	shows[0] = Show("Attack on Titan", "Action, Dark Fantasy", "Hajime Isayama", 75, 0, 2013, 9.0);
	shows[1] = Show("Gurren Lagann", "Action, Mecha", "Kazuki Nakashima", 27, 0, 2007, 8.7);
	shows[2] = Show("Breaking Bad", "Crime, Drama", "Vince Gilligan", 62, 0, 2008, 9.5);
	shows[3] = Show("The Dragon Prince", "Fantasy, Adventure", "Aaron Ehasz", 24, 0, 2018, 8.0);
	shows[4] = Show("Avatar: The Last Airbender", "Action, Adventure", "Michael Dante DiMartino", 61, 0, 2005, 9.2);
	shows[5] = Show("The Legend of Korra", "Action, Adventure", "Michael Dante DiMartino", 52, 0, 2012, 8.4);
	int count = 6;
	int index;

	do {
		printMenu();
		cout << "Enter your choice: ";
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 1: // Display all shows
			displayAllShows(shows, count, MAX_SHOWS);
			break;
		case 2: // Add a new show
			addShow(shows, count, Show());
			break;
		case 3: // Search for a show
			cout << "Enter the index of the show to search: ";
			cin >> index;
			index--;
			cin.ignore();
			if (index >= 0 && index < count) {
				cout << endl << "------------------------";
				displaySingleShow(shows[index]);
				cout << endl;
			}
			else cout << "Invalid show index." << endl << endl;
			break;
		case 4: // Edit a show
			cout << "Enter the index of the show to edit: ";
			cin >> index;
			index--;
			cin.ignore();
			if (index >= 0 && index < count) editShow(shows[index]);
			else cout << "Invalid show index." << endl << endl;
			break;
		case 5: // Exit
			cout << "Exiting..." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl << endl;
		}
	} while (choice != 5);
}