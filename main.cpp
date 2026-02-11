#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAX_MOVIES 8

struct Movie {
    string title;
    string genre;
    int year;
    string rating;    // e.g., "PG", "R", etc.
    int minAge;       // Minimum age required to watch the movie
};

// Function prototypes
void printMenu();
void listAllMovies(const Movie movies[], int count);
void randomMovie(const Movie movies[], int count);
void randomByGenre(const Movie movies[], int count);
void randomByAge(const Movie movies[], int count);
void showMovieDetails(const Movie& movie);       //reference
const Movie* pickRandomFromIndexes(const Movie movies[], const int indexes[], int indexescount); //pointer return

int main() {
    Movie movies[MAX_MOVIES] = {
        {"Star Wars", "Sci-Fi", 1977, "PG", 10},
        {"Spider-Man", "Action", 2002, "PG-13", 13},
        {"The Dark Knight", "Action", 2008, "PG-13", 13},
        {"Fight Club", "Drama", 1999, "R", 17},
        {"Oppenheimer", "Drama", 2023, "R", 17},
        {"Nightcrawler", "Thriller", 2014, "R", 17},
        {"Blade Runner", "Sci-Fi", 1982, "R", 17},
        {"Harry Potter", "Fantasy", 2001, "PG", 10}
    };

int choice;
srand((unsigned)time(nullptr)); // Seed the random number generator

do {
    printMenu();
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // consume the newline 

    switch (choice) {
        case 1:
            listAllMovies(movies, MAX_MOVIES);
            break;
        case 2:
            randomMovie(movies, MAX_MOVIES);
            break;
        case 3:
            randomByGenre(movies, MAX_MOVIES);
            break;
        case 4:
            randomByAge(movies, MAX_MOVIES);
            break;
        case 5:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again.\n" << endl;
    }
    cout << "\n";
} while (choice != 5);

return 0;
}

void printMenu() {
    cout << "=== Random Movie Generator ===\n" << endl;
    cout << "1. List all movies\n" << endl;
    cout << "2. Pick a random movie\n" << endl;
    cout << "3. Pick a random movie by genre\n" << endl;
    cout << "4. Pick a random movie by age\n" << endl;
    cout << "5. Exit\n";
}

void showMovieDetails(const Movie& movie) {
    cout << "Selected Movie:\n";
    cout << "Title: " << movie.title << "\n";
    cout << "Genre: " << movie.genre << "\n";
    cout << "Year: " << movie.year << "\n";
    cout << "Rating: " << movie.rating << " (Minimum Age: " << movie.minAge << "+)\n";
}

void listAllMovies(const Movie movies[], int count) {
    cout << " All Movies in List:\n";
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ". " << movies[i].title << " (" << movies[i].year << ") - " 
             << movies[i].genre << " [" << movies[i].rating << "]\n";
    }   
}

void randomMovie(const Movie movies[], int count) {
    if (count == 0) {
        cout << "No movies available.\n";
        return;
    }
    int r = rand() % count;
    const Movie* picked = &movies[r]; // pointer to chosen movie
    showMovieDetails(*picked);
}

const Movie* pickRandomFromIndexes(const Movie movies[], const int indexes[], int indexescount) {
    if (indexescount == 0) return nullptr; // No movies to choose from
    int r = rand() % indexescount;
    return &movies[indexes[r]]; // Return pointer to randomly picked movie
}

void randomByGenre(const Movie movies[], int count) {
    string genreChoice;
    cout << "Enter genre( Action, Drama, Sci-Fi, Fantasy, Thriller): ";
    getline(cin, genreChoice);

    int matchingIndexes[MAX_MOVIES];
    int matchCount = 0;

    for (int i = 0; i < count; ++i) {
        if (movies[i].genre == genreChoice) {
            matchingIndexes[matchCount++] = i; 
            matchCount++;
        } else {
            // do nothing, just continue checking other movies
        }
    }

    if (matchCount == 0) {
        cout << "No movies found in the genre: " << genreChoice << "\n";
        return;
    }
    const Movie* picked = pickRandomFromIndexes(movies, matchingIndexes, matchCount);
    showMovieDetails(*picked);
}

void randomByAge(const Movie movies[], int count) {
    int age;
    cout << "Enter your age: ";
    cin >> age;
    cin.ignore(); // consume the newline

    int allowed[MAX_MOVIES];
    int allowedCount = 0;

    for (int i = 0; i < count; ++i) {
        if (age >= movies[i].minAge) {
            allowed[allowedCount++] = i; 
        } else if (age < movies[i].minAge) {
            // cout << "Skipping " << movies[i].title << " (age restriction)\n";
        } else {
            // do nothing, just continue checking other movies
        }
    }
    if (allowedCount == 0) {
        cout << "No movies available for your age group.\n";
        return;
    }
    const Movie* picked = pickRandomFromIndexes(movies, allowed, allowedCount);
    showMovieDetails(*picked);
}